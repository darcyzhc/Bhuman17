option(KeeperReady)
{
  /* position has been reached -> stand and wait */
  initial_state(stand)
  {
	  transition
	  {
		  if(std::abs(theRobotPose.translation.y()) < 100)
			  goto turn;
	  }
    action
    {
	  WalkToTarget(Pose2f(50.f, 50.f, 50.f),Pose2f(-(theRobotPose.rotation + pi/2), theRobotPose.translation.y(),0.f));
      LookForward();
	  OUTPUT_TEXT("stand");
    }
  }
  state(turn)
  {
	  transition
	  {
		  //if(libCodeRelease.timeSinceCircleWasSeen() < 300)
			  //goto positiononfield;
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
		  if(std::abs(theRobotPose.translation.x()+4200) < 50 &&std::abs(theRobotPose.translation.y()) < 10 && std::abs(theRobotPose.rotation) < 5_deg)
			  goto waite;
	  }
	  action
	  {
		  WalkToTarget(Pose2f(50.f, 50.f, 50.f),Pose2f(-theRobotPose.rotation,-(theRobotPose.translation.x()+4200),-(theRobotPose.translation.y())));
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