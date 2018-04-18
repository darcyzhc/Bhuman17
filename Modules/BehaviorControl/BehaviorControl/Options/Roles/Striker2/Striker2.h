/** A test striker option without common decision */
option(Striker2)
{
//  common_transition
//  {
//
//  }
  TeamBallModel::ConsideredBall consideredBall;
  static bool flag = false;
  static unsigned int time = 0;
  
  common_transition
  {
	  if(theArmContactModel.status[Arms::left].contact == true || theArmContactModel.status[Arms::right].contact == true)
		  
	  {
		  flag = true;
		  time = theFrameInfo.time;//theFrameInfo.time为全局的时间，从机器人开始运行代码从0开始，正常的话半场十分钟总共600000毫秒。
	  }
	      
	  if(flag == true)
	  {
		
		  theArmMotionRequest.armMotion[Arms::left] = theArmMotionRequest.armMotion[Arms::right] = ArmMotionRequest::keyFrame;
		  theArmMotionRequest.armKeyFrameRequest.arms[Arms::left].motion = theArmMotionRequest.armKeyFrameRequest.arms[Arms::right].motion = ArmKeyFrameRequest::back;
	       
	  }
	  
	  if((theFrameInfo.time - time) > 5000)//从接触障碍手背后持续五秒，可加特殊条件。
		  flag = false;
		  
	  if(flag == false)
	  {
		  theArmMotionRequest.armMotion[Arms::left] = theArmMotionRequest.armMotion[Arms::right] = ArmMotionRequest::none;
	      theArmMotionRequest.armKeyFrameRequest.arms[Arms::left].motion = theArmMotionRequest.armKeyFrameRequest.arms[Arms::right].motion = ArmKeyFrameRequest::useDefault;
	  }
  }
  
    initial_state(start)
    {
        transition
        {
            //OUTPUT_TEXT("Striker1_start");
            if(state_time > 500)
              ;//goto strategy;
            if((std::abs(theRobotPose.translation.y()) > 3000 || std::abs(theRobotPose.translation.x()) > 2250))
              {
                  ;//goto goToArea;
              }
        }
        action 
        {
        OUTPUT_TEXT("mark");
        OUTPUT_TEXT(theTeamBallModel.position.x());
        OUTPUT_TEXT(theLibCodeRelease.striker2.theRobotPose.translation.x());
            //theHeadControlMode = HeadControl::lookForward;
        }
    }

state(strategy)
  {
	  transition
	  {
          //OUTPUT_TEXT("Striker1_strategy");

          if(!theTeamBallModel.isValid || action_aborted)
              {
                  goto searchForBall;
              }
	  }
	  action
	  {
        //theHeadControlMode = HeadControl::lookLeftAndRight;
        S2Action();
        //SpecialAction(SpecialActionRequest::standHigh);
      }
  }

 
  
  state(searchForBall)
  {
    transition
    {
      //OUTPUT_TEXT("Striker1_searchForBall");
      if(action_done)
          goto strategy;
    }
    action
    {
        S2Search();
    }
  }
  
state(goToArea)  //走到指定区域
  {
    transition
    {
        //OUTPUT_TEXT("Striker1_goToArea_t");
        if(!(std::abs(theRobotPose.translation.y()) > 3000 || std::abs(theRobotPose.translation.x()) > 2250))
            {
                goto strategy;
            }
    }
    action
    {
      //OUTPUT_TEXT("Striker1_goToArea_a");
      theHeadControlMode = HeadControl::lookLeftAndRight;
      WalkToDestination(Pose2f(60.f, 20.f, 20.f), Pose2f(-theRobotPose.rotation,  -(theRobotPose.translation.x() - 1000.f), -(theRobotPose.translation.y())), true);
    }
  }

}
