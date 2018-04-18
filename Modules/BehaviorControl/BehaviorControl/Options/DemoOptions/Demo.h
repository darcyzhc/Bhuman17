/**
 * @file Demo.h
 *
 * @author <a href="mailto:jesse@tzi.de">Jesse Richter-Klug</a>
 */

option(Demo)
{
  common_transition
  {
      //OUTPUT_TEXT("Demo_common_transition");
    switch(theLibDemo.demoGameState)
    {
      case LibDemo::waving:
        goto waving;
      case LibDemo::normal:
        goto normal;
      default:
        OUTPUT_TEXT("state false!");
        FAIL("Unknown demo game state.");
        ASSERT(false);
        break;
    }
  }

  initial_state(normal)
  {
    action
    {
        //TestStriker();
      //OUTPUT_TEXT("Demo_normal_action");
        if(theRobotInfo.number == 1)
			Keeper();
		if(theRobotInfo.number == 2)
			Striker1();
		if(theRobotInfo.number == 3)
			Defender1();
	    if(theRobotInfo.number == 4)
			Defender2();
		if(theRobotInfo.number == 5)
			Striker2();
      //theHeadControlMode = HeadControl::lookForward;
    }
  }

  state(waving)
  {
    action
    {
      OUTPUT_TEXT("Demo_waving_action");
      //Activity(BehaviorStatus::waving);
      theHeadControlMode = HeadControl::lookForward;
      Waving();
    }
  }
}
