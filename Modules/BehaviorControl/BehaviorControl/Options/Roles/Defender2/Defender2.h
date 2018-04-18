/** A test striker option without common decision */
option(Defender2)
{
//  common_transition
//  {
//
//  }
    initial_state(start)
    {
        transition
        {
            OUTPUT_TEXT("Defender2_start");
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
          OUTPUT_TEXT("Defender2_strategy");
		  if((std::abs(theRobotPose.translation.y()) > 3000 || std::abs(theRobotPose.translation.x()-2250) > 2250))
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
        D2Action();
        //SpecialAction(SpecialActionRequest::standHigh);
      }
  }

 
  
  state(searchForBall)
  {
    transition
    {
      OUTPUT_TEXT("Defender2_searchForBall");
      if(action_done)
          goto strategy;
    }
    action
    {
        D2Search();
    }
  }
  
state(goToArea)  //走到指定区域
  {
    transition
    {
        OUTPUT_TEXT("Defender2_goToArea_t");
        if(std::abs(theRobotPose.rotation)>30_deg)
                goto alignToY;
        if(!(std::abs(theRobotPose.translation.y()) > 3000 || std::abs(theRobotPose.translation.x()-2250) > 2250))
            {
                goto strategy;
            }
    }
    action
    {
      OUTPUT_TEXT("Defender2_goToArea_a");
      theHeadControlMode = HeadControl::lookForward;
      if(std::abs(theRobotPose.rotation)<30_deg)
            WalkToDestination(Pose2f(100.f, 100.f, 100.f), Pose2f(-theRobotPose.rotation,  -(theRobotPose.translation.x() - 2000.f), -theRobotPose.translation.y()));
    }
  }

  state(alignToY)       //对准Y轴正方向，以便更快走向指定地点
  {
    static int Flag=0;      
    transition
    {
        OUTPUT_TEXT("Defender2_alignToY");
        if(Flag)
        {
            Flag=0;
            goto goToArea;
        }
    }
    action
    {
        OUTPUT_TEXT("action");
        if(std::abs(theRobotPose.rotation)>20_deg&&!Flag)
        {   OUTPUT_TEXT("action1");
            if((theRobotPose.rotation)>0_deg)
            {
                OUTPUT_TEXT("action2");
                WalkAtRelativeSpeed(Pose2f(-1.f, 0.f, 0.f));
            }
                
            else if((theRobotPose.rotation)<0_deg)
            {
                OUTPUT_TEXT("action3");
                WalkAtRelativeSpeed(Pose2f(1.f, 0.f, 0.f));
            }
                
        }
        else if(std::abs(theRobotPose.rotation)<20_deg&&!Flag)
        {
            OUTPUT_TEXT("action4");
            Flag=1;
        }
    }
  }
}
