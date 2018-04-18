/** Pun intended. Looks straight ahead in a way that the Nao V4's cameras cover the area in front of its feet as well as everything else in front of the robot.*/
option(LookLeft, (float)(0.38f) tilt, (float)(0.8) pan)
{
  /** Simply sets the necessary angles */
  initial_state(lookLeft)
  {
    action
    {
      //OUTPUT_TEXT("LookForward_lookForward_action");
      SetHeadPanTilt(pan, tilt, 150_deg);
    }
  }
}
