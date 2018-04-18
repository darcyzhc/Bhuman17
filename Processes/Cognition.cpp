/**
 * @file Processes/Cognition.cpp
 * Implementation of a class that represents a process that receives data from the robot at about 60 Hz.
 */

#include "Tools/Math/Eigen.h" // include first to avoid conflicts between Cabsl defines and some clang headers
#include "Cognition.h" // include second header conflicts on Windows
#include "Modules/Configuration/ConfigurationDataProvider/CognitionConfigurationDataProvider.h"
#include "Modules/Infrastructure/CameraProvider/CameraProvider.h"
#include "Modules/Infrastructure/LogDataProvider/CognitionLogDataProvider.h"
#include "Platform/BHAssert.h"
#include "Platform/Time.h"
#include "Platform/SystemCall.h"
#include "Representations/Communication/TeamData.h"
#include "Representations/Communication/BHumanMessage.h"

Cognition::Cognition() :
  Process(theDebugReceiver, theDebugSender),
  theDebugReceiver(this),
  theDebugSender(this),
  theMotionReceiver(this),
  theMotionSender(this),
  theSPLMessageHandler(inTeamMessages, outTeamMessage),
  moduleManager({ModuleBase::cognitionInfrastructure, ModuleBase::communication,
                 ModuleBase::perception, ModuleBase::modeling, ModuleBase::behaviorControl}),
  logger(Logger::LoggedProcess::cognition)
{
  theDebugSender.setSize(5200000, 100000);
  theDebugReceiver.setSize(2800000);
  theMotionSender.moduleManager = theMotionReceiver.moduleManager = &moduleManager;
}

void Cognition::init()
{
#ifdef TARGET_SIM
  //OUTPUT_TEXT("Cognition::init()_theSPLMessageHandler.startLocal");
  theSPLMessageHandler.startLocal(Global::getSettings().teamPort,   //该方法启动一个本地通信实例
                static_cast<unsigned>(Global::getSettings().playerNumber));  //第一个参数是监听的端口，第二个参数是robot标识符
  //OUTPUT_TEXT(Global::getSettings().teamPort);
  //OUTPUT_TEXT(static_cast<unsigned>(Global::getSettings().playerNumber));
  //SystemCall::playSound("theValidityDuck.wav");
#else
  //OUTPUT_TEXT("Cognition::init()_theSPLMessageHandler.start");
  std::string bcastAddr = UdpComm::getWifiBroadcastAddress();
   //printf("bcastAddr is: %s\n", (UdpComm::getWifiBroadcastAddress()).c_str());
   //printf("Port is: %d\n", Global::getSettings().teamPort);
  //OUTPUT_TEXT(bcastAddr);
  //SystemCall::playSound("theFlippingChicken.wav");
  theSPLMessageHandler.start(Global::getSettings().teamPort, bcastAddr.c_str());  //该方法启动一个给定端口的通信实例
                                                                                                                                                                //第一个参数是监听的端口，第二个参数是要广播的子网
#endif
  moduleManager.load();  //The method loads the selection of solutions from a configuration file.
  BH_TRACE_INIT("Cognition");  //@param name: The name of the current thread     @return: Whether the initialization was successful
 

  // Prepare first frame
  numberOfMessages = theDebugSender.getNumberOfMessages();
  OUTPUT(idProcessBegin, bin, 'c');  // * OUTPUT(idImage, bin, *pMyImage);
  //OUTPUT_TEXT(Global::getSettings().teamPort);
  //OUTPUT_TEXT(Global::getSettings().playerNumber);
}

void Cognition::terminate()
{
  moduleManager.destroy();    //   * The method destroys all modules. It can be called to destroy the modules  before the constructor is called.
  Process::terminate();
}

bool Cognition::main()
{
  // read from team comm udp socket
  static_cast<void>(theSPLMessageHandler.receive());
  
 // CognitionLogDataProvider::isFrameDataComplete(): The method returns whether idProcessFinished was received.
  if(CognitionLogDataProvider::isFrameDataComplete() && CameraProvider::isFrameDataComplete())   {
            //OUTPUT_TEXT("Cognition::terminate_if");
            timingManager.signalProcessStart();  // * The TimingManager has a special stopwatch that is used to keep track of the overall process time. 
                                        //You should call signalProcessStart at the beginning of every process iteration.It is used to calculate the frequency of the process.
            annotationManager.signalProcessStart();  //系统层面的注释，不用深究

            BH_TRACE_MSG("before TeamData");  //Adds a message to the log message ring buffer
            
            // push teammate data in our system
            if(Blackboard::getInstance().exists("TeamData") &&    //获取TeamData对象实例
               static_cast<const TeamData&>(Blackboard::getInstance()["TeamData"]).generate.operator bool())
               {
                   while(!inTeamMessages.empty())
                            static_cast<const TeamData&>(Blackboard::getInstance()["TeamData"]).generate(inTeamMessages.takeBack());
                //OUTPUT_TEXT("Cognition::main_if1");
                
               }
                      

            // Reset coordinate system for debug field drawing
            DECLARE_DEBUG_DRAWING("origin:Reset", "drawingOnField"); // Set the origin to the (0,0,0)
            ORIGIN("origin:Reset", 0.0f, 0.0f, 0.0f);

            STOPWATCH_WITH_PLOT("Cognition") moduleManager.execute();

            DEBUG_RESPONSE_ONCE("automated requests:DrawingManager") OUTPUT(idDrawingManager, bin, Global::getDrawingManager());
            DEBUG_RESPONSE_ONCE("automated requests:DrawingManager3D") OUTPUT(idDrawingManager3D, bin, Global::getDrawingManager3D());
            DEBUG_RESPONSE_ONCE("automated requests:StreamSpecification") OUTPUT(idStreamSpecification, bin, Global::getStreamHandler());

            theMotionSender.timeStamp = Time::getCurrentSystemTime();
            BH_TRACE_MSG("before theMotionSender.send()");
            theMotionSender.send();

            if(Blackboard::getInstance().exists("BHumanMessageOutputGenerator") && 
                        static_cast<const BHumanMessageOutputGenerator&>(Blackboard::getInstance()["BHumanMessageOutputGenerator"]).generate.operator bool() &&
                            static_cast<const BHumanMessageOutputGenerator&>(Blackboard::getInstance()["BHumanMessageOutputGenerator"]).sendThisFrame)
            {
              //生成要发送的消息
              static_cast<const BHumanMessageOutputGenerator&>(Blackboard::getInstance()["BHumanMessageOutputGenerator"]).generate(&outTeamMessage);

              BH_TRACE_MSG("before theTeamHandler.send()");
              theSPLMessageHandler.send();  //发送消息
              //OUTPUT_TEXT("Cognition::main_theSPLMessageHandler.send()");
            }

            timingManager.signalProcessStop();
            logger.execute();

            DEBUG_RESPONSE("timing") timingManager.getData().copyAllMessages(theDebugSender);

            DEBUG_RESPONSE("annotation") annotationManager.getOut().copyAllMessages(theDebugSender);
            annotationManager.clear();

            if(theDebugSender.getNumberOfMessages() > numberOfMessages + 1)
            {
              // Send process finished message
              if(Blackboard::getInstance().exists("CameraInfo") &&
                 static_cast<const CameraInfo&>(Blackboard::getInstance()["CameraInfo"]).camera == CameraInfo::lower)
              {
                // lower camera -> process called 'd'
                // Send completion notification
                theDebugSender.patchMessage(numberOfMessages, 0, 'd');
                OUTPUT(idProcessFinished, bin, 'd');
              }
              else
              {
                OUTPUT(idProcessFinished, bin, 'c');
              }
            }
            else
              theDebugSender.removeLastMessage();

            BH_TRACE_MSG("theDebugSender.send()");
            theDebugSender.send();

            // Prepare next frame
            numberOfMessages = theDebugSender.getNumberOfMessages();
            OUTPUT(idProcessBegin, bin, 'c');
  }
  
  else if(Global::getDebugRequestTable().pollCounter > 0 &&
          --Global::getDebugRequestTable().pollCounter == 0)
            OUTPUT(idDebugResponse, text, "pollingFinished");

  if(Blackboard::getInstance().exists("Image"))
  {
        if(SystemCall::getMode() == SystemCall::physicalRobot)
          setPriority(10);
        Thread::sleep(1);
        BH_TRACE_MSG("before waitForFrameData");
        CameraProvider::waitForFrameData();
        if(SystemCall::getMode() == SystemCall::physicalRobot)
          setPriority(0);
  }
  else
        Thread::sleep(33);

  return SystemCall::getMode() != SystemCall::physicalRobot;
}

bool Cognition::handleMessage(InMessage& message)
{
  //OUTPUT_TEXT("Cognition_Cognition::handleMessage");
  BH_TRACE_MSG("before Cognition:handleMessage");
  switch(message.getMessageID())  /** returns the message id of the current message */
  {
    case idModuleRequest:
    {
      unsigned timeStamp;
      message.bin >> timeStamp;
      moduleManager.update(message.bin, timeStamp);
      return true;
    }
    default:
      return CognitionLogDataProvider::handleMessage(message) ||
             CognitionConfigurationDataProvider::handleMessage(message) ||
             Process::handleMessage(message);
  }
}

MAKE_PROCESS(Cognition);

// Make sure that two time consuming modules are linked from the Controller library.
#ifdef MACOS

#include "Modules/Perception/BallPerceptors/BallPerceptor.h"
extern Module<BallPerceptor, BallPerceptorBase> theBallPerceptorModule;
auto linkBallPerceptor = &theBallPerceptorModule;

#include "Modules/Perception/ImagePreprocessors/ECImageProvider.h"
extern Module<ECImageProvider, ECImageProviderBase> theECImageProviderModule;
auto linkECImageProvider = &theECImageProviderModule;

#endif

