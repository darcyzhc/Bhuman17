/*
 * 原地站立摇头找球，然后旋转120度继续，旋转一周后结束
 */
option(TurnAndSearchBall)
{
  static int turnCount=0; //用于计数找球时旋转的次数
  state(start1)
  {
    transition
    {
         //OUTPUT_TEXT("TurnAndSearchBall_start");
         if(std::abs(theRobotPose.rotation-120_deg)<3_deg || std::abs(theRobotPose.rotation+120_deg)<3_deg || std::abs(theRobotPose.rotation)<5_deg)  //调整好初始角度后开始找球
            {
                turnCount++;
                turnCount=turnCount%4;
                goto standAndTurnLeftAndRight;
            }
    }
    action
    {
      Activity(BehaviorStatus::searchForBall);
      theHeadControlMode = HeadControl::lookForward;
      WalkAtRelativeSpeed(Pose2f(0.8, 0.f, 0.f)); 
    }
  }
  
  initial_state(start)
  {
    transition
    {
         //OUTPUT_TEXT("TurnAndSearchBall_start");
          if(theLibCodeRelease.timeSinceBallWasSeen < 400)
           {
                goto found;
           }
         if(state_time>11000)
         {
             goto notFound;
         }
    }
    action
    {
      Activity(BehaviorStatus::searchForBall);
      theHeadControlMode = HeadControl::lookForward;
      WalkAtRelativeSpeed(Pose2f(0.7, 0.f, 0.f)); 
    }
  }
  
  state(standAndTurnLeftAndRight)  //站立，摇头找球
  {
      transition
      {
          //OUTPUT_TEXT("TurnAndSearchBall_standAndTurnLeftAndRight");
          if(theLibCodeRelease.timeSinceBallWasSeen < 400)
            {
                turnCount=0;
                goto found;
            }
          if(theTeamBallModel.isValid)
            {
                turnCount=0;
                goto notFound;
            }
          if(!turnCount)
              {
                  goto notFound;
              }
          if(state_time>10000)
            {
                  goto turnAround90deg;
            }
      }
      action
      {
          SpecialAction(SpecialActionRequest::standHigh);
          theHeadControlMode = HeadControl::lookLeftAndRight;
      }
  }
  
  state(turnAround90deg )  //旋转90度再找球
  {
      transition
      {
          //OUTPUT_TEXT("TurnAndSearchBall_turnAround90deg");
        if(theLibCodeRelease.timeSinceBallWasSeen < 400)
            {
                turnCount=0;
                goto found;
            }
        if(theTeamBallModel.isValid)
            {
                turnCount=0;
                goto notFound;
            }
        if((std::abs(theRobotPose.rotation-120_deg)<3_deg || std::abs(theRobotPose.rotation+120_deg)<3_deg || std::abs(theRobotPose.rotation)<5_deg) && (state_time>3000) )
              {
                  goto start;
              }
      }
      action
      {
          theHeadControlMode = HeadControl::lookForward;
          WalkAtRelativeSpeed(Pose2f(0.8, 0.f, 0.f)); 
      }
  }
  target_state(found)
  {
      transition
      {
          turnCount=0;
          goto start;
      }
  }
  aborted_state(notFound)
  {
      transition
      {
          turnCount=0;
          goto start;
      }
  }
  
}
