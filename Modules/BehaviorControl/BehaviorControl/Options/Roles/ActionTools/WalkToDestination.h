/*
 * 走向指定位置，会检测并避开障碍物
 */
option(WalkToDestination, (const Pose2f&) speed, (const Pose2f&) target, (bool)(true) AlignBall)  //TBall表示走的时候是否要朝向目的地
{
    static float degree=0.f;
    common_transition
      {
          //OUTPUT_TEXT("WalkToDestination_common_transition");
         if(target.translation.y()>0 && target.translation.x()<0)  //第三象限
                degree = (std::atan((target.translation.y())/(target.translation.x()))+180_deg);
        else if(target.translation.y()<0 && target.translation.x()<0) //第四象限
                degree = (std::atan((target.translation.y())/(target.translation.x()))-180_deg);
        else if(target.translation.y()<0 && target.translation.x()>0)  //第一象限
                degree = (std::atan((target.translation.y())/(target.translation.x())));
        else if(target.translation.y()>0 && target.translation.x()>0)  //第二象限
                degree = (std::atan((target.translation.y())/(target.translation.x())));
    }
    
  initial_state(start)
  {
    transition
    {
        //OUTPUT_TEXT("WalkToDestination_start_t");
//        if(theArmContactModel.status[Arms::left].duration>50)
//                goto moveToRA;
//        else if(theArmContactModel.status[Arms::right].duration>50)
//                goto moveToLA;
        if(theLibCodeRelease.timeSinceBallWasSeen > theBehaviorParameters.ballNotSeenTimeOut || 
                theLibCodeRelease.timeSinceBallWasSeen<400&&theBallModel.estimate.position.norm()>520)  //如果没看到球||看到球并且球的距离大于520则要避障
        {
            if(theLibCodeRelease.ObsAtLorR==1)
                goto moveToR;
            else if(theLibCodeRelease.ObsAtLorR==-1)
                goto moveToL;
            else if(theLibCodeRelease.ObsAtLorR==0)
            {
                if(AlignBall) goto alignGoWhenAlignBallTrue;
                else goto alignGoWhenAlignBallFalse;
            }
        }
        else 
             {
                if(AlignBall) goto alignGoWhenAlignBallTrue;
                else goto alignGoWhenAlignBallFalse;
            }
    }
    action
    {
        //theHeadControlMode = HeadControl::lookLeftAndRight;
    }
  }
  


  state(alignGoWhenAlignBallFalse)       //对准X轴正方向，以便更快走向指定地点
  {
    transition
    {
        //OUTPUT_TEXT("WalkToDestination_alignGoWhenAlignBallFalse_t");
         if(std::abs(theRobotPose.rotation-target.rotation)<10_deg )
         {  
             //OUTPUT_TEXT("WalkToDestination_alignGoWhenAlignBallFalse_t1110");
                 WalkToTarget(speed, Pose2f(-(theRobotPose.rotation-target.rotation),  target.translation.y()*std::sin(theRobotPose.rotation) +
target.translation.x()*std::cos(theRobotPose.rotation), target.translation.y()*std::cos(theRobotPose.rotation) - target.translation.x()*std::sin(theRobotPose.rotation)));
             goto start;
         }
    }
    action
    {
        //theHeadControlMode = HeadControl::lookForward;
        if(std::abs(theRobotPose.rotation-target.rotation)>10_deg )  //先对齐
        {
            if(theRobotPose.rotation>0)  //先确定机器人的朝向
            {
                if(theRobotPose.rotation-target.rotation<3.14159 && theRobotPose.rotation-target.rotation>0)  //再判断目标角度
                    WalkAtRelativeSpeed(Pose2f(-100.f, 0.f, 0.f));
                else WalkAtRelativeSpeed(Pose2f(100.f, 0.f, 0.f));
            }
            else
            {
                if(theRobotPose.rotation-target.rotation>-3.14159 && theRobotPose.rotation-target.rotation<0)
                    WalkAtRelativeSpeed(Pose2f(100.f, 0.f, 0.f));
                else WalkAtRelativeSpeed(Pose2f(-100.f, 0.f, 0.f));
            }
        }
    }
  }
  
  state(alignGoWhenAlignBallTrue)       //对准目标，以便更快走向指定地点
  {
    transition
    {
        //OUTPUT_TEXT("WalkToDestination_alignGoWhenAlignBallTrue_t");
         if(std::abs(theRobotPose.rotation-degree)<18_deg )
         {
                WalkToTarget(speed, Pose2f(-(theRobotPose.rotation-degree),  target.translation.y()*std::sin(theRobotPose.rotation) +
target.translation.x()*std::cos(theRobotPose.rotation), target.translation.y()*std::cos(theRobotPose.rotation) - target.translation.x()*std::sin(theRobotPose.rotation)));
             goto start;
         }
    }
    action
    {
       // theHeadControlMode = HeadControl::lookForward;
        if(std::abs(theRobotPose.rotation-degree)>18_deg )
        {
           if(theRobotPose.rotation>0)  //先确定机器人的朝向
            {
                if((theRobotPose.rotation-degree)<3.14159 && (theRobotPose.rotation-degree)>0)  //再判断目标角度
                    WalkAtRelativeSpeed(Pose2f(-1.f, 0.f, 0.f));
                else WalkAtRelativeSpeed(Pose2f(1.f, 0.f, 0.f));
            }
            else
            {
                if((theRobotPose.rotation-degree)>-3.14159 && (theRobotPose.rotation-degree)<0)
                    WalkAtRelativeSpeed(Pose2f(1.f, 0.f, 0.f));
                else WalkAtRelativeSpeed(Pose2f(-1.f, 0.f, 0.f));
            }
        }
    }
  }
  
  state(moveToL)
  {
      transition
      {
          OUTPUT_TEXT("WalkToDestination_moveToL_t");
          if(state_time>1500)
              goto start;
      }
      action
      {
          theHeadControlMode = HeadControl::lookForward;
          WalkAtRelativeSpeed(Pose2f(0.f, 0.f, 1.f));
      }
  }
  state(moveToR)
  {
      transition
      {
          OUTPUT_TEXT("WalkToDestination_moveToR_t");
          if(state_time>1500)
              goto start;
      }
      action
      {
          theHeadControlMode = HeadControl::lookForward;
          WalkAtRelativeSpeed(Pose2f(0.f, 0.f, -1.f));
      }
  }
  
  state(moveToLA)  //向左移动，因为右臂碰撞
  {
      transition
      {
          OUTPUT_TEXT("WalkToDestination_moveToLA");
          if(theFrameInfo.getTimeSince(theArmContactModel.status[Arms::right].timeOfLastContact)>500)
              goto start;
      }
      action
      {
          WalkAtRelativeSpeed(Pose2f(0.f, 0.f, 1.f));
      }
  }
  state(moveToRA)
  {
      transition
      {
          OUTPUT_TEXT("WalkToDestination_moveToRA");
          if(theFrameInfo.getTimeSince(theArmContactModel.status[Arms::left].timeOfLastContact)>500)
              goto start;
      }
      action
      {
          WalkAtRelativeSpeed(Pose2f(0.f, 0.f, -1.f));
      }
  }
}
