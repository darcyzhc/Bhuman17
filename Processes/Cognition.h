/**
 * @file Processes/Cognition.h
 * Declaration of a class that represents a process that receives data from the robot at about 60 Hz.
 */

#pragma once

#include "Tools/ProcessFramework/SPLMessageHandler.h" // include this first to prevent WinSock2.h/Windows.h conflicts

#include "Tools/Logging/Logger.h"
#include "Tools/Module/ModulePackage.h"
#include "Tools/ProcessFramework/Process.h"

/**
 * @class Cognition
 * A class that represents a process that receives data from the robot at about 30 Hz.
 */
class Cognition : public Process
{
private:
  Receiver<DebugToCognition> theDebugReceiver;   //定义了到其他两个process(线程实现)的通信接收器和发射器，实现进程(线程)间通信
  DebugSender<CognitionToDebug> theDebugSender;
  Receiver<MotionToCognition> theMotionReceiver;
  Sender<CognitionToMotion> theMotionSender;

  SPLStandardMessageBuffer<MAX_NUMBER_OF_PARALLEL_RECEIVABLE_SPLSTDMSG> inTeamMessages;  //收到的队伍消息
  RoboCup::SPLStandardMessage outTeamMessage;    //要发送的队伍消息
  SPLMessageHandler theSPLMessageHandler;   //消息处理器

  int numberOfMessages;
  ModuleManager moduleManager; /**< The solution manager handles the execution of modules. */
  Logger logger; /**< The logger logs representations in the background. */

public:
  Cognition();

  /**
   * The method is called from the framework once in every frame.
   */
  virtual bool main();

  /**
   * The method is called directly before the first call of main().
   */
  virtual void init();

  /**
   * The method is called when the process is terminated.
   */
  virtual void terminate();

  /**
   * The function handles incoming debug messages.
   * @param message the message to handle.
   * @return Has the message been handled?
   */
  virtual bool handleMessage(InMessage& message);  //InMessage：用来从 被MessageHandler派生类使用的MessageQueue中读取单条消息的借口
};
