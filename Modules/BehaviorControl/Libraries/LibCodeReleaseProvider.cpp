/**
 * @file LibCodeRelease.cpp
 */

#include "LibCodeReleaseProvider.h"

MAKE_MODULE(LibCodeReleaseProvider, behaviorControl);

void LibCodeReleaseProvider::update(LibCodeRelease& libCodeRelease)
{
    //OUTPUT_TEXT("LibCodeReleaseProvider::update()");
//    OUTPUT_TEXT("Mark");
//    OUTPUT_TEXT(theBallPercept.status);
    //计算球的全局坐标
    libCodeRelease.globalballx = theRobotPose.translation.x() + (float)std::sqrt(std::pow(theBallModel.estimate.position.x(),2) + 
                            std::pow(theBallModel.estimate.position.y(),2))*std::cos(theRobotPose.rotation + theBallModel.estimate.position.angle());
    libCodeRelease.globalbally = theRobotPose.translation.y() + (float)std::sqrt(std::pow(theBallModel.estimate.position.x(),2) + 
                            std::pow(theBallModel.estimate.position.y(),2))*std::sin(theRobotPose.rotation + theBallModel.estimate.position.angle());
    
//    OUTPUT_TEXT(libCodeRelease.globalballx);
    
    if(std::abs(libCodeRelease.globalballx) > 4500.f || std::abs(libCodeRelease.globalbally) > 3000.f)
        libCodeRelease.ballOut=true;
    else libCodeRelease.ballOut=false;
    //暂时未知
    libCodeRelease.angle1 = (theRobotPose.inversePose * Vector2f(theFieldDimensions.xPosOpponentGroundline, 500.f)).angle();
    libCodeRelease.angle2 = (theRobotPose.inversePose * Vector2f(theFieldDimensions.xPosOpponentGroundline, -500.f)).angle();
     if(libCodeRelease.detectedJersey == 1)
      {
        libCodeRelease.globalplayx = libCodeRelease.centerOnFieldx * std::cos(theRobotPose.rotation) + 
                                                                        libCodeRelease.centerOnFieldy * std::sin(theRobotPose.rotation) + theRobotPose.translation.x();
        libCodeRelease.globalplayy = -libCodeRelease.centerOnFieldx * std::sin(theRobotPose.rotation) + 
                                                                        libCodeRelease.centerOnFieldy * std::cos(theRobotPose.rotation) - theRobotPose.translation.y();
      }
  

  if(std::sqrt(std::pow( libCodeRelease.lasttheBallModelx -  libCodeRelease.globalballx ,2)+ 
                                std::pow( libCodeRelease.lasttheBallModely - libCodeRelease.globalbally,2)) > 300)
	{
		 libCodeRelease.isMovedBall = true;
	}
	if(std::sqrt(std::pow( libCodeRelease.lasttheBallModelx -  libCodeRelease.globalballx ,2)+ 
                    std::pow( libCodeRelease.lasttheBallModely - libCodeRelease.globalbally,2)) < 300)
	{
		 libCodeRelease.isMovedBall = false;
	}
    
  //下面获取视野中的机器人的信息
  int i=0;
  for(const PlayersFieldPercept::PlayerOnField& p: thePlayersFieldPercept.players) //PlayersFieldPercept.players是一个vector<PlayerOnField>类型的容器
	{
        i++;
        libCodeRelease.players[i]=p;
	}
    libCodeRelease.numOfPlayers=i;
    if(std::abs(theRobotPose.rotation) < 10_deg  )
      {
          if(libCodeRelease.numOfPlayers>0)
          {
               int i;
              for(i=1; i<=libCodeRelease.numOfPlayers; i++)
              {
                  //if(libCodeRelease.players[i].detectedJersey==false) continue;
                  if((theRobotPose.translation.x() + (float)std::sqrt(std::pow(libCodeRelease.players[i].centerOnField.x(),2) + 
                            std::pow(libCodeRelease.players[i].centerOnField.y(),2))*std::cos(theRobotPose.rotation + libCodeRelease.players[i].centerOnField.angle()))>3900 && 
                            std::abs((theRobotPose.translation.y() + (float)std::sqrt(std::pow(libCodeRelease.players[i].centerOnField.x(),2) + 
                            std::pow(libCodeRelease.players[i].centerOnField.y(),2))*std::sin(theRobotPose.rotation + libCodeRelease.players[i].centerOnField.angle())))<720)   //如果该机器人在禁区内
                  {
                      if((theRobotPose.translation.y() + (float)std::sqrt(std::pow(libCodeRelease.players[i].centerOnField.x(),2) + 
                            std::pow(libCodeRelease.players[i].centerOnField.y(),2))*std::sin(theRobotPose.rotation + libCodeRelease.players[i].centerOnField.angle()))>0)
                                libCodeRelease.DirF=1;
                      else libCodeRelease.DirF=2;
                  }
              }
          }
          else libCodeRelease.DirF=0;
      } 
          
  int j=0;
   for(const auto& obstacle : theTeamPlayersModel.obstacles)
	{
        j++;
        libCodeRelease.TeamObstacle[j]=obstacle;
	}
          
  //下面获取通信信息
    for(auto const& teammate : theTeamData.teammates)
    {
        //OUTPUT_TEXT(teammate.number);
        //OUTPUT_TEXT(teammate.theRobotPose.translation.x());
        switch(teammate.number)
        {
            case 1:
                libCodeRelease.keeper = teammate; break;
            case 2:
                libCodeRelease.striker1 = teammate; break;
            case 3:
                libCodeRelease.defender1 = teammate; break;
            case 4:
                libCodeRelease.defender2 = teammate; break;
            case 5:
                libCodeRelease.striker2 = teammate; break;
            default: break;
        }
    }
    
        //检测看到的障碍物
        libCodeRelease.closestObstacle.centerOnField.x()=0;
        for(const auto& obstacle : thePlayersFieldPercept.players)
            {
                if(libCodeRelease.closestObstacle.centerOnField.x()==0)
                    libCodeRelease.closestObstacle=obstacle;
                else if(obstacle.centerOnField.x()<libCodeRelease.closestObstacle.centerOnField.x())
                    libCodeRelease.closestObstacle=obstacle;
            }
        if(libCodeRelease.closestObstacle.centerOnField.x()<450 && libCodeRelease.closestObstacle.centerOnField.x()>0 && std::abs(libCodeRelease.closestObstacle.centerOnField.y())<250 && std::abs(libCodeRelease.closestObstacle.centerOnField.y())>0)
        {
            if(libCodeRelease.closestObstacle.centerOnField.y()>0)
                libCodeRelease.ObsAtLorR=1;
            else  libCodeRelease.ObsAtLorR=-1;
        }
        else libCodeRelease.ObsAtLorR=0;

        //OUTPUT_TEXT(libCodeRelease.ObsAtLorR);

    libCodeRelease.tilt = (float)(-0.085*(theBallModel.estimate.position.norm() / 1000) + 0.435);
      if(libCodeRelease.tilt > 0.35f)
          libCodeRelease.tilt = 0.35f;
      if(libCodeRelease.tilt < 0.18f)
          libCodeRelease.tilt = 0.18f;
     //OUTPUT_TEXT(static_cast<int>(theTeamData.numberOfActiveTeammates));
                                
    //球在
    libCodeRelease.ballx = (theTeamBallModel.position.x() - theRobotPose.translation.x())*std::cos(theRobotPose.rotation) + (theTeamBallModel.position.y() - theRobotPose.translation.y())*std::sin(theRobotPose.rotation);
    libCodeRelease.bally = -(theTeamBallModel.position.x() - theRobotPose.translation.x())*std::sin(theRobotPose.rotation) + (theTeamBallModel.position.y() - theRobotPose.translation.y())*std::cos(theRobotPose.rotation);

                                
                                
                                
    libCodeRelease.timeSinceBallWasSeen = theFrameInfo.getTimeSince(theBallModel.timeWhenLastSeen);
    libCodeRelease.angleToGoal = (theRobotPose.inversePose * Vector2f(theFieldDimensions.xPosOpponentGroundline, 0.f)).angle(); 
    libCodeRelease.angleToGoalL = (theRobotPose.inversePose * Vector2f(theFieldDimensions.xPosOpponentGroundline, 200.f)).angle(); 
    libCodeRelease.angleToGoalR = (theRobotPose.inversePose * Vector2f(theFieldDimensions.xPosOpponentGroundline, -200.f)).angle();
    //OUTPUT_TEXT(libCodeRelease.angleToGoal);
    //OUTPUT_TEXT(libCodeRelease.angleToGoalL);
    


    libCodeRelease.between = [&](float value, float min, float max) -> bool
    {
    return value >= min && value <= max;
    };
}
