option(LookUpandDown, (float) (-0.38f) Uptilt, (float) (0.38f) Downtilt, (float) (0.f) pan,(float)(pi) speed, ((HeadMotionRequest) CameraControlMode)(autoCamera) camera)
{
  /** Set the head motion request. */
  initial_state(setRequest)
  {
    transition
    {
      if(state_time >4000)
        goto targetReached;
    }
    action
    {
      SetHeadPanTilt(pan, Uptilt, 50_deg);
    }
  }

  /** This state "notifies" the caller that the requested head angles are reached */
  target_state(targetReached)
  {
    transition
    {
	  if(state_time >4000)
      goto setRequest;
    }
    action
    {
      SetHeadPanTilt(pan, Downtilt, 50_deg);
    }
  }
}