/*
 * 
 */
option(S1Action)
{
    common_transition
    {
         if(!theTeamBallModel.isValid)
              {
                  goto lostBall;
              }
    }
    
   initial_state(start)
   {
       transition
       {
           OUTPUT_TEXT("transition");
        if(theLibCodeRelease.timeSinceBallWasSeen < 400 && theBallModel.estimate.position.norm()<5000)
            goto attack;
        if(theTeamBallModel.position.x()<-1000)
        {
            goto waitForSelfBall;
        }
        else  if(theTeamBallModel.position.x()>-1000)  //如果球在对方半场
        {
            
            if(theLibCodeRelease.timeSinceBallWasSeen < 400 ) //如果自己看到了球 
            {
                if(theLibCodeRelease.striker2.isPenalized || !theLibCodeRelease.striker2.isUpright)  //如果S2不在线，则直接开始进攻
                        goto attack;
                            
                if( theFrameInfo.getTimeSince(theLibCodeRelease.striker2.theBallModel.timeWhenLastSeen) < 500 &&
                                (float)std::sqrt(std::pow(theTeamBallModel.position.x()-theRobotPose.translation.x(),2) +
                                std::pow(theTeamBallModel.position.y()-theRobotPose.translation.y(),2))  - (float)std::sqrt(std::pow(theTeamBallModel.position.x()-theLibCodeRelease.striker2.theRobotPose.translation.x(),2) +
                                std::pow(theTeamBallModel.position.y()-theLibCodeRelease.striker2.theRobotPose.translation.y(),2)) < 10)  //球离S1的距离-球到S2的距离)
                        goto attack;
                if(theFrameInfo.getTimeSince(theLibCodeRelease.striker2.theBallModel.timeWhenLastSeen) > 500)  //S2没有看到球
                        goto attack;
                goto waitForBall;
            }
                        
            if(theLibCodeRelease.timeSinceBallWasSeen > 400 )  //如果没有看到球
            {
                //OUTPUT_TEXT("noball");
                if(!theLibCodeRelease.striker2.isPenalized && theLibCodeRelease.striker2.isUpright &&    //如果S2在线
                                  theFrameInfo.getTimeSince(theLibCodeRelease.striker2.theBallModel.timeWhenLastSeen) < 500 &&  //S2看到了球
                                  theLibCodeRelease.striker2.theBallModel.estimate.position.norm() < 700)  //S2离球的距离小于600，证明S2要attack了
                {
                                   goto waitS2attack;
                }
                else 
                {
//                    if(!(std::abs(theRobotPose.rotation-(std::atan((theRobotPose.translation.y()-
//                                            theTeamBallModel.position.y())/(theRobotPose.translation.x()-theTeamBallModel.position.x()))+180_deg)) < 5_deg  ||
//                                            std::abs(theRobotPose.rotation-(std::atan((theRobotPose.translation.y()-
//                                            theTeamBallModel.position.y())/(theRobotPose.translation.x()-theTeamBallModel.position.x()))-180_deg)) < 5_deg  ||
//                                            std::abs(theRobotPose.rotation-(std::atan((theRobotPose.translation.y()-
//                                            theTeamBallModel.position.y())/(theRobotPose.translation.x()-theTeamBallModel.position.x())))) < 5_deg ||
//                                            std::abs(theRobotPose.rotation-(std::atan((theRobotPose.translation.y()-
//                                            theTeamBallModel.position.y())/(theRobotPose.translation.x()-theTeamBallModel.position.x())))) < 5_deg ))
                    if(!(std::abs(std::atan(theLibCodeRelease.bally / theLibCodeRelease.ballx)) < 18_deg && theLibCodeRelease.ballx > 0.f ))
                            goto turnToTeamBallL;
                    else goto walkToTeamBall;
                                        
                }
            }
        }
       }
       action
       {
           //Activity(BehaviorStatus::acting);
           //theHeadControlMode = HeadControl::lookForward;
       }
   }
   
     state(waitS2attack)
  {
      transition
      {
          if(state_time>2000)
              goto start;
      }
      action
      {
          theHeadControlMode = HeadControl::lookForward;
           if(theRobotPose.translation.y()>0)
                    WalkToDestination(Pose2f(100.f, 20.f, 20.f), Pose2f(-(theRobotPose.rotation),  0.f, -(theRobotPose.translation.y()-1200)));
            else WalkToDestination(Pose2f(100.f, 20.f, 20.f), Pose2f(-(theRobotPose.rotation),  0.f, -(theRobotPose.translation.y()+1200)));
      }
  }
   state(walkToTeamBall)
   {
       transition
       {
        if(theLibCodeRelease.timeSinceBallWasSeen < 400)
        {
            goto start;
        }
        if((float)std::sqrt(std::pow(theTeamBallModel.position.x()-theRobotPose.translation.x(),2) +
                            std::pow(theTeamBallModel.position.y()-theRobotPose.translation.y(),2))<800.f || state_time>10000)  //走向teamBall，如果距离小于800或者时间大于10s
            goto actionSearchBall;   //则原地转圈找球
       }
       action
       {
            theHeadControlMode = HeadControl::lookLeftAndRight;
            WalkToDestination(Pose2f(100.f, 30.f, 30.f), Pose2f(-(theRobotPose.rotation),  -(theRobotPose.translation.x()-theTeamBallModel.position.x()), -(theRobotPose.translation.y()-theTeamBallModel.position.y())));     
        }
   }
   
    state(actionSearchBall)
  {
    transition
    {
         //OUTPUT_TEXT("TurnAndSearchBall_start");
          if(theLibCodeRelease.timeSinceBallWasSeen < 400)
           {
                goto start;
           }
         if(state_time>10000 ||  !theTeamBallModel.isValid)
         {
             goto lostBall;
         }
    }
    action
    {
      theHeadControlMode = HeadControl::lookForward;
      WalkAtRelativeSpeed(Pose2f(0.5, 0.f, 0.f)); 
    }
  }
  
   state(attack)
  {
      transition
      {
          //OUTPUT_TEXT("S1Action_attack");
          if(theLibCodeRelease.timeSinceBallWasSeen > theBehaviorParameters.ballNotSeenTimeOut || action_aborted)
          {
                  goto lostBall;
          }
          if(action_done)
              {
                  if((theLibCodeRelease.globalballx<4500.f&&
                        theLibCodeRelease.globalballx>3500.f&&theLibCodeRelease.globalbally<700.f&&theLibCodeRelease.globalballx>-700.f))
                      goto kick;
                  else
                    goto shoot;
              }
      }
      action
      {
          //theHeadControlMode = HeadControl::lookForward;
          //WalkToDestination(Pose2f(100.f, 100.f, 100.f), Pose2f(theBallModel.estimate.position.angle(), 0.f, 0.f));
          ReadyAttack();
      }
  }
  
  state(waitForBall)
  {
      transition
      {
          //OUTPUT_TEXT("S1Action_waitForBall");
          if(state_time>1000)
              goto start;
      }
      action
      {
          FollowTheTarget(theBallModel.estimate.position.angle(), theLibCodeRelease.tilt);
          if(theRobotPose.translation.y()>0)
                        WalkToDestination(Pose2f(100.f, 30.f, 30.f), Pose2f(-(theRobotPose.rotation),  -(theRobotPose.translation.x()-theTeamBallModel.position.x()), -(theRobotPose.translation.y()-600.f)));
          else WalkToDestination(Pose2f(100.f, 30.f, 30.f), Pose2f(-(theRobotPose.rotation),  -(theRobotPose.translation.x()-theTeamBallModel.position.x()), -(theRobotPose.translation.y()+600.f)));
      }
  }
  

  
  state(waitForSelfBall)
  {
      transition
      {
          //OUTPUT_TEXT("S1Action_waitForSelfBall");
          if(state_time>2000)
              goto start;
      }
      action
      {
            theHeadControlMode = HeadControl::lookForward;
            WalkToDestination(Pose2f(100.f, 30.f, 30.f), Pose2f(-(theRobotPose.rotation-180_deg),  (theRobotPose.translation.x()-2800.f), (theRobotPose.translation.y()-theTeamBallModel.position.y())), true);
      }
  }
  
 state(turnToBall)
  {
    transition
    {
	  //OUTPUT_TEXT("S1Action_turnToBall");
	  if(theLibCodeRelease.timeSinceBallWasSeen > theBehaviorParameters.ballNotSeenTimeOut)
        goto lostBall;
      if(std::abs(theBallModel.estimate.position.angle()) < 5_deg)
        goto start;
	  
    }
    action
    {
	  //OUTPUT_TEXT("Striker_turnToBall_action");
      theHeadControlMode = HeadControl::lookForward;
      WalkToDestination(Pose2f(100.f, 30.f, 30.f), Pose2f(theBallModel.estimate.position.angle(), 0.f, 0.f));
    }
  }
  
  state(turnToTeamBallL)
  {
      transition
      {
          if(action_done)
              goto start;
          if(action_aborted)
              goto lostBall;
      }
      action
      {
          TurnToTeamBall();
      }
  }
  
  state(kick)
  {
    transition
    {
        OUTPUT_TEXT(theLibCodeRelease.globalballx);
      if(state_time > 3000 || (state_time > 10 && action_done))
      {
            goto start;
      }
    }
    action
    {
      //OUTPUT_TEXT("Striker_kick_action");
      FollowTheTarget(theBallModel.estimate.position.angle(), theLibCodeRelease.tilt);
      InWalkKick(WalkKickVariant(WalkKicks::forward, Legs::left), 
                                Pose2f((float)0, theBallModel.estimate.position.x() - 160.f, theBallModel.estimate.position.y() - 55.f));
    }
  }
  
  state(shoot)
  {
    transition
    {
        //OUTPUT_TEXT("Striker_shoot");
        if(theLibCodeRelease.timeSinceBallWasSeen > theBehaviorParameters.ballNotSeenTimeOut)
          {
                  goto lostBall;
          }
      if(state_time > 3000 || (state_time > 10 && action_done))
      {
          Activity(BehaviorStatus::shoot);
          goto start;
      }
    }
    action
    {
      //OUTPUT_TEXT("Striker_kick_action");
     FollowTheTarget(theBallModel.estimate.position.angle(), theLibCodeRelease.tilt);
      Shoot(KickRequest::greatKickForward);
    }
  }
  
  target_state(finish)
  {
      transition
      {
          goto start;
      }
  }
  aborted_state(lostBall)
  {
      transition
      {
          goto start;
      }
  }
  
}

