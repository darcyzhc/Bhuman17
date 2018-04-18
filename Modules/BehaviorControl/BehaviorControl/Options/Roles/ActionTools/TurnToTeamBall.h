/*
 * 原地站立摇头找球，然后旋转90度继续，旋转一周后结束
 */
option(TurnToTeamBall)
{
  static int turnCount=0; //用于计数找球时旋转的次数
  initial_state(instead)
  {
      transition
      {
           OUTPUT_TEXT("TurnToTeamBall_turnToTeamBallL");
          if(!theTeamBallModel.isValid)
                goto lostBall;
        if(std::abs(std::atan(theLibCodeRelease.bally / theLibCodeRelease.ballx)) < 18_deg && theLibCodeRelease.ballx > 0.f )
//          if(std::abs(theRobotPose.rotation-(std::atan((theRobotPose.translation.y()-
//                        theTeamBallModel.position.y())/(theRobotPose.translation.x()-theTeamBallModel.position.x()))+180_deg)) < 5_deg  ||
//                        std::abs(theRobotPose.rotation-(std::atan((theRobotPose.translation.y()-
//                        theTeamBallModel.position.y())/(theRobotPose.translation.x()-theTeamBallModel.position.x()))-180_deg)) < 5_deg  ||
//                        std::abs(theRobotPose.rotation-(std::atan((theRobotPose.translation.y()-
//                        theTeamBallModel.position.y())/(theRobotPose.translation.x()-theTeamBallModel.position.x())))) < 5_deg ||
//                        std::abs(theRobotPose.rotation-(std::atan((theRobotPose.translation.y()-
//                        theTeamBallModel.position.y())/(theRobotPose.translation.x()-theTeamBallModel.position.x())))) < 5_deg || state_time > 4000 )
                goto finish; 
      }
      action
      {
          theHeadControlMode = HeadControl::lookForward;
//        if(theRobotPose.rotation >= 0_deg)
//            WalkToTarget(Pose2f(50.f, 50.f, 50.f),Pose2f( pi - theRobotPose.rotation + std::atan((theRobotPose.translation.y() - 
//                        theTeamBallModel.position.y()) / (theRobotPose.translation.x() - theTeamBallModel.position.x())), 0.f, 0.f));
//        if(theRobotPose.rotation < 0_deg)
//            WalkToTarget(Pose2f(50.f, 50.f, 50.f),Pose2f( (-(pi + theRobotPose.rotation)) + std::atan((theRobotPose.translation.y() - 
//                    theTeamBallModel.position.y()) / (theRobotPose.translation.x() - theTeamBallModel.position.x())), 0.f, 0.f));
          WalkToDestination(Pose2f(60.f, 20.f, 20.f), Pose2f(0_deg,  -(theRobotPose.translation.x() - theTeamBallModel.position.x()), 
                -(theRobotPose.translation.y() - theTeamBallModel.position.y())), true);
      }
  }
  
  
  state(turnToTeamBallL)
  {
      transition
      {
         
          if(std::abs(theRobotPose.rotation-(std::atan((theRobotPose.translation.y()-
                        theTeamBallModel.position.y())/(theRobotPose.translation.x()-theTeamBallModel.position.x()))+180_deg)) < 5_deg  ||
                        std::abs(theRobotPose.rotation-(std::atan((theRobotPose.translation.y()-
                        theTeamBallModel.position.y())/(theRobotPose.translation.x()-theTeamBallModel.position.x()))-180_deg)) < 5_deg  ||
                        std::abs(theRobotPose.rotation-(std::atan((theRobotPose.translation.y()-
                        theTeamBallModel.position.y())/(theRobotPose.translation.x()-theTeamBallModel.position.x())))) < 5_deg ||
                        std::abs(theRobotPose.rotation-(std::atan((theRobotPose.translation.y()-
                        theTeamBallModel.position.y())/(theRobotPose.translation.x()-theTeamBallModel.position.x())))) < 5_deg  )
                goto finish; 
        if(!theTeamBallModel.isValid)
                goto lostBall;
      }
      action
      {
          if(theTeamBallModel.isValid)
          {
              if(theTeamBallModel.position.y()>theRobotPose.translation.y() && theTeamBallModel.position.x()<theRobotPose.translation.x())
            {
                if(theRobotPose.rotation<-1.57 && theRobotPose.rotation >-3.14)
                    goto transitToThreeQuadrant;
                else WalkToDestination(Pose2f(80.f, 100.f, 100.f), Pose2f(-(theRobotPose.rotation-(std::atan((theRobotPose.translation.y()-
                        theTeamBallModel.position.y())/(theRobotPose.translation.x()-theTeamBallModel.position.x()))+180_deg)),0.f, 0.f));
            }
              else if(theTeamBallModel.position.y()<theRobotPose.translation.y() && theTeamBallModel.position.x()<theRobotPose.translation.x())
              {
                  if(theRobotPose.rotation>1.57 && theRobotPose.rotation <3.14)
                    goto transitToFourQuadrant;
                else WalkToDestination(Pose2f(80.f, 100.f, 100.f), Pose2f(-(theRobotPose.rotation-(std::atan((theRobotPose.translation.y()-
                        theTeamBallModel.position.y())/(theRobotPose.translation.x()-theTeamBallModel.position.x()))-180_deg)),0.f, 0.f));
              }
              else if(theTeamBallModel.position.y()<theRobotPose.translation.y() && theTeamBallModel.position.x()>theRobotPose.translation.x())
                   WalkToDestination(Pose2f(80.f, 100.f, 100.f), Pose2f(-(theRobotPose.rotation-(std::atan((theRobotPose.translation.y()-
                        theTeamBallModel.position.y())/(theRobotPose.translation.x()-theTeamBallModel.position.x())))),0.f, 0.f));
              else if(theTeamBallModel.position.y()>theRobotPose.translation.y() && theTeamBallModel.position.x()>theRobotPose.translation.x())
                   WalkToDestination(Pose2f(80.f, 100.f, 100.f), Pose2f(-(theRobotPose.rotation-(std::atan((theRobotPose.translation.y()-
                        theTeamBallModel.position.y())/(theRobotPose.translation.x()-theTeamBallModel.position.x())))),0.f, 0.f));
          }
      }
  }
  
  state(transitToThreeQuadrant)  //从第四象限转向第三象限时的过渡
  {
      transition
      {
          if(theRobotPose.rotation>0_deg)
              goto turnToTeamBallL;
      }
      action
      {
          WalkAtRelativeSpeed(Pose2f(-100.f, 0.f, 0.f));
      }
  }

  state(transitToFourQuadrant)  //从第三象限转向第四象限时的过渡
  {
      transition
      {
          if(theRobotPose.rotation<0_deg)
              goto turnToTeamBallL;
      }
      action
      {
          WalkAtRelativeSpeed(Pose2f(100.f, 0.f, 0.f));
      }
  }
  target_state(finish)
  {
      transition
      {
          goto turnToTeamBallL;
      }
  }
  
  aborted_state(lostBall)
  {
      transition
      {
          goto turnToTeamBallL;
      }
  }
   
}

