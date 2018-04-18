option(Striker1Ready)
{
  /* position has been reached -> stand and wait */
  initial_state(start)
  {
	  transition
	  {
		  if((std::abs(theRobotPose.translation.y() - 750) < 100) || state_time>25000)
			goto turn;
	  }
    action
    {
	  if(std::abs(theRobotPose.rotation + pi/2) < 15_deg)
	    WalkToTarget(Pose2f(15.f, 15.f, 15.f),Pose2f(-(theRobotPose.rotation + pi/2), (theRobotPose.translation.y() - 750),0.f));
      else
		WalkToTarget(Pose2f(15.f, 15.f, 15.f),Pose2f(-(theRobotPose.rotation + pi/2),0.f,0.f));
        LookLeft();
	 // OUTPUT_TEXT("start");
    }
  }
  state(turn)
  {
	  transition
	  {
		if(std::abs(theRobotPose.rotation) < 5_deg)
		  goto positiononfield;
	  }
	  action
	  {
		  WalkToTarget(Pose2f(30.f, 30.f, 30.f),Pose2f(-theRobotPose.rotation, 0.f, 0.f));
		  LookForward();
	  }
  }
  state(positiononfield)
  {
	  transition
	  {
		  if((std::abs(theRobotPose.translation.x() +800) < 50 && std::abs(theRobotPose.translation.y() ) < 50 && std::abs(theRobotPose.rotation) < 5_deg) || state_time>15000)
			  goto wait;
	  }
	  action
	  {
		  WalkToTarget(Pose2f(30.f, 30.f, 30.f),Pose2f(-theRobotPose.rotation,-(theRobotPose.translation.x() +1000) ,-(theRobotPose.translation.y() )));
		  LookForward();
		  OUTPUT_TEXT("positiononfield");
	  }
  }
  state(wait)
  {
	  action
	  {
		   Stand();
		   LookForward();
		   OUTPUT_TEXT("wait");
	  }
  }
}