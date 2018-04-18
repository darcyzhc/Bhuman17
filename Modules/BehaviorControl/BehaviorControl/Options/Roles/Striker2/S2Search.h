/*
 * 
 */
option(S2Search)
{
  common_transition
  {
      if(theLibCodeRelease.timeSinceBallWasSeen < 400 || theTeamBallModel.isValid)
        {
            goto found;
        }
      OUTPUT_TEXT("S1Search_common_transition");
  }
  
  initial_state(searchAfterShoot)
  {
      transition
      {
          if(theLibCodeRelease.timeSinceBallWasSeen < 400 || theTeamBallModel.isValid)
        {
            goto found;
        }
          // OUTPUT_TEXT("S1Search_searchAfterShoot");
          if(theBehaviorStatus.activity==BehaviorStatus::ballOut)
              goto searchForBall;
          if(state_time>6500)
              goto searchForBall;
      }
      action
      {
          WalkToDestination(Pose2f(20.f, 20.f, 20.f), Pose2f(0_deg,  -(theRobotPose.translation.x() - theLibCodeRelease.globalballx),
                -(theRobotPose.translation.y() - theLibCodeRelease.globalbally)));
      }
  }
  
   state(start)
   {
       transition
       {
           if(theLibCodeRelease.timeSinceBallWasSeen < 400 || theTeamBallModel.isValid)
        {
            goto found;
        }
           //OUTPUT_TEXT("S1Search_start");
           if(!theTeamBallModel.isValid)
              {
                  if(theRobotPose.translation.y()>0)
                      goto goToP;
                  else goto goToN;
              }
            else goto found;
       }
       action
       {
           Activity(BehaviorStatus::searchForBall);
       }
   }

   state(NPSwitch)
   {
       transition
       {
           if(!theTeamBallModel.isValid)
              {
                  if(theRobotPose.translation.y()>0)
                      goto goToN;
                  else goto goToP;
              }
            else goto found;
       }
       action
       {
           
       }
   }
   
  state(searchForBall)
  {
    transition
    {
      OUTPUT_TEXT("S2Search_searchForBall");
      if(theLibCodeRelease.timeSinceBallWasSeen < 400 || theTeamBallModel.isValid)
        {
            goto found;
        }
      if(action_done)
          goto found;
      if(action_aborted)
          goto NPSwitch;
    }
    action
    {
      //OUTPUT_TEXT("Striker_searchForBall_action");
        TurnAndSearchBall();
    }
  }
  
  state(goToP)
  {
      transition
      {
          OUTPUT_TEXT("S2Search_goToP");
          if(theLibCodeRelease.timeSinceBallWasSeen < 400)
            {
                goto found;
            }
          if((std::abs(theRobotPose.translation.y() -1200)<200 && std::abs(theRobotPose.translation.x()-200)<200) || 
                (std::abs(theRobotPose.translation.y() -1200)<200 && std::abs(theRobotPose.translation.x()-800)<200) || 
                (std::abs(theRobotPose.translation.y() -1200)<200 && std::abs(theRobotPose.translation.x()-2200)<200))
              goto searchForBall;
      }
      action
      {
          theHeadControlMode = HeadControl::lookLeftAndRight;
          if(theLibCodeRelease.striker2.isPenalized || !theLibCodeRelease.striker2.isUpright)
              WalkToDestination(Pose2f(100.f, 100.f, 100.f), Pose2f(-(theRobotPose.rotation),  -(theRobotPose.translation.x() - 2200.f), -(theRobotPose.translation.y()-1200)));
           if(theLibCodeRelease.defender1.status!=2 || theLibCodeRelease.defender2.status!=2)
              WalkToDestination(Pose2f(100.f, 100.f, 100.f), Pose2f(-(theRobotPose.rotation),  -(theRobotPose.translation.x() - 200.f), -(theRobotPose.translation.y() -1200)));
          else WalkToDestination(Pose2f(100.f, 100.f, 100.f), Pose2f(-(theRobotPose.rotation),  -(theRobotPose.translation.x() - 800.f), -(theRobotPose.translation.y()-1200)));
      }
  }
  
  state(goToN)
  {
      transition
      {
          OUTPUT_TEXT("S2Search_goToN");
          if(theLibCodeRelease.timeSinceBallWasSeen < 400)
            {
                goto found;
            }
          if((std::abs(theRobotPose.translation.y() +1200)<200 && std::abs(theRobotPose.translation.x()-200)<200) || 
                (std::abs(theRobotPose.translation.y() +1200)<200 && std::abs(theRobotPose.translation.x()-800)<200) || 
                (std::abs(theRobotPose.translation.y() +1200)<200 && std::abs(theRobotPose.translation.x()-2200)<200))
              goto searchForBall;
      }
      action
      {
          theHeadControlMode = HeadControl::lookLeftAndRight;
          if(theLibCodeRelease.striker2.isPenalized || !theLibCodeRelease.striker2.isUpright)
              WalkToDestination(Pose2f(100.f, 100.f, 100.f), Pose2f(-(theRobotPose.rotation),  -(theRobotPose.translation.x() - 2200.f), -(theRobotPose.translation.y() +1200)));
          if(theLibCodeRelease.defender1.status!=2 || theLibCodeRelease.defender2.status!=2)
              WalkToDestination(Pose2f(100.f, 100.f, 100.f), Pose2f(-(theRobotPose.rotation),  -(theRobotPose.translation.x() - 200.f), -(theRobotPose.translation.y() +1200)));
          else WalkToDestination(Pose2f(100.f, 100.f, 100.f), Pose2f(-(theRobotPose.rotation),  -(theRobotPose.translation.x() - 800.f), -(theRobotPose.translation.y() +1200)));
      }
  } 
  target_state(found)
  {
      transition
      {
          goto searchAfterShoot;
      }
  }
  aborted_state(notFound)
  {
      transition
      {
          goto searchAfterShoot;
      }
  }
  
}

