/** A test striker option without common decision */
option(Defender1)
{
//  common_transition
//  {
//
//  }
    initial_state(start)
    {
        transition
        {
            OUTPUT_TEXT("Defender1_start");
            if(state_time > 1000)
              goto strategy;
        }
        action 
        {

        }
    }

state(strategy)
  {
	  transition
	  {
          OUTPUT_TEXT("Defender1_strategy");
		  if((std::abs(theRobotPose.translation.y()) > 3000 || std::abs(theRobotPose.translation.x()+2250) > 2250))
              {
                      goto goToArea;
              }
          if(!theTeamBallModel.isValid || action_aborted)
              {
                  goto searchForBall;
              }
	  }
	  action
	  {
        theHeadControlMode = HeadControl::lookLeftAndRight;
        D1Action();
        //SpecialAction(SpecialActionRequest::standHigh);
      }
  }

 
  
  state(searchForBall)
  {
    transition
    {
      OUTPUT_TEXT("Defender1_searchForBall");
      if(action_done)
          goto strategy;
    }
    action
    {
        D1Search();
    }
  }
  
state(goToArea)  //走到指定区域
  {
    transition
    {
        OUTPUT_TEXT("Defender1_goToArea_t");
        if(!(std::abs(theRobotPose.translation.y()) > 3000 || std::abs(theRobotPose.translation.x()+2250) > 2250))
            {
                goto strategy;
            }
    }
    action
    {
      OUTPUT_TEXT("Defender1_goToArea_a");
      theHeadControlMode = HeadControl::lookForward;
      WalkToDestination(Pose2f(100.f, 100.f, 100.f), Pose2f(-theRobotPose.rotation,  -(theRobotPose.translation.x() - 2000.f), -(theRobotPose.translation.y())), true);
    }
  }

}
