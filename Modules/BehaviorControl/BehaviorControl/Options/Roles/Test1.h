/** A test striker option without common decision */
option(Test1)
{
  initial_state(firstState)
  {
    transition
    {
        
        OUTPUT_TEXT("Test1_firstState_transition");
        if(action_done)
        {
            OUTPUT_TEXT("Test1_firstState_action_done");
        }
    }
    action
    {
        
        OUTPUT_TEXT("Test1_firstState_action");
        Test2();

    }
  }
  
  target_state(targetstate)
  {
    transition
    {

        OUTPUT_TEXT("Test1_targetstate_transition");

    }
    action
    {

        OUTPUT_TEXT("Test1_targetstate_action");

    }
      
  }
}
