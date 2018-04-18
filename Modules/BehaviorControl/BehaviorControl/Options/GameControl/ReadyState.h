option(ReadyState)
{
  /* position has been reached -> stand and wait */
  initial_state(stand)
  {
	  transition
	  {
		  if(std::abs(theRobotPose.translation.y() -750) < 100)
			  goto turn;
	  }
    action
    {
	  WalkToTarget(Pose2f(50.f, 50.f, 50.f),Pose2f(0.f, (theRobotPose.translation.y() - 750), -(theRobotPose.translation.x() + 2000)));
      LookForward();
	  OUTPUT_TEXT("stand");
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
		  WalkToTarget(Pose2f(50.f, 0.f, 0.f),Pose2f(-theRobotPose.rotation, 0.f, 0.f));
	  }
  }
  state(positiononfield)
  {
	  transition
	  {
		  if(std::abs(theRobotPose.translation.x()+2000) < 100 &&std::abs(theRobotPose.translation.y() - 750) < 10 && std::abs(theRobotPose.rotation) < 5_deg)
			  goto waite;
	  }
	  action
	  {
		  WalkToTarget(Pose2f(50.f, 50.f, 50.f),Pose2f(-theRobotPose.rotation,-(theRobotPose.translation.x()+2000) ,-(theRobotPose.translation.y() - 750)));
		  OUTPUT_TEXT("positiononfield");
	  }
  }
  state(waite)
  {
	  action
	  {
		   Stand();
		   OUTPUT_TEXT("waite");
	  }
  }
}