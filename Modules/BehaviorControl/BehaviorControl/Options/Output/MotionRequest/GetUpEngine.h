/** Sets all members of the MotionRequest representation for simple get up from engine*/
option(GetUpEngine)
{
  /** Set the motion request. */
  initial_state(setRequest)
  {
    transition
    {
      if(theGetUpEngineOutput.isLeavingPossible == false)
        goto executing;
    }
    action
    {
      //OUTPUT_TEXT("GetUpEngine_setRequest_action");
      theMotionRequest.motion = MotionRequest::getUp;
    }
  }

  /** The motion process has started executing the request. */
  state(executing)
  {
    transition
    {
      if(theGetUpEngineOutput.isLeavingPossible == true)
        goto requestIsExecuted;
    }
    action
    {
      //OUTPUT_TEXT("GetUpEngine_executing_action");
      theMotionRequest.motion = MotionRequest::getUp;
    }
  }

  target_state(requestIsExecuted)
  {
    action
    {
      //OUTPUT_TEXT("GetUpEngine_requestIsExecuted_action");
      theMotionRequest.motion = MotionRequest::getUp;
    }
  }
}
