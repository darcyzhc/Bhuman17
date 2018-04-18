/*
 * 
 */
option(D2Search)
{
   initial_state(start)
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
      OUTPUT_TEXT("D2Search_searchForBall");
      if(theLibCodeRelease.timeSinceBallWasSeen < 400 || theTeamBallModel.isValid)
        {
            goto found;
        }
      if(action_done)
          goto found;
      if(action_aborted)
          goto start;
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
          OUTPUT_TEXT("D2Search_goToP");
          if(theLibCodeRelease.timeSinceBallWasSeen < 400)
            {
                goto found;
            }
          if((std::abs(theRobotPose.translation.y() -1200)<30 && std::abs(theRobotPose.translation.x()-3200)<30) || 
                (std::abs(theRobotPose.translation.y() -1200)<30 && std::abs(theRobotPose.translation.x()-2200)<30))
              goto searchForBall;
      }
      action
      {
          theHeadControlMode = HeadControl::lookLeftAndRight;
          if(theLibCodeRelease.striker2.isPenalized || !theLibCodeRelease.striker2.isUpright)
              WalkToDestination(Pose2f(100.f, 100.f, 100.f), Pose2f(-(theRobotPose.rotation),  -(theRobotPose.translation.x() - 2200.f), -(theRobotPose.translation.y()-1200)));
          else WalkToDestination(Pose2f(100.f, 100.f, 100.f), Pose2f(-(theRobotPose.rotation),  -(theRobotPose.translation.x() - 3200.f), -(theRobotPose.translation.y()-1200)));
      }
  }
  
  state(goToN)
  {
      transition
      {
          OUTPUT_TEXT("D2Search_goToN");
          if(theLibCodeRelease.timeSinceBallWasSeen < 400)
            {
                goto found;
            }
          if((std::abs(theRobotPose.translation.y() +1200)<30 && std::abs(theRobotPose.translation.x()-3200)<30) || 
                (std::abs(theRobotPose.translation.y() +1200)<30 && std::abs(theRobotPose.translation.x()-2200)<30))
              goto searchForBall;
      }
      action
      {
          theHeadControlMode = HeadControl::lookLeftAndRight;
          if(theLibCodeRelease.striker2.isPenalized || !theLibCodeRelease.striker2.isUpright)
              WalkToDestination(Pose2f(100.f, 100.f, 100.f), Pose2f(-(theRobotPose.rotation),  -(theRobotPose.translation.x() - 2200.f), -(theRobotPose.translation.y() +1200)));
          else WalkToDestination(Pose2f(100.f, 100.f, 100.f), Pose2f(-(theRobotPose.rotation),  -(theRobotPose.translation.x() - 3200.f), -(theRobotPose.translation.y() +1200)));
      }
  } 
  target_state(found)
  {
      transition
      {
          goto start;
      }
  }
  aborted_state(notFound)
  {
      transition
      {
          goto start;
      }
  }
  
}

