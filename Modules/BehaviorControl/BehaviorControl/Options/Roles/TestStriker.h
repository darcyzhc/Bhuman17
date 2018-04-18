/** A test striker option without common decision */
option(TestStriker)
{

  initial_state(firstState)
  {
    transition
    {
        //OUTPUT_TEXT("TestStriker_firstState_transition");
    }
    action
    {
       //OUTPUT_TEXT(theTeammate.isPenalized);
       //OUTPUT_TEXT(Time::getCurrentSystemTime());
       //TEAM_OUTPUT("1");
    }
    
  }

  state(secondState)
  {
    transition
    {
        static int c=0;
        c++;
        OUTPUT_TEXT("TestStriker_secondState_transition");
        OUTPUT_TEXT(c);
         if(state_time>1500 )
          goto firstState;
    }
    action
    {
        static int d=0;
        d++;
        OUTPUT_TEXT("TestStriker_secondState_action");
        OUTPUT_TEXT(d);
      //Activity(BehaviorStatus::unknown);
      //LookForward();
      Test1();
     //SpecialAction(SpecialActionRequest::sitDown);
     //Test1();
    }
  }

//  target_state(targetstate)
//  {
//    transition
//    {
//        OUTPUT_TEXT("TestStriker_targetstate_transition");
//        if( action_done || action_aborted )
//          goto firstState;
//    }
//    action
//    {
//        OUTPUT_TEXT("TestStriker_targetstate_action");
//        SpecialAction(SpecialActionRequest::stand);
//    }
//      
//  }
  
}
