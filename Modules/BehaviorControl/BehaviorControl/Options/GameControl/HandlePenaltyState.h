/** Handle penalty state (and the actions to be performed after leaving the penalty state).
 *   This option is one level higher than the main game state handling as penalties
 *   might occur in most game states. */
option(HandlePenaltyState)
{
  /** By default, the robot is not penalized and plays soccer according to the current game state.
  The chestbutton has to be pushed AND released to manually penalize a robot */
  initial_state(notPenalized)
  {
    transition
    {
      if(theRobotInfo.penalty != PENALTY_NONE)
        goto penalized;
    }
    action
    {
      //OUTPUT_TEXT("HandlePenaltyState_notPenalized_action");
      //theHeadControlMode = HeadControl::lookLeftAndRight;
      HandleGameState();
    }
  }

  /** In case of any penalty, the robots stands still. */
  state(penalized)
  {
    transition
    {
      if(theRobotInfo.penalty == PENALTY_NONE)
        goto preUnpenalize;
    }
    action
    {
      PlaySound("penalized.wav");
      //OUTPUT_TEXT("HandlePenaltyState_penalized_action");
      theHeadControlMode = HeadControl::lookForward;
      SpecialAction(SpecialActionRequest::standHigh);
    }
  }

  state(preUnpenalize)
  {
    transition
    {
      if(theRobotInfo.penalty != PENALTY_NONE)
        goto penalized;
      else if(theGameInfo.state == STATE_INITIAL || state_time > 500)
      {
           switch(theRobotInfo.number)
            {
            case 1: goto KeepergoToField;
			case 2: goto  notPenalized;//notPenalized;//Striker1goToField;
			case 3: goto Defender1goToField;
			case 4: goto Defender2goToField;
			case 5: goto Striker2goToField;
            }		
      }
    }
    action
    {
      PlaySound("notPenalized.wav");
      
      //OUTPUT_TEXT("HandlePenaltyState_preUnpenalize_action");
      theHeadControlMode = HeadControl::lookForward;
      Stand();
    }
  }
  
  state(KeepergoToField)
  {
	  transition
	  {
          //OUTPUT_TEXT("HandlePenaltyState_KeepergoToField_transition");
//		  if((std::abs(theRobotPose.rotation) < 5_deg && std::abs(theRobotPose.translation.y()) < 100 && 
//                            std::abs((theRobotPose.translation.x() + 4200)) <100) || theLibCodeRelease.isMovedBall == true)  
			goto notPenalized;
	  }
	  action
	  {
		  LookForward();
//		  WalkToDestination(Pose2f(100.f,100.f,100.f),Pose2f(-theRobotPose.rotation,-(theRobotPose.translation.x() + 4200),-theRobotPose.translation.y()));
	  }
  }
  state(Striker1goToField)
  {
	  transition
	  {
		  if(state_time>14000)
			goto beforeNotPenalized;
        if(theLibCodeRelease.timeSinceBallWasSeen < 400)
            goto notPenalized;
	  }
	  action
	  {
          Activity(BehaviorStatus::preUnpenalized);
		  theHeadControlMode = HeadControl::lookLeftAndRight;
		   WalkAtRelativeSpeed(Pose2f(0.f, 0.9, 0.f));
      }
  }
  
  state(beforeNotPenalized)
  {
      transition
      {
          if(state_time>4000)
              goto notPenalized;
        if(theLibCodeRelease.timeSinceBallWasSeen < 400)
            goto notPenalized;
      }
      action
      {
          theHeadControlMode = HeadControl::lookLeftAndRight;
          SpecialAction(SpecialActionRequest::standHigh);
      }
  }
  state(Defender1goToField)
  {
	  transition
	  {
//		  if((std::abs(theRobotPose.rotation) < 5_deg && std::abs(theRobotPose.translation.y()) < 100 && 
//                            std::abs((theRobotPose.translation.x() + 2000)) <100) || theLibCodeRelease.isMovedBall == true || theLibCodeRelease.timeSinceBallWasSeen < 300)  
			goto notPenalized;
	  }
	  action
	  {
		  LookForward();
//		  WalkToDestination(Pose2f(100.f,100.f,100.f),Pose2f(-theRobotPose.rotation,-(theRobotPose.translation.x() +2000),-theRobotPose.translation.y()));
	  }
  }
  
  state(Defender2goToField)
  {
	  transition
	  {
//		  if((std::abs(theRobotPose.rotation) < 5_deg && std::abs(theRobotPose.translation.y()) < 100 && 
//                            std::abs((theRobotPose.translation.x() + 2900)) <100) || theLibCodeRelease.isMovedBall == true || theLibCodeRelease.timeSinceBallWasSeen < 300)  
			goto notPenalized;
	  }
	  action
	  {
		  LookForward();
//		  WalkToDestination(Pose2f(100.f,100.f,100.f),Pose2f(-theRobotPose.rotation,-(theRobotPose.translation.x() +2900),-theRobotPose.translation.y()));
	  }
  }
  state(Striker2goToField)
  {
	  transition
	  {
		  if(state_time>10000)  
			goto beforeNotPenalized;
	  }
	  action
	  {
		  theHeadControlMode = HeadControl::lookLeftAndRight;
		   WalkAtRelativeSpeed(Pose2f(0.f, 0.9, 0.f));
      }
  }
}
