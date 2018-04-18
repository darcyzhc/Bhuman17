option(LookLeftAndRight, (float) (1.0) rightPan, (float) (-1.0) leftPan, (float) (0.38f) tilt,(float)(pi) speed, ((HeadMotionRequest) CameraControlMode)(autoCamera) camera)
{
  /** Set the head motion request. */
  initial_state(Request1)
  {
    transition
    {
      if(action_done)
        goto pausetime1;
    }
    action
    {
      SetHeadPanTilt(0.2, tilt, speed);
    }
  }
  state(pausetime1)
  {
    transition
    {
	  if(state_time>600)
      goto Request2;
    }
  }
  state(Request2)
  {
    transition
    {
      if(action_done)
        goto pausetime2;
    }
    action
    {
      SetHeadPanTilt(0.4, tilt, speed);
    }
  }
state(pausetime2)
  {
    transition
    {
	  if(state_time>600)
      goto Request3;
    }
  }
  
  state(Request3)
  {
    transition
    {
      if(action_done)
        goto pausetime3;
    }
    action
    {
      SetHeadPanTilt(0.6, tilt, speed);
    }
  }
  state(pausetime3)
  {
    transition
    {
	  if(state_time>600)
      goto Request4;
    }
  }
  
  state(Request4)
  {
    transition
    {
      if(action_done)
        goto pausetime4;
    }
    action
    {
      SetHeadPanTilt(0.8, tilt, speed);
    }
  }
  state(pausetime4)
  {
    transition
    {
	  if(state_time>600)
      goto Request5;
    }
  }
  
  state(Request5)
  {
    transition
    {
      if(action_done)
        goto pausetime5;
    }
    action
    {
      SetHeadPanTilt(1.0, tilt, speed);
    }
  }
  state(pausetime5)
  {
    transition
    {
	  if(state_time>600)
      goto Request6;
    }
  }
  
    state(Request6)
  {
    transition
    {
      if(action_done)
        goto pausetime6;
    }
    action
    {
      SetHeadPanTilt(-0.2, tilt, speed);
    }
  }
  state(pausetime6)
  {
    transition
    {
	  if(state_time>600)
      goto Request7;
    }
  }
  
    state(Request7)
  {
    transition
    {
      if(action_done)
        goto pausetime7;
    }
    action
    {
      SetHeadPanTilt(-0.4, tilt, speed);
    }
  }
  state(pausetime7)
  {
    transition
    {
	  if(state_time>600)
      goto Request8;
    }
  }
  
    state(Request8)
  {
    transition
    {
      if(action_done)
        goto pausetime8;
    }
    action
    {
      SetHeadPanTilt(-0.6, tilt, speed);
    }
  }
  state(pausetime8)
  {
    transition
    {
	  if(state_time>600)
      goto Request9;
    }
  }
  
    state(Request9)
  {
    transition
    {
      if(action_done)
        goto pausetime9;
    }
    action
    {
      SetHeadPanTilt(-0.8, tilt, speed);
    }
  }
  state(pausetime9)
  {
    transition
    {
	  if(state_time>600)
      goto Request10;
    }
  }
  
    state(Request10)
  {
    transition
    {
      if(action_done)
        goto pausetime10;
    }
    action
    {
      SetHeadPanTilt(-1.0, tilt, speed);
    }
  }
  state(pausetime10)
  {
    transition
    {
	  if(state_time>600)
      goto Request1;
    }
  }
  /** This state "notifies" the caller that the requested head angles are reached */

}