/** Sets all members of the MotionRequest representation for executing a targetMode-WalkRequest
 *  (i.e. Walk to a \c target at a \c speed)
 *  @param speed Walking speeds, as a ratio of the maximum speeds [0..1].
 *  @param target Walking target, in mm and radians, relative to the robot.
 */
option(WalkToTarget, (const Pose2f&) speed, (const Pose2f&) target)
{
  /** Set the motion request. */
  initial_state(setRequest)
  {
    transition
    {
      //OUTPUT_TEXT("WalkToTarget_setRequest_transition");
      if(theMotionInfo.motion == MotionRequest::walk)
        goto requestIsExecuted;
    }
    action
    {
      //OUTPUT_TEXT("WalkToTarget_setRequest_action");
      theMotionRequest.motion = MotionRequest::walk;
      theMotionRequest.walkRequest.mode = WalkRequest::targetMode;
      theMotionRequest.walkRequest.target = target;
      theMotionRequest.walkRequest.speed = speed;
      theMotionRequest.walkRequest.walkKickRequest = WalkRequest::WalkKickRequest();
    }
  }

  /** The motion process has started executing the request. */
  target_state(requestIsExecuted)
  {
    transition
    {
      //OUTPUT_TEXT("WalkToTarget_requestIsExecuted_transition");
      if(theMotionInfo.motion != MotionRequest::walk)
        goto setRequest;
    }
    action
    {
      //OUTPUT_TEXT("WalkToTarget_requestIsExecuted_action");
      //OUTPUT_TEXT(state_time);
      theMotionRequest.motion = MotionRequest::walk;
      theMotionRequest.walkRequest.mode = WalkRequest::targetMode;
      theMotionRequest.walkRequest.target = target;
      theMotionRequest.walkRequest.speed = speed;
      theMotionRequest.walkRequest.walkKickRequest = WalkRequest::WalkKickRequest();
      //MotionRequest.motion共有6种取值:
      //walk,
      //kick,
      //specialAction,
      //stand,
      //getUp,
      //fall,
      
      //walkRequest.mode有3种取值:
      // absoluteSpeedMode, /**< Interpret \c speed as absolute walking speed and ignore \c target. */
      //relativeSpeedMode, /**< Interpret \c speed as ratio of the maximum walking speed and ignore \c target. */
      //targetMode, /**< Use \c target as walking target relative to the current position of the robot and interpret \c speed as percentage walking speed. */
    }
  }
}
