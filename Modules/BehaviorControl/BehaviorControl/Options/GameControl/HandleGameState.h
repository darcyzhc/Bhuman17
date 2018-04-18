/** Triggers the options for the different game states.
 *  This option also invokes the get up behavior after a fall, as this is needed in most game states.
 */
option(HandleGameState)
{
  /** As game state changes are discrete external events and all states are independent of each other,
      a common transition can be used here. */
  common_transition
  {
    //OUTPUT_TEXT("HandleGameState_common_transition");
    if(theGameInfo.state == STATE_INITIAL)
    {
        //OUTPUT_TEXT("HandleGameState_STATE_INITIAL");
        goto initial;
    }
      
    if(theGameInfo.state == STATE_FINISHED)
    {
        //OUTPUT_TEXT("HandleGameState_STATE_FINISHED");
        goto finished;
    }
      

    if(theFallDownState.state == FallDownState::fallen)
    {
        //OUTPUT_TEXT("HandleGameState_FallDownState::fallen");
        goto getUp;
    }
      

    if(theGameInfo.state == STATE_READY)
    {
        //OUTPUT_TEXT("HandleGameState_STATE_READY");
        goto ready;
    }
      
    if(theGameInfo.state == STATE_SET)
    {
        //OUTPUT_TEXT("HandleGameState_STATE_SET");
        goto set;
    }
      
    if(theGameInfo.state == STATE_PLAYING)
    {
        //OUTPUT_TEXT("HandleGameState_STATE_PLAYING");
        goto playing;
    }
      
  }

  /** Stand still and wait. */
  initial_state(initial)
  {
    action
    {
      //OUTPUT_TEXT("HandleGameState_initial_action");
      SetHeadPanTilt(0.f, 0.f, 150_deg);
      SpecialAction(SpecialActionRequest::standHigh);
    }
  }

  /** Stand still and wait. If somebody wants to implement cheering moves => This is the place. ;-) */
  state(finished)
  {
    transition
    {
        if(std::abs(theRobotPose.translation.x() + 800.f)<100&&std::abs(theRobotPose.translation.y() - 0.f)<100)
            goto afterFinished;
    }
    action
    {
      WalkToDestination(Pose2f(20.f, 20.f, 20.f), Pose2f(0_deg,  -(theRobotPose.translation.x() + 800.f), -(theRobotPose.translation.y() - 0.f)), true);
      theHeadControlMode = HeadControl::lookForward;
    }
  }

  state(afterFinished)
  {
      transition
      {
          if(std::abs(theRobotPose.rotation)<5_deg)
              goto initial;
      }
      action
      {
          WalkAtRelativeSpeed(Pose2f(0.8, 0.f, 0.f)); 
      }
  }
  
  /** Get up from the carpet. */
  state(getUp)
  {
    action
    {
      //OUTPUT_TEXT("HandleGameState_getUp_action");
      Activity(BehaviorStatus::preUnpenalized);
      GetUp();
    }
  }

  /** Walk to kickoff position. */
  state(ready)
  {
    action
    {
      //OUTPUT_TEXT("HandleGameState_ready_action");
      //ReadyState();
//        if(theRobotInfo.number == 1)
//			KeeperReady();
        if(theRobotInfo.number == 2)
			{
                if(theGameInfo.kickOffTeam != theOwnTeamInfo.teamNumber)
                  Striker1Ready();
                else Striker1kickOffReady();
                
            }
//		if(theRobotInfo.number == 3)
//			ReadyState1();
//	    if(theRobotInfo.number == 4)
//			ReadyState();
		if(theRobotInfo.number == 5)
			Striker2Ready();
    }
  }
  
  /** Stand and look around. */
  state(set)
  {
    action
    {
      Stand();
    }
  }

  /** Play soccer! */
  state(playing)
  {
    action
    {
      //PlayingState();
//      if((std::abs(theLibCodeRelease.globalballx) > 4700 || std::abs(theLibCodeRelease.globalbally) > 3200) && theLibCodeRelease.timeSinceBallWasSeen < 300)
//			{
//                //OUTPUT_TEXT("HandleGameState_playing_action1");
//				Stand();
//				theHeadControlMode = HeadControl::lookLeftAndRight;
//			}
//			else
            PlayingState();
    }
  }
}
