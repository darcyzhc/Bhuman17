/**
 * @file Tools/ProcessFramework/SPLMessageHandler.cpp
 *
 * @author <a href="mailto:jesse@tzi.de">Jesse Richter-Klug</a>
 *
 * based on TeamHandler.cpp authored by
 * @author <A href="mailto:Thomas.Roefer@dfki.de">Thomas Röfer</A>
 */

#include "SPLMessageHandler.h"
#include "Platform/BHAssert.h"
#include "Platform/SystemCall.h"
#include "Tools/Debugging/DebugDrawings.h"

void SPLMessageHandler::startLocal(int port, unsigned localId)
{
  ASSERT(!this->port);
  this->port = port;
  this->localId = localId;

  socket.setBlocking(false);
  VERIFY(socket.setBroadcast(false));
  std::string group = SystemCall::getHostAddr();
//      OUTPUT_TEXT("SPLMessageHandler::startLocal_group1:");
//      OUTPUT_TEXT(group);
  group = "239" + group.substr(group.find('.'));
  VERIFY(socket.bind("0.0.0.0", port));
  VERIFY(socket.setTTL(0)); //keep packets off the network. non-standard(?), may work.
  VERIFY(socket.joinMulticast(group.c_str()));
  VERIFY(socket.setTarget(group.c_str(), port));
  socket.setLoopback(true);
//      OUTPUT_TEXT("SPLMessageHandler::startLocal_group2:");
//      OUTPUT_TEXT(group);
}

void SPLMessageHandler::start(int port, const char* subnet)
{
  ASSERT(!this->port);
  this->port = port;

  std::string ip = SystemCall::getHostAddr();
  socket.setBlocking(false);
  VERIFY(socket.setBroadcast(true));
  VERIFY(socket.bind("0.0.0.0", port));
  socket.setTarget(subnet, port);
  socket.setLoopback(false);

//  printf("SPLMessageHandler::start_bcastAddr Port is: %d\n", port);
//  OUTPUT_TEXT("SPLMessageHandler::start:");
//  OUTPUT_TEXT(port);
}

void SPLMessageHandler::send()
{
  if(!port)
    return;

  socket.write((char*)& out, offsetof(RoboCup::SPLStandardMessage, data) + out.numOfDataBytes);

  // Plot usage of data buffer in percent:
  const float usageInPercent = 100.f * out.numOfDataBytes / static_cast<float>(SPL_STANDARD_MESSAGE_DATA_SIZE);
  PLOT("module:TeamHandler:standardMessageDataBufferUsageInPercent", usageInPercent);
  
//  printf("module:TeamHandler:standardMessageDataBufferUsageInPercent: %f\n", usageInPercent);
//  OUTPUT_TEXT("module:TeamHandler:standardMessageDataBufferUsageInPercent");
//  OUTPUT_TEXT(usageInPercent);
}

unsigned SPLMessageHandler::receive()
{
  if(!port)
    return 0; // not started yet

  int size;
  unsigned remoteIp = 0;
  unsigned receivedSize = 0;

  do
  {
    size = localId ? socket.readLocal((char*)in.setForward(), sizeof(RoboCup::SPLStandardMessage))
                   : socket.read((char*)in.setForward(), sizeof(RoboCup::SPLStandardMessage), remoteIp);
    if(size < static_cast<int>(offsetof(RoboCup::SPLStandardMessage, data)) || size > static_cast<int>(sizeof(RoboCup::SPLStandardMessage)))
      in.removeFront();
//      printf("SPLMessageHandler::receive_remoteIp: %d\n", remoteIp);
//      OUTPUT_TEXT("SPLMessageHandler::receive_remoteIp:");
//      OUTPUT_TEXT(remoteIp);
  }
  while(size > 0);

  return receivedSize;
}
