/** The root option that controls the behavior before the robot actually starts to play */
option(Soccer)
{
/*
 * theArmMotionRequest: An instance of class  ArmMotionRequest declared in ArmMotionRequest.h, which is instantiated in BehaviorControl.h:151
 * theArmMotionRequest.armMotion: Enum indexed array, indexed type: (Arms) Arm, datatype:(ArmMotionRequest) ArmRequest      
 * Arms: namespace      Arm: enum type
 * theHeadControlMode: An instance of enum type declared in struct type HeadControl in HeadControl.h, which is instantiated in HeadControl.h
 */
  common_transition
  {
    //OUTPUT_TEXT("Soccer_common_transition");
    theArmMotionRequest.armMotion[Arms::left] = ArmMotionRequest::none;   
    theArmMotionRequest.armMotion[Arms::right] = ArmMotionRequest::none;
    theHeadControlMode = HeadControl::none;
    if(!theCameraStatus.ok)  //摄像头状态
    {
        goto sitDown;
    }
      
  }

  /** Initially, all robot joints are off until the chest button is pressed. */
  /*
   enum Mode
  {
    physicalRobot,
    remoteRobot,
    simulatedRobot,
    logfileReplay,
  }
   * SystemCall: A class  defined in SystemCall.h 
   * getMode(): A static method in SystemCall, return a enum type Mode defined in SystemCall
   */
  initial_state(playDead)
  {
    transition
    {
        //OUTPUT_TEXT("Soccer_playDead_transition");
      if(SystemCall::getMode() == SystemCall::simulatedRobot)  //如果是模拟，则不用等待按下胸口按钮来开始
      {
          goto simRobotStandHigh; // Don't wait for the button in SimRobot
      }
        
      if(action_done) // chest button pressed and released   
      {
         
          goto standUp;
      }
        
      // Skip playDead state at a restart after a crash
      //getSettings() returns static thread_local Settings* theSettings
      else if(Global::getSettings().recover)
      {
          
          goto standUp;
      }
        
    }
    action
    {
      //OUTPUT_TEXT("Soccer_playDead_action");
      Activity(BehaviorStatus::unknown);  //设置当前活动状态为unknown
      SpecialAction(SpecialActionRequest::playDead);  //设置特殊动作，共有一下6种类型：
    // playDead,
    //sitDown,
    //stand,
    //standHigh,
    //standHighLookUp,
    //getUpEngineDummy
      ButtonPressedAndReleased(KeyStates::chest, 1000, 0);  //等待胸前按钮按下，按下时间为0-1000ms有效
    }
  }

  state(simRobotStandHigh)
  {
    transition
    {
      if(action_done)
      {
          goto playSoccer;
      }
        
    }
    action
    {
      Activity(BehaviorStatus::unknown);
      LookForward();
      SpecialAction(SpecialActionRequest::standHigh);
       
    }
  }

  /** The robot stands up and starts to play when stand was executed. */
  state(standUp)
  {
    transition
    {
      if(action_done)
        goto playSoccer;
    }
    action
    {
      Activity(BehaviorStatus::gettingUp);
      LookForward();
      Stand();
    }
  }

  /**
   * The main state that triggers the actual soccer behavior.
   * It also checks whether the chest button was pressed.
   */
  state(playSoccer)
  {
    transition
    {
      if(action_done) // chest button pressed and released once
        goto waitForSecondButtonPress;
    }
    action
    {
      HandlePenaltyState();
      HeadControl();
      ButtonPressedAndReleased(KeyStates::chest, 1000, 200);
    }
  }

  /** The following two states check whether the chest button is quickly pressed another two times. */
  state(waitForSecondButtonPress)
  {
    transition
    {
      if(action_done) // chest button pressed and released for the second time
        goto waitForThirdButtonPress;
      else if(action_aborted) // too slow -> abort
        goto playSoccer;
    }
    action
    {
      HandlePenaltyState();
      HeadControl();
      ButtonPressedAndReleased(KeyStates::chest, 1000, 200);
    }
  }

  state(waitForThirdButtonPress)
  {
    transition
    {
      if(action_done) // chest button pressed and released for the third time
        goto sitDown;
      else if(action_aborted) // too slow -> abort
        goto playSoccer;
    }
    action
    {
      HandlePenaltyState();
      HeadControl();
      ButtonPressedAndReleased(KeyStates::chest, 1000, 200);
    }
  }

  /** The robot sits down and turns off all joints afterwards. */
  state(sitDown)
  {
    transition
    {
      if(action_done)
        goto playDeadDoNotRecover;
    }
    action
    {
      Activity(BehaviorStatus::unknown);
      LookForward();
      SpecialAction(SpecialActionRequest::sitDown);
    }
  }

  /** After pressing the chest button thrice we don't want the robot to recover */
  state(playDeadDoNotRecover)
  {
    transition
    {
      if(action_done)// chest button pressed and released
        goto standUp;
    }
    action
    {
      Activity(BehaviorStatus::unknown);
      SpecialAction(SpecialActionRequest::playDead);
      ButtonPressedAndReleased(KeyStates::chest, 1000, 0);
    }
  }
}
