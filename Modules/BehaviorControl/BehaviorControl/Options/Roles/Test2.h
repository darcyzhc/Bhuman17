/** A test striker option without common decision */
option(Test2)
{
  initial_state(firstState)
  {
    transition
    {
        OUTPUT_TEXT("Test2_firstState_transition");
        OUTPUT_TEXT(state_time);
        if(state_time>2000)
            goto targetState;
    }
    action
    {
        OUTPUT_TEXT("Test2_firstState_action");
    }
  }
  target_state( targetState )
    { 
        transition
        {
          OUTPUT_TEXT("Test2_targetstate_transition");
          if(state_time>2000)
            goto firstState;
        }

    }

}
