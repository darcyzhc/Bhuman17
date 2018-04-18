/*
 * 
 */
option(D2Action)
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
           if(theTeamBallModel.position.x()<0)
              {
//                  if(std::abs(theBallModel.estimate.position.angle()) < 5_deg)
//                    goto turnToTeamBallL;
                        goto waitForSelfBall;
              }
           else  if(theTeamBallModel.position.x()>0)  //如果球在对方半场
                {
                    if(theLibCodeRelease.timeSinceBallWasSeen < 400 ) //如果自己看到了球 
                        {
                            if(theLibCodeRelease.striker2.isPenalized || !theLibCodeRelease.striker2.isUpright)  //如果S2不在线，则直接开始进攻
                                    goto attack;
                            
                            if( theFrameInfo.getTimeSince(theLibCodeRelease.striker2.theBallModel.timeWhenLastSeen) < 500 &&
                                    (float)std::sqrt(std::pow(theTeamBallModel.position.x()-theRobotPose.translation.x(),2) +
                                    std::pow(theTeamBallModel.position.y()-theRobotPose.translation.y(),2))  - (float)std::sqrt(std::pow(theTeamBallModel.position.x()-theLibCodeRelease.striker2.theRobotPose.translation.x(),2) +
                                    std::pow(theTeamBallModel.position.y()-theLibCodeRelease.striker2.theRobotPose.translation.y(),2)) < 100)  //球离S1的距离-球到S2的距离)
                                        goto attack;
                            if(theFrameInfo.getTimeSince(theLibCodeRelease.striker2.theBallModel.timeWhenLastSeen) > 500)  //S2没有看到球
                                        goto attack;
                            goto waitForBall;
                        }
                        
                    if(theLibCodeRelease.timeSinceBallWasSeen > 400 )  //如果没有看到球
                        {
                            if(!theLibCodeRelease.striker2.isPenalized && theLibCodeRelease.striker2.isUpright &&    //如果S2在线
                                  theFrameInfo.getTimeSince(theLibCodeRelease.striker2.theBallModel.timeWhenLastSeen) < 500 &&  //S2看到了球
                                 (float)std::sqrt(std::pow(theTeamBallModel.position.x()-theLibCodeRelease.striker2.theRobotPose.translation.x(),2) +
                                    std::pow(theTeamBallModel.position.y()-theLibCodeRelease.striker2.theRobotPose.translation.y(),2)) < 600)  //S2离球的距离小于600，证明S2要attack了
                                {
                                    if(theRobotPose.translation.y()>0)
                                        WalkToDestination(Pose2f(100.f, 100.f, 100.f), Pose2f(-(theRobotPose.rotation),  0.f, -(theRobotPose.translation.y()-1100)));
                                    else WalkToDestination(Pose2f(100.f, 100.f, 100.f), Pose2f(-(theRobotPose.rotation),  0.f, -(theRobotPose.translation.y()+1100)));
                                }
                            else 
                                {
                                      if(!(std::abs(theRobotPose.rotation-(std::atan((theRobotPose.translation.y()-
                                            theTeamBallModel.position.y())/(theRobotPose.translation.x()-theTeamBallModel.position.x()))+180_deg)) < 5_deg  ||
                                            std::abs(theRobotPose.rotation-(std::atan((theRobotPose.translation.y()-
                                            theTeamBallModel.position.y())/(theRobotPose.translation.x()-theTeamBallModel.position.x()))-180_deg)) < 5_deg  ||
                                            std::abs(theRobotPose.rotation-(std::atan((theRobotPose.translation.y()-
                                            theTeamBallModel.position.y())/(theRobotPose.translation.x()-theTeamBallModel.position.x())))) < 5_deg ||
                                            std::abs(theRobotPose.rotation-(std::atan((theRobotPose.translation.y()-
                                            theTeamBallModel.position.y())/(theRobotPose.translation.x()-theTeamBallModel.position.x())))) < 5_deg ))
                                                goto turnToTeamBallL;
                                    else WalkToDestination(Pose2f(100.f, 100.f, 100.f), Pose2f(0.f,  (float)std::sqrt(std::pow(theTeamBallModel.position.x()-theRobotPose.translation.x(),2) +
                                        std::pow(theTeamBallModel.position.y()-theRobotPose.translation.y(),2)), 0.f));
                                        
                                }
                        }
                }
       }
       action
       {
           
       }
   }
   
   state(attack)
  {
      transition
      {
          OUTPUT_TEXT("D2Action_attack");
          if(theLibCodeRelease.timeSinceBallWasSeen > theBehaviorParameters.ballNotSeenTimeOut || action_aborted)
          {
                  goto lostBall;
          }
          if(action_done)
              goto shoot;
      }
      action
      {
          theHeadControlMode = HeadControl::lookForward;
          //WalkToDestination(Pose2f(100.f, 100.f, 100.f), Pose2f(theBallModel.estimate.position.angle(), 0.f, 0.f));
          ReadyAttack();
      }
  }
  
  state(waitForBall)
  {
      transition
      {
          OUTPUT_TEXT("D2Action_waitForBall");
          if(state_time>1000)
              goto start;
      }
      action
      {
          if(theRobotPose.translation.y()>0)
                        WalkToDestination(Pose2f(100.f, 100.f, 100.f), Pose2f(-(theRobotPose.rotation),  -(theRobotPose.translation.x()-theTeamBallModel.position.x()), -(theRobotPose.translation.y()-1100)));
          else WalkToDestination(Pose2f(100.f, 100.f, 100.f), Pose2f(-(theRobotPose.rotation),  -(theRobotPose.translation.x()-theTeamBallModel.position.x()), -(theRobotPose.translation.y()+1100)));
      }
  }
  
  state(waitForSelfBall)
  {
      transition
      {
          OUTPUT_TEXT("D2Action_waitForSelfBall");
          if(state_time>1000)
              goto start;
      }
      action
      {
            WalkToDestination(Pose2f(100.f, 100.f, 100.f), Pose2f(-(theRobotPose.rotation-180_deg),  (theRobotPose.translation.x()-3000.f), (theRobotPose.translation.y()-theTeamBallModel.position.y())));
      }
  }
  
 state(turnToBall)
  {
    transition
    {
	  OUTPUT_TEXT("D2Action_turnToBall");
	  if(theLibCodeRelease.timeSinceBallWasSeen > theBehaviorParameters.ballNotSeenTimeOut)
        goto lostBall;
      if(std::abs(theBallModel.estimate.position.angle()) < 5_deg)
        goto start;
	  
    }
    action
    {
	  //OUTPUT_TEXT("Striker_turnToBall_action");
      theHeadControlMode = HeadControl::lookForward;
      WalkToDestination(Pose2f(100.f, 50.f, 50.f), Pose2f(theBallModel.estimate.position.angle(), 0.f, 0.f));
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
        OUTPUT_TEXT("Defender2_kick");
      if(state_time > 3000 || (state_time > 10 && action_done))
      {
            goto start;
      }
    }
    action
    {
      //OUTPUT_TEXT("Striker_kick_action");
      theHeadControlMode = HeadControl::lookForward;
      InWalkKick(WalkKickVariant(WalkKicks::forward, Legs::left), 
                                Pose2f((float)0, theBallModel.estimate.position.x() - 160.f, theBallModel.estimate.position.y() - 55.f));
    }
  }
  
  state(shoot)
  {
    transition
    {
        OUTPUT_TEXT("D2_shoot");
        OUTPUT_TEXT(theBallModel.estimate.position.y());
      if(state_time > 3000 || (state_time > 10 && action_done))
      {
              goto start;
      }
    }
    action
    {
      //OUTPUT_TEXT("Striker_kick_action");
      theHeadControlMode = HeadControl::lookForward;
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

