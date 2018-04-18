/*
 * S1找球策略
 */
option(S1Search)
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
          if(state_time>8000)
              goto searchForBall;
      }
      action
      {
          theHeadControlMode = HeadControl::lookLeftAndRight;
          WalkToDestination(Pose2f(20.f, 50.f, 50.f), Pose2f(0_deg,  -(theRobotPose.translation.x() - theLibCodeRelease.globalballx),
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
           if(theLibCodeRelease.timeSinceBallWasSeen < 400 || theTeamBallModel.isValid)
        {
            goto found;
        }
           //OUTPUT_TEXT("S1Search_NPSwitch");
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
      //OUTPUT_TEXT("S1Search_searchForBall");
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
        TurnAndSearchBall();
    }
  }
  
  state(goToP)
  {
      transition
      {
          //OUTPUT_TEXT("S1Search_goToP");
          if(theLibCodeRelease.timeSinceBallWasSeen < 400)
            {
                goto found;
            }
          if((std::abs(theRobotPose.translation.y() -1200)<600 && std::abs(theRobotPose.translation.x()-3000)<300) || 
                (std::abs(theRobotPose.translation.y() -1200)<600 && std::abs(theRobotPose.translation.x()-2600)<300))
              goto searchForBall;
      }
      action
      {
          theHeadControlMode = HeadControl::lookLeftAndRight;
          if(theLibCodeRelease.striker2.isPenalized || !theLibCodeRelease.striker2.isUpright)
              WalkToDestination(Pose2f(20.f, 50.f, 50.f), Pose2f(90_deg,  -(theRobotPose.translation.x() - 2600.f), -(theRobotPose.translation.y()-1200)), true);
          else WalkToDestination(Pose2f(20.f, 50.f, 50.f), Pose2f(90_deg,  -(theRobotPose.translation.x() - 3000.f), -(theRobotPose.translation.y()-1200)), true);
      }
  }
  
  state(goToN)
  {
      transition
      {
          //OUTPUT_TEXT("S1Search_goToN");
          if(theLibCodeRelease.timeSinceBallWasSeen < 400)
            {
                goto found;
            }
          if((std::abs(theRobotPose.translation.y() +1200)<600 && std::abs(theRobotPose.translation.x()-3000)<300) || 
                (std::abs(theRobotPose.translation.y() +1200)<600 && std::abs(theRobotPose.translation.x()-2600)<300))
              goto searchForBall;
      }
      action
      {
          theHeadControlMode = HeadControl::lookLeftAndRight;
          if(theLibCodeRelease.striker2.isPenalized || !theLibCodeRelease.striker2.isUpright)
              WalkToDestination(Pose2f(20.f, 50.f, 50.f), Pose2f(-90_deg,  -(theRobotPose.translation.x() - 2600.f), -(theRobotPose.translation.y() +1200)), true);
          else WalkToDestination(Pose2f(20.f, 50.f, 50.f), Pose2f(-90_deg,  -(theRobotPose.translation.x() - 3000.f), -(theRobotPose.translation.y() +1200)), true);
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

