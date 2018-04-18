/*
 * 射门或者传球前的准备工作，前提是看到球
 */
option(ReadyAttack)
{
  static int dirF=0;  //用于判断敌方守门员的位置
  common_transition
  {
    if(std::abs(theRobotPose.rotation) < 30_deg  )
       {
           if(theLibCodeRelease.DirF!=0)
               dirF=theLibCodeRelease.DirF;
       }
  }
  
   initial_state(turnToBall)
  {
    transition
    {
	  OUTPUT_TEXT("ReadyAttack_turnToBall");
	  if(theLibCodeRelease.timeSinceBallWasSeen > theBehaviorParameters.ballNotSeenTimeOut)
        goto lostBall;
      if(std::abs(theBallModel.estimate.position.angle()) < 5_deg)
      {
          if(theLibCodeRelease.ballOut)
              goto ballOut;
          else goto walkToBall;
      }
    }
    action
    {
	  //OUTPUT_TEXT("Striker_turnToBall_action");
      FollowTheTarget(theBallModel.estimate.position.angle(), theLibCodeRelease.tilt);
      WalkToTarget(Pose2f(100.f, 50.f, 50.f), Pose2f(theBallModel.estimate.position.angle(), 0.f, 0.f));
    }
  }
  
  state(ballOut)
  {
      transition
      {
          if(state_time>3000)
              goto lostBall;
      }
      action
      {
          Activity(BehaviorStatus::ballOut);
          theHeadControlMode = HeadControl::lookForward;
          WalkAtRelativeSpeed(Pose2f(1.f, 0.f, 0.f));
      }
  }
  state(walkToBall)
  {
    transition
    {
      OUTPUT_TEXT("ReadyAttack_walkToBall");
      if(theLibCodeRelease.timeSinceBallWasSeen > theBehaviorParameters.ballNotSeenTimeOut)
              goto lostBall;
      
      if(theBallModel.estimate.position.norm() < 500.f)
            goto beforeAlignToGoal;
            
//      if(theLibCodeRelease.movedBall == true)
//            goto turnToBall;
    }
    action
    {
      FollowTheTarget(theBallModel.estimate.position.angle(), theLibCodeRelease.tilt);
      WalkToTarget(Pose2f(0.01, 50.f, 50.f), theBallModel.estimate.position);
    }
  }

  state(beforeAlignToGoal)
  {
      transition
      {
            if(theLibCodeRelease.timeSinceBallWasSeen > theBehaviorParameters.ballNotSeenTimeOut)
            {
              goto lostBall;
            }
           if(std::abs(theRobotPose.rotation - theLibCodeRelease.angleToGoal) < 50_deg&& theLibCodeRelease.timeSinceBallWasSeen<300 &&
                    theBallModel.estimate.position.x() > 10) //theLibCodeRelease.globalballx>theRobotPose.translation.x()
               goto alignToGoal;
      }
      action
      {
        FollowTheTarget(theBallModel.estimate.position.angle(), theLibCodeRelease.tilt);
		if(theLibCodeRelease.angleToGoal >= 0)
			WalkAtAbsoluteSpeed(Pose2f(1.f, 0.f, -300.f));//右
		if(theLibCodeRelease.angleToGoal < 0)
			WalkAtAbsoluteSpeed(Pose2f(-1.f, 0.f, 300.f));//左
      }
  }
    
  state(alignToGoal)
  {
    transition
    {
        OUTPUT_TEXT("ReadyAttack_alignToGoal");
      if(theLibCodeRelease.timeSinceBallWasSeen > theBehaviorParameters.ballNotSeenTimeOut)
      {
              goto lostBall;
      }
      if((theLibCodeRelease.globalballx<4500.f&&
                        theLibCodeRelease.globalballx>3500.f&&theLibCodeRelease.globalbally<700.f&&theLibCodeRelease.globalballx>-700.f))
        goto alignBehindBall;
      if(dirF==1)
        goto alignBehindBallR;
      else if(dirF==2)
        goto alignBehindBallL;
      else if(dirF==0)
        {
            if(theRobotPose.translation.y()>0) goto alignBehindBallL;
            else goto alignBehindBallR;
        }
    }
    action
    {
      //OUTPUT_TEXT("Striker_alignToGoal_action");
      FollowTheTarget(theBallModel.estimate.position.angle(), theLibCodeRelease.tilt);
      Stand();
    }
  }

  state(alignBehindBallL)
  {
    transition
    {
        OUTPUT_TEXT("ReadyAttack_alignBehindBallL");
      if(theLibCodeRelease.timeSinceBallWasSeen > theBehaviorParameters.ballNotSeenTimeOut)
      {
              goto lostBall;
      }
      
      if(theLibCodeRelease.between(theBallModel.estimate.position.y(), -33.f, -25.f)
      && theLibCodeRelease.between(theBallModel.estimate.position.x(), 200.f, 220.f)
      && std::abs(theLibCodeRelease.angleToGoalL) < 3_deg)
      {
              goto finish;
      }
    }
    action
    {
      FollowTheTarget(theBallModel.estimate.position.angle(), theLibCodeRelease.tilt);
//      if(theRobotPose.translation.x()>theLibCodeRelease.globalballx)    //如果机器人在球的前方，则要先走到球的后方再对齐  
//          {
//              if(theRobotPose.translation.y()>theLibCodeRelease.globalbally)
//                    {
//                        if(std::abs(theRobotPose.translation.y()-theLibCodeRelease.globalbally)<100)        
//                            WalkToTarget(Pose2f(100.f, 100.f, 100.f), Pose2f(0.f, 0.f, -120.f));
//                        else WalkToTarget(Pose2f(100.f, 100.f, 100.f), Pose2f(theLibCodeRelease.angleToGoalL, theBallModel.estimate.position.x() - 200.f, theBallModel.estimate.position.y() + 150.f));
//                    }
//            else 
//                  {
//                      if(std::abs(theRobotPose.translation.y()-theLibCodeRelease.globalbally)<100)
//                            WalkToTarget(Pose2f(100.f, 100.f, 100.f), Pose2f(0.f, 0.f, 120.f));
//                        else WalkToTarget(Pose2f(100.f, 100.f, 100.f), Pose2f(theLibCodeRelease.angleToGoalL, theBallModel.estimate.position.x() - 200.f, theBallModel.estimate.position.y() - 150.f));
//                  }
//         }
//      else WalkToTarget(Pose2f(100.f, 100.f, 100.f), Pose2f(theLibCodeRelease.angleToGoalL, theBallModel.estimate.position.x() - 200.f, theBallModel.estimate.position.y() + 38.f));
        WalkToTarget(Pose2f(50.f, 50.f, 50.f), Pose2f(theLibCodeRelease.angleToGoalL, theBallModel.estimate.position.x() - 210.f, theBallModel.estimate.position.y() + 29.f));
    }
  }

state(alignBehindBallR)
  {
    transition
    {
        OUTPUT_TEXT("ReadyAttack_alignBehindBallR");
      if(theLibCodeRelease.timeSinceBallWasSeen > theBehaviorParameters.ballNotSeenTimeOut)
      {
              goto lostBall;
      }
        
      if(theLibCodeRelease.between(theBallModel.estimate.position.y(), -33.f, -25.f)
      && theLibCodeRelease.between(theBallModel.estimate.position.x(), 200.f, 220.f)
      && std::abs(theLibCodeRelease.angleToGoalR) < 3_deg)
      {
              goto finish;
      }
    }
    action
    {
     FollowTheTarget(theBallModel.estimate.position.angle(), theLibCodeRelease.tilt);
//      if(theRobotPose.translation.x()>theLibCodeRelease.globalballx)
//          {
//              if(theRobotPose.translation.y()>theLibCodeRelease.globalbally)
//                    {
//                        if(std::abs(theRobotPose.translation.y()-theLibCodeRelease.globalbally)<100)
//                            WalkToTarget(Pose2f(100.f, 100.f, 100.f), Pose2f(0.f, 0.f, -120.f));
//                        else WalkToTarget(Pose2f(100.f, 100.f, 100.f), Pose2f(theLibCodeRelease.angleToGoalR, theBallModel.estimate.position.x() - 200.f, theBallModel.estimate.position.y() + 150.f));
//                    }
//            else 
//                  {
//                      if(std::abs(theRobotPose.translation.y()-theLibCodeRelease.globalbally)<100)
//                            WalkToTarget(Pose2f(100.f, 100.f, 100.f), Pose2f(0.f, 0.f, 120.f));
//                        else WalkToTarget(Pose2f(100.f, 100.f, 100.f), Pose2f(theLibCodeRelease.angleToGoalR, theBallModel.estimate.position.x() - 200.f, theBallModel.estimate.position.y() - 150.f));
//                  }
//         }
//      else WalkToTarget(Pose2f(100.f, 100.f, 100.f), Pose2f(theLibCodeRelease.angleToGoalR, theBallModel.estimate.position.x() - 200.f, theBallModel.estimate.position.y() + 38.f));
        WalkToTarget(Pose2f(50.f, 50.f, 50.f), Pose2f(theLibCodeRelease.angleToGoalR, theBallModel.estimate.position.x() - 210.f, theBallModel.estimate.position.y() + 29.f));
    }
  }
  
  state(alignBehindBall)
  {
      transition
      {
          OUTPUT_TEXT("ReadyAttack_alignBehindBall");
        if(theLibCodeRelease.timeSinceBallWasSeen > theBehaviorParameters.ballNotSeenTimeOut)
        {
              goto lostBall;
        }
        
      if(theLibCodeRelease.between(theBallModel.estimate.position.y(), -45.f, -25.f)
      && theLibCodeRelease.between(theBallModel.estimate.position.x(), 20.f, 200.f)
      && std::abs(theRobotPose.rotation) < 5_deg)
      {
              goto finish;
      }
      }
      action
      {
          FollowTheTarget(theBallModel.estimate.position.angle(), theLibCodeRelease.tilt);
          WalkToTarget(Pose2f(80.f, 50.f, 50.f), Pose2f(-theRobotPose.rotation, theBallModel.estimate.position.x() - 100.f, theBallModel.estimate.position.y() + 38.f));
      }
  }
  target_state(finish)
  {
      transition
      {
          goto turnToBall;
      }
  }
  
  aborted_state(lostBall)
  {
      transition
      {
          goto turnToBall;
      }
  }
}

