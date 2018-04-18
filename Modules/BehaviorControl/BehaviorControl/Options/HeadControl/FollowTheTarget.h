option(FollowTheTarget, (float) (0.f) pan , (float) (0.35f) tilt)
{
  /** Simply sets the necessary angles */
  initial_state(lookForward)
  {
    action
    { 
      SetHeadPanTilt(pan, tilt, 150_deg);
    }
  }
}