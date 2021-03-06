option(HeadControl)
{
  common_transition
  {
      //OUTPUT_TEXT("HeadControl_common_transition");
    if(!theGroundContactState.contact && theGameInfo.state != STATE_INITIAL)
      goto lookForward;

    switch(theHeadControlMode)
    {
      case HeadControl::off:
        goto off;
      case HeadControl::lookForward:
        goto lookForward;
      case HeadControl::lookLeftAndRight:
        goto lookLeftAndRight;
      default:
        goto none;
    }
  }

  initial_state(none) {}
  state(off) {action SetHeadPanTilt(JointAngles::off, JointAngles::off, 0.f);}
  state(lookForward) 
  {
      action 
      {
          //OUTPUT_TEXT("HeadControl_lookForward_action");
          LookForward();
      }
  }
  state(lookLeftAndRight) 
  {
      action 
      {
          //OUTPUT_TEXT("HeadControl_lookLeftAndRight_action");
          LookLeftAndRight();
      }
  }
}

struct HeadControl
{
  ENUM(Mode,
  {,
    none,
    off,
    lookForward,
    lookLeftAndRight,
  });
};

HeadControl::Mode theHeadControlMode = HeadControl::Mode::none; /**< The head control mode executed by the option HeadControl. */
