/** A test striker option without common decision */
option(Striker1)
{
//  common_transition
//  {
//
//  }
//  TeamBallModel::ConsideredBall consideredBall;
//  static bool flag = false;
//  static unsigned int time = 0;
//  
//  common_transition
//  {
//      
//	  if(theArmContactModel.status[Arms::left].contact == true || theArmContactModel.status[Arms::right].contact == true)
//		  
//	  {
//		  flag = true;
//		  time = theFrameInfo.time;//theFrameInfo.time为全局的时间，从机器人开始运行代码从0开始，正常的话半场十分钟总共600000毫秒。
//	  }
//	      
//	  if(flag == true)
//	  {
//		
//		  theArmMotionRequest.armMotion[Arms::left] = theArmMotionRequest.armMotion[Arms::right] = ArmMotionRequest::keyFrame;
//		  theArmMotionRequest.armKeyFrameRequest.arms[Arms::left].motion = theArmMotionRequest.armKeyFrameRequest.arms[Arms::right].motion = ArmKeyFrameRequest::back;
//	       
//	  }
//	  
//	  if((theFrameInfo.time - time) > 5000)//从接触障碍手背后持续五秒，可加特殊条件。
//		  flag = false;
//		  
//	  if(flag == false)
//	  {
//		  theArmMotionRequest.armMotion[Arms::left] = theArmMotionRequest.armMotion[Arms::right] = ArmMotionRequest::none;
//	      theArmMotionRequest.armKeyFrameRequest.arms[Arms::left].motion = theArmMotionRequest.armKeyFrameRequest.arms[Arms::right].motion = ArmKeyFrameRequest::useDefault;
//	  }
//  }
//  
  initial_state(start)
  {
    transition
    {
        OUTPUT_TEXT("S1_initial");
		if(theGameInfo.kickOffTeam != theOwnTeamInfo.teamNumber && theBehaviorStatus.activity != BehaviorStatus::preUnpenalized)  //如果敌方发球
			goto waitkickoff;
        if(theGameInfo.kickOffTeam == theOwnTeamInfo.teamNumber && theBehaviorStatus.activity != BehaviorStatus::preUnpenalized)  //如果我方发球
			goto kickoff;
            
		if(theGameInfo.kickOffTeam == theOwnTeamInfo.teamNumber && theBehaviorStatus.activity != BehaviorStatus::preUnpenalized)  //如果惩罚后上场
            goto afterpenalized;
//            goto deng;  //点球就直接跳转
    }
    action
    {
		if(theLibCodeRelease.timeSinceBallWasSeen < 300)
			FollowTheTarget(theBallModel.estimate.position.angle(), theLibCodeRelease.tilt);
		else
			LookLeftAndRight();
		Stand();
    }
  }
  
  state(deng)  //点球开始
{
    transition
    {
        OUTPUT_TEXT("deng");
        if(state_time>2000)
            goto zou;
    }
}

  state(zou)
{
    transition
    {
        OUTPUT_TEXT("deng");
        if(state_time>1000)
             goto kickoff;
    }
    action
    {
        WalkAtRelativeSpeed(Pose2f(0.f, 1.f, 0.f));
    }
}


  state(kickoff)
  {
      transition
      {
          OUTPUT_TEXT("kickoff");
//        if(theLibCodeRelease.timeSinceBallWasSeen > theBehaviorParameters.ballNotSeenTimeOut&&state_time>10000)
//          {
//                  goto searchForBall;
//          }
//          if(state_time>4000)
//              goto strategy;
       if(theLibCodeRelease.between(theBallModel.estimate.position.y(), -36.f, -28.f)
      && theLibCodeRelease.between(theBallModel.estimate.position.x(), 200.f, 220.f))
//      && std::abs(theLibCodeRelease.angleToGoalL) < 4_deg )
      {
          goto S1shoot;
      }
      }
      action
      {
      theHeadControlMode = HeadControl::lookForward;
      if(theLibCodeRelease.timeSinceBallWasSeen<400)
      WalkToTarget(Pose2f(80.f, 30.f, 30.f), Pose2f(0.f, theBallModel.estimate.position.x() - 210.f, theBallModel.estimate.position.y() + 32.f));

      }
  }
  
  state(S1kick)
  {
    transition
    {
        //OUTPUT_TEXT("Striker_kick");
      if(state_time > 3000 || (state_time > 10 && action_done))
      {
            goto strategy;
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
  state(S1shoot)
  {
    transition
    {
        if(theLibCodeRelease.timeSinceBallWasSeen > theBehaviorParameters.ballNotSeenTimeOut)
          {
                  goto searchForBall;
          }
      if(state_time > 3000 || (state_time > 10 && action_done))
      {
          Activity(BehaviorStatus::shoot);
          goto strategy;
      }
    }
    action
    {
      //OUTPUT_TEXT("Striker_kick_action");
     FollowTheTarget(theBallModel.estimate.position.angle(), theLibCodeRelease.tilt);
      Shoot(KickRequest::greatKickForward);
    }
  }
  
  state(waitkickoff)
  {
      transition
      {
          OUTPUT_TEXT("waitkickoff");
          if(state_time>10000)
              goto strategy;
      }
      action
      {
           FollowTheTarget(theBallModel.estimate.position.angle(), theLibCodeRelease.tilt);
           Stand();
      }
  }
  
  state(afterpenalized)  //此State用作以后的功能完善使用，目前没有用到
  {
      transition
      {
          OUTPUT_TEXT("afterpenalized");
          goto strategy;
      }
      action
      {
          theHeadControlMode = HeadControl::lookForward;
      }
  }
state(strategy)
  {
	  transition
	  {
          //OUTPUT_TEXT("Striker1_strategy");
		  if((std::abs(theRobotPose.translation.y()) > 3000 || std::abs(theRobotPose.translation.x()-1000) > 3500) &&
                        !(theLibCodeRelease.timeSinceBallWasSeen < 400 ))
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
        //theHeadControlMode = HeadControl::lookLeftAndRight;
        S1Action();
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
        S1Search();
    }
  }
  
state(goToArea)  //走到指定区域
  {
    transition
    {
        //OUTPUT_TEXT("Striker1_goToArea_t");
        if(theLibCodeRelease.timeSinceBallWasSeen < 400 && theBallModel.estimate.position.norm()<250)
            goto strategy;
        if(!(std::abs(theRobotPose.translation.y()) > 3000 || std::abs(theRobotPose.translation.x()-2250) > 2100))
            {
                goto strategy;
            }
    }
    action
    {
      //OUTPUT_TEXT("Striker1_goToArea_a");
      theHeadControlMode = HeadControl::lookLeftAndRight;
      WalkToDestination(Pose2f(60.f, 20.f, 20.f), Pose2f(-theRobotPose.rotation,  -(theRobotPose.translation.x() - 2000.f), -(theRobotPose.translation.y())), true);
    }
  }

}
