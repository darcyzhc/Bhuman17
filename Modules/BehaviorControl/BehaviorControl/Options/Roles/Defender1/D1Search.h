/*
 * S1找球策略
 */
option(D1Search)
{
  common_transition
  {
      OUTPUT_TEXT("D1Search_common_transition");
    if(theBehaviorStatus.activity==BehaviorStatus::shoot)
        {
            Activity(BehaviorStatus::search1);
            goto searchAfterShoot;
        }
    
  }
  
  initial_state(searchAfterShoot)
  {
      transition
      {
           OUTPUT_TEXT("D1Search_searchAfterShoot");
          if(state_time>4000)
              goto start;
      }
      action
      {
          WalkToTarget(Pose2f(100.f, 100.f, 100.f), theBallModel.lastPerception);
      }
  }
   state(start)
   {
       transition
       {
           OUTPUT_TEXT("D1Search_start");
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
           OUTPUT_TEXT("D1Search_NPSwitch");
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
      OUTPUT_TEXT("D1Search_searchForBall");
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
          OUTPUT_TEXT("D1Search_goToP");
          if(theLibCodeRelease.timeSinceBallWasSeen < 400)
            {
                goto found;
            }
          if((std::abs(theRobotPose.translation.y() -1200)<50 && std::abs(theRobotPose.translation.x()+3200)<50) || 
                (std::abs(theRobotPose.translation.y() -1200)<50 && std::abs(theRobotPose.translation.x()+2200)<50))
              goto searchForBall;
      }
      action
      {
          if(theLibCodeRelease.striker2.isPenalized || !theLibCodeRelease.striker2.isUpright)
              WalkToDestination(Pose2f(100.f, 100.f, 100.f), Pose2f(90_deg,  -(theRobotPose.translation.x() + 2200.f), -(theRobotPose.translation.y()-1200)), true);
          else WalkToDestination(Pose2f(100.f, 100.f, 100.f), Pose2f(90_deg,  -(theRobotPose.translation.x() + 3200.f), -(theRobotPose.translation.y()-1200)), true);
      }
  }
  
  state(goToN)
  {
      transition
      {
          OUTPUT_TEXT("D1Search_goToN");
          if(theLibCodeRelease.timeSinceBallWasSeen < 400)
            {
                goto found;
            }
          if((std::abs(theRobotPose.translation.y() +1200)<50 && std::abs(theRobotPose.translation.x()+3200)<50) || 
                (std::abs(theRobotPose.translation.y() +1200)<50 && std::abs(theRobotPose.translation.x()+2200)<50))
              goto searchForBall;
      }
      action
      {
          if(theLibCodeRelease.striker2.isPenalized || !theLibCodeRelease.striker2.isUpright)
              WalkToDestination(Pose2f(100.f, 100.f, 100.f), Pose2f(-90_deg,  -(theRobotPose.translation.x() + 2200.f), -(theRobotPose.translation.y() +1200)), true);
          else WalkToDestination(Pose2f(100.f, 100.f, 100.f), Pose2f(-90_deg,  -(theRobotPose.translation.x() + 3200.f), -(theRobotPose.translation.y() +1200)), true);
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

