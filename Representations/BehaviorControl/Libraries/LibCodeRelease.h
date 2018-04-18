/**
 * @file LibCodeRelease.h
 */

#pragma once
#include "Tools/Function.h"
#include "Representations/Communication/TeamData.h"
#include "Representations/Perception/PlayersPercepts/PlayersFieldPercept.h"
#include "Tools/Modeling/Obstacle.h"
#include "Representations/Modeling/TeamPlayersModel.h"
STREAMABLE(LibCodeRelease,
{
  FUNCTION(bool(float value, float min, float max)) between,
  (bool)  alreadycomeback,
  (bool)  alreadykick,
  (bool)  alreadyLoseBall,
  (bool)  alreadyturn,
  (float) angle1,
  (float) angle2,
  (float) angleToGoal,  
  (float) angleToGoalL,      //机器人相对于敌方球门中心的角度
  (float) angleToGoalR, 
  (float) centerOnFieldx,
  (float) centerOnFieldy,
  (bool) detected,
  (bool)(false) detectedJersey,
  (bool) detectedJersey1,
  (float) Fieldx,
  (float) Fieldy,
  (float) globalballx ,    //球的全局坐标
  (float) globalbally ,
  (float) globalplayx,
  (float) globalplayy,
  (int) kickleg,
  (float) lasttheBallModelx,            //球的上一次位置坐标
  (float) lasttheBallModely,
  (float) leftOnFieldx,
  (float) leftOnFieldy,
  (bool)(false) isMovedBall,      //判断球是否移动了。若两次定位之间相差30mm则认为球移动了
  (bool) observesituation,
  (bool) ownTeam,
  (float) theCircleangle,         //中心圆相对于机器人的角度
  (float) themarkangle,         //己方罚球点相对于机器人的校对
  (int) timeSinceBallWasSeen,
  (float) turnbody,
  (Teammate) striker1,
  (Teammate) striker2,
  (Teammate) defender1,
  (Teammate) defender2,
  (Teammate) keeper,
  (PlayersFieldPercept::PlayerOnField) players[10],
  (Obstacle) TeamObstacle[16],
  (int)(0) numOfPlayers,
  (int)(0) DirF,  //射门方向，1代表守门员在左边，2代表右边，0代表未检测到障碍物
  (bool)(false) ballOut,  //球是否出界
  (float) tilt,  //头部偏转角度
   (PlayersFieldPercept::PlayerOnField)  closestObstacle,
  (int)(0) ObsAtLorR,  //障碍物是在左边还是右边，1代表左边，-1代表右边
  (float) ballx,
  (float) bally,
});
