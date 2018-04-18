///** A test striker option without common decision */
option(Keeper)
{
  initial_state(start)
  {
    transition
    {
		if(state_time > 1000)
			;//goto searchForBall;
			//goto alignToGoal;
    }
    action
    {
		OUTPUT_TEXT("state");
		LookForward();
		Stand();
    }
  }
//  /*
//  state(start1)
//  {
//    transition
//    {
//		if((std::abs(theRobotPose.rotation ) < 5_deg && std::abs(theRobotPose.translation.x() -3000.f) <100 && std::abs(theRobotPose.translation.y()) <100) || theRobotPose.translation.x() > 2500.f)
//			//走到指定位置|| 在敌方区域
//			goto searchForBall;
//    }
//    action
//    {
//		LookForward();
//		//走到x=2000
//		if(std::abs(theRobotPose.rotation) < 35_deg) 
//			WalkToTarget(Pose2f(100.f, 100.f, 100.f), Pose2f(-theRobotPose.rotation, -(theRobotPose.translation.x() - 3000.f), -theRobotPose.translation.y()));
//		else
//			WalkToTarget(Pose2f(100.f, 100.f, 100.f), Pose2f(-theRobotPose.rotation, 0.f, 0.f));
//		OUTPUT_TEXT("start1");
//		OUTPUT_TEXT(theRobotPose.translation.x());
//    }
//  }*/
//  
//  state(turnToBall)
//  {
//    transition
//    {
//		if(theLibCodeRelease.timeSinceBallWasSeen > theBehaviorParameters.ballNotSeenTimeOut || theLibCodeRelease.globalballx > 4500.f || std::abs(theLibCodeRelease.globalbally) > 3000.f)
//			goto searchForBall;
//		if(std::abs(theBallModel.estimate.position.angle()) < 5_deg && theLibCodeRelease.globalballx < 4500.f && std::abs(theLibCodeRelease.globalbally) < 3000.f)//对准球,球没出界
//			goto walkToBall;
//    } 
//    action
//    {
//		OUTPUT_TEXT("turnToBall");
//		OUTPUT_TEXT(theLibCodeRelease.globalballx);
//		WalkToTarget(Pose2f(100.f, 100.f, 100.f), Pose2f(theBallModel.estimate.position.angle(), 0.f, 0.f));
//		FollowTheTarget(theBallModel.estimate.position.angle(), theLibCodeRelease.tilt);
//    }	
//  }
//  /*
//  state(waitBall)//在自己的区域内对准球(|y|超过2000的只走到2000处)，等待
//  {
//	  transition
//	  {   
//		if(theLibCodeRelease.timeSinceBallWasSeen > theBehaviorParameters.ballNotSeenTimeOut)
//			goto searchForBall;
//		if(theLibCodeRelease.globalballx > 1700.f && theLibCodeRelease.globalballx < 4500.f && std::abs(theLibCodeRelease.globalbally) < 3000.f)//球没出界，在我的区域
//			goto walkToBall;
//		//if(std::abs(theLibCodeRelease.globalballx) > 4500.f)
//			//goto backReadyTurn;
//	  }
//	  action
//	  {
//		FollowTheTarget(theBallModel.estimate.position.angle());
//		WalkToTarget(Pose2f(50.f, 50.f, 50.f), Pose2f(theBallModel.estimate.position.angle(), 0.f, 0.f));
//		  OUTPUT_TEXT("waitBall");
//		  OUTPUT_TEXT(theRobotPose.translation.x());
//	  }
//  }*/
//
//  state(walkToBall)
//  {
//    transition
//    {
//		if(theLibCodeRelease.timeSinceBallWasSeen > theBehaviorParameters.ballNotSeenTimeOut || theLibCodeRelease.globalballx > 4500.f || std::abs(theLibCodeRelease.globalbally) > 3000.f)
//			goto searchForBall;
//			
//		if(theBallModel.estimate.position.norm() < 350.f)//theBallModel.estimate.position.norm机器人和球之间的距离
//			goto observesituation;
//			
//		if(theRobotPose.translation.y() > 2850.f || theRobotPose.translation.y() < -2850.f || theRobotPose.translation.x() > 4350.f || theRobotPose.translation.x() < - 4350.f )
//			goto turn;
//    }
//    action
//    {
//      FollowTheTarget(theBallModel.estimate.position.angle(), theLibCodeRelease.tilt);
//      OUTPUT_TEXT("walkToBall");
//	  OUTPUT_TEXT(theLibCodeRelease.globalballx);
//	   OUTPUT_TEXT(theRobotPose.translation.x());
//      WalkToTarget(Pose2f(50.f, 50.f, 50.f), Pose2f(theBallModel.estimate.position.angle(), theBallModel.estimate.position.x() - 250.f, theBallModel.estimate.position.y() + 55.f));
//    }
//  }
//  
//  state(observesituation)
//  {
//	  transition
//	  {   
///*
//* 区域1：theRobotPose.translation.x() > 3100.f && std::abs(theRobotPose.translation.x()) < 1100.f
//* 区域2：theRobotPose.translation.x() > 3100.f && std::abs(theRobotPose.translation.x()) > 1100.f
//* 区域3：theRobotPose.translation.x() < 3100.f
//*/ 
//		if(((theRobotPose.translation.x() > 3100.f && theLibCodeRelease.detectedRobot == false) || (theRobotPose.translation.x() > 3900.f && 
//                    theLibCodeRelease.detectedRobot == true)) && std::abs(theRobotPose.translation.y()) < 750.f)//（球门前的区域，没看到人 || 禁区看到人），inwalkkick
//			goto kickInWalk;
//			
//		if(theRobotPose.translation.x() > 3100.f && theRobotPose.translation.x() < 3900.f && std::abs(theRobotPose.translation.y()) < 750.f && 
//                    theLibCodeRelease.detectedRobot == true)//球门前的区域，看到人，踢死角
//			goto kickInWalk;
//			
//		if(((theRobotPose.translation.x() > 3100.f && std::abs(theRobotPose.translation.y()) > 750.f) || theRobotPose.translation.x() < 3100.f) && 
//                    theRobotPose.rotation > -pi/2 && theRobotPose.rotation < pi/2 && theLibCodeRelease.detectedRobot == true && 
//                            std::sqrt(std::pow( theLibCodeRelease.obstacle.center.x(),2)+ std::pow(theLibCodeRelease.obstacle.center.y(),2)) < 800.f && 
//                                std::abs(std::atan(theLibCodeRelease.obstacle.center.y()/theLibCodeRelease.obstacle.center.x())) < 35_deg)//其他区域看到人，在面向敌方方向左右35度,离得近，过人
//			goto acrossrobot;
//			
//		if(((theRobotPose.translation.x() > 3100.f && std::abs(theRobotPose.translation.y()) > 750.f) || theRobotPose.translation.x() < 3100.f) && 
//                    (theRobotPose.rotation < -pi/2 || theRobotPose.rotation > pi/2) && theLibCodeRelease.detectedRobot == true && 
//                        std::sqrt(std::pow( theLibCodeRelease.obstacle.center.x(),2)+ std::pow(theLibCodeRelease.obstacle.center.y(),2)) < 800.f && 
//                            std::abs(std::atan(theLibCodeRelease.obstacle.center.y()/theLibCodeRelease.obstacle.center.x())) < 35_deg)//其他区域看到人，在面向己方方向 左右35度,离得近，不过人
//			goto alignToGoal;
//			
//		if( ((theRobotPose.translation.x() > 3100.f && std::abs(theRobotPose.translation.y()) > 750.f) || theRobotPose.translation.x() < 3100.f) && 
//                    ((theLibCodeRelease.detectedRobot == true && std::abs(std::atan(theLibCodeRelease.obstacle.center.y()/theLibCodeRelease.obstacle.center.x())) > 35_deg) || 
//                        (theLibCodeRelease.detectedRobot == false ) || (theLibCodeRelease.detectedRobot == true && 
//                            std::abs(std::atan(theLibCodeRelease.obstacle.center.y()/theLibCodeRelease.obstacle.center.x())) < 35_deg && 
//                                std::sqrt(std::pow(theLibCodeRelease.obstacle.center.y(),2)+ std::pow(theLibCodeRelease.obstacle.center.x(),2)) > 800.f)))//其他区域 (看到人，在前面左右35度之外)||没看到人 || （看到人，前面35度之内，离得远），shoot
//			goto alignToGoal;
//		
//		if(theRobotPose.translation.y() > 2850.f || theRobotPose.translation.y() < -2850.f || theRobotPose.translation.x() > 4350.f || theRobotPose.translation.x() < - 4350.f )
//			goto turn;
//	  }
//	  action
//	  {  
//		  OUTPUT_TEXT("observesituation");
//		  OUTPUT_TEXT(theLibCodeRelease.obstacle.type);
//		  OUTPUT_TEXT( theRobotPose.translation.x());
//		  OUTPUT_TEXT(theRobotPose.translation.y());
//		  LookForward(0.2f);
//		  if(theRobotPose.translation.x() > 3200.f && std::abs(theRobotPose.translation.y()) <1100.f){
//			WalkToTarget(Pose2f(100.f, 100.f, 100.f), Pose2f(-theRobotPose.rotation, 0.f, 0.f));
//			OUTPUT_TEXT("0du");
//		  }
//		  else
//			Stand();
//	}	  
//  }
//  /*
//  state(alignToGoal)
//  {
//    transition
//    {
//		if(theLibCodeRelease.timeSinceBallWasSeen > theBehaviorParameters.ballNotSeenTimeOut || theLibCodeRelease.globalballx > 4500.f || std::abs(theLibCodeRelease.globalbally) > 3000.f)
//			goto searchForBall;
//			
//		if(((std::abs(theLibCodeRelease.angleToGoal)< 20_deg && theRobotPose.translation.x()<3500.f) || (std::abs(theLibCodeRelease.angleToGoal)<30_deg && theRobotPose.translation.x()>3500.f)) && theBallModel.estimate.position.norm() < 600.f)
//			goto alignBehindBall;
//			
//		if(theBallModel.estimate.position.norm() > 600.f && theLibCodeRelease.globalballx > 1700.f && theLibCodeRelease.globalballx < 4500.f && std::abs(theLibCodeRelease.globalbally) < 3000.f)
//			goto walkToBall;
//			
//		if(std::abs(theRobotPose.translation.x()) > 4400.f || std::abs(theRobotPose.translation.y()) > 2900.f)
//			goto backArea;
//		//if(std::abs(theLibCodeRelease.globalballx) > 4500.f)
//			//goto backReadyTurn;
//    }
//    action
//    {
//		LookForward();
//		OUTPUT_TEXT("alignToGoal");
//		OUTPUT_TEXT(theLibCodeRelease.angleToGoal);
//		OUTPUT_TEXT(theBallModel.estimate.position.norm());
//	  if(theRobotPose.translation.x() > 3800 && std::abs(theRobotPose.translation.y()) < 1100)
//	  {
//		 if(theRobotPose.rotation > pi/2 ||theRobotPose.rotation < -pi/2)
//		 {
//			  
//              
//             if( theLibCodeRelease.angleToGoal <0.f)
//                  WalkToGoal(Pose2f(-8.f,0.f,0.f));//转-8度，用的是这个walkToTarget(Pose2f(50.f,50.f,50.f),speed)函数Pose2f(-8.f,0.f,0.f)传给speed表示位置
//               else
//                   WalkToGoal(Pose2f(8.f,0.f,0.f));
//		  }
//		  else
//		  {
//			  
//              WalkToTarget(Pose2f(50.f, 50.f, 50.f), Pose2f(-theRobotPose.rotation, theBallModel.estimate.position.x() - 250.f, theBallModel.estimate.position.y()));
//		  }
//		  OUTPUT_TEXT("state14");
//	  }
//          if(theRobotPose.rotation > pi/2 ||theRobotPose.rotation < -pi/2)
//		  {
//		   if( theLibCodeRelease.angleToGoal <0.f)
//                  WalkToGoal(Pose2f(-8.f,0.f,0.f));
//               else
//                   WalkToGoal(Pose2f(8.f,0.f,0.f));
//		  }
//		  else
//          {
//			  WalkToTarget(Pose2f(50.f, 50.f, 50.f), Pose2f(theLibCodeRelease.kickAngle, theBallModel.estimate.position.x() - 250.f, theBallModel.estimate.position.y()));//调整踢球角度
//			  
//		  }
//	}
//  }*/
//  state(alignToGoal)
//  {
//	  transition
//	  {
//		  if(theLibCodeRelease.timeSinceBallWasSeen > theBehaviorParameters.ballNotSeenTimeOut || theLibCodeRelease.globalballx > 4500.f || std::abs(theLibCodeRelease.globalbally) > 3000.f)
//			goto searchForBall;
//			
//		if(std::abs(theRobotPose.rotation - theLibCodeRelease.angleToGoal) < 60_deg)
//			goto alignBehindBall;
//			
//		if(theBallModel.estimate.position.norm() > 600.f && theLibCodeRelease.globalballx < 4500.f && std::abs(theLibCodeRelease.globalbally) < 3000.f)
//			goto walkToBall;
//			
//		if(theRobotPose.translation.y() > 2850.f || theRobotPose.translation.y() < -2850.f || theRobotPose.translation.x() > 4350.f || theRobotPose.translation.x() < - 4350.f )
//			goto turn;
//	  }
//	  action
//	  {
//		  OUTPUT_TEXT("alignToGoal");
//		  FollowTheTarget(theBallModel.estimate.position.angle() ,theLibCodeRelease.tilt);
//		if(theLibCodeRelease.angleToGoal >= 0)
//			WalkAtAbsoluteSpeed(Pose2f(0.6f, 0.f, -200.f));//右
//		if(theLibCodeRelease.angleToGoal < 0)
//			WalkAtAbsoluteSpeed(Pose2f(-0.6f, 0.f, 200.f));//左
//			  
//	  }
//  }
//  
//  state(alignBehindBall)
//  {
//    transition
//    {
//		if(theLibCodeRelease.timeSinceBallWasSeen > theBehaviorParameters.ballNotSeenTimeOut || theLibCodeRelease.globalballx > 4500.f || std::abs(theLibCodeRelease.globalbally) > 3000.f)
//			goto searchForBall;
//			
//		if(theBallModel.estimate.position.x() < 230.f && std::abs(theBallModel.estimate.position.y()) < 45.f && std::abs(theLibCodeRelease.kickAngle) < 2_deg )
//			goto kick;
////			
////		if(theBallModel.estimate.position.x() > 350.f || std::abs(theBallModel.estimate.position.y()) > 45.f)
////			goto walkToBall;
//		
//		if(theRobotPose.translation.y() > 2850.f || theRobotPose.translation.y() < -2850.f || theRobotPose.translation.x() > 4350.f || theRobotPose.translation.x() < - 4350.f )
//			goto turn;
//    }
//    action
//    {
//		//LookForward();
//		OUTPUT_TEXT("alignBehindBall");
//		//OUTPUT_TEXT(kickangle);
//		OUTPUT_TEXT(theLibCodeRelease.detectedJersey);
//		OUTPUT_TEXT(theLibCodeRelease.centerOnFieldx);
//		OUTPUT_TEXT(theLibCodeRelease.centerOnFieldy);
//		FollowTheTarget(theBallModel.estimate.position.angle(), theLibCodeRelease.tilt);
//		WalkToTarget(Pose2f(40.f, 40.f, 30.f), Pose2f(theLibCodeRelease.kickAngle, theBallModel.estimate.position.x() - 200.f, theBallModel.estimate.position.y() + 35.f));
//			
//		/*if(theRobotPose.translation.x() > 3100.f && std::abs(theRobotPose.translation.y()) <1100.f && theRobotPose.translation.y() < 0)
//		{//在球门前，机器人y<0往球门左踢
//			kickangle = theLibCodeRelease.qiuMenZuo;
//			WalkToTarget(Pose2f(40.f, 40.f, 30.f), Pose2f(theLibCodeRelease.qiuMenZuo, theBallModel.estimate.position.x() - 180.f, theBallModel.estimate.position.y() + 30.f));
//			OUTPUT_TEXT("y<0");
//		}
//		else if(theRobotPose.translation.x() > 3100.f && std::abs(theRobotPose.translation.y()) <1100.f && theRobotPose.translation.y() > 0)
//		{//在球门前，机器人y>0往球门右踢
//			kickangle = theLibCodeRelease.qiuMenYou;
//			WalkToTarget(Pose2f(40.f, 40.f, 30.f), Pose2f(theLibCodeRelease.qiuMenYou, theBallModel.estimate.position.x() - 180.f, theBallModel.estimate.position.y() + 30.f));
//			OUTPUT_TEXT("y>0");
//		}
//			
//		//不在球门前
//	  else if(theLibCodeRelease.detectedRobot == true && theRobotPose.translation.y() > 0 && std::abs(theLibCodeRelease.centerOnFieldy + theRobotPose.translation.y()) < 1100 && (theLibCodeRelease.centerOnFieldx + theRobotPose.translation.x()) > 3600.f)
//	  {//检测到球衣在禁区内（认为是守门员），机器人在左边
//			//往右踢
//			kickangle = theLibCodeRelease.kickAngleRight;
//			WalkToTarget(Pose2f(40.f, 40.f, 30.f), Pose2f(theLibCodeRelease.kickAngleRight, theBallModel.estimate.position.x() - 180.f, theBallModel.estimate.position.y() + 30.f));
//			OUTPUT_TEXT("right");
//	  }
//	  else if(theLibCodeRelease.detectedRobot == true && theRobotPose.translation.y() < 0 && std::abs(theLibCodeRelease.centerOnFieldy + theRobotPose.translation.y()) < 1100 && (theLibCodeRelease.centerOnFieldx + theRobotPose.translation.x()) > 3600.f)
//	  {//检测到球衣在禁区内（认为是守门员），机器人在右边
//			//往左踢
//			kickangle = theLibCodeRelease.kickAngleLeft;
//			WalkToTarget(Pose2f(40.f, 40.f, 30.f), Pose2f(theLibCodeRelease.kickAngleLeft, theBallModel.estimate.position.x() - 180.f, theBallModel.estimate.position.y() + 30.f));
//			OUTPUT_TEXT("left");
//	  }
//	  else
//	  {//不在球门前，没看到球衣
//		if(theRobotPose.translation.y() < 0)
//		{
//			kickangle = theLibCodeRelease.qiuMenZuo;
//		  WalkToTarget(Pose2f(40.f, 40.f, 30.f), Pose2f(theLibCodeRelease.qiuMenZuo, theBallModel.estimate.position.x() - 180.f, theBallModel.estimate.position.y() + 30.f));
//		  OUTPUT_TEXT("meikandao zuo");
//		}
//		else
//		{
//			kickangle = theLibCodeRelease.qiuMenYou;
//		  WalkToTarget(Pose2f(40.f, 40.f, 30.f), Pose2f(theLibCodeRelease.qiuMenYou, theBallModel.estimate.position.x() - 180.f, theBallModel.estimate.position.y() + 30.f));
//		  OUTPUT_TEXT("meikandao you");
//		}
//	  }*/
//    }
//  }
//  
//  state(kickInWalk)
//  {
//    transition
//    {
//		if(state_time > 2000)
//			goto turnToBall;
//			
//		if(theLibCodeRelease.timeSinceBallWasSeen > theBehaviorParameters.ballNotSeenTimeOut || theLibCodeRelease.globalballx > 4500.f || std::abs(theLibCodeRelease.globalbally) > 3000.f)
//			goto searchForBall;
//			
//if(theRobotPose.translation.y() > 2850.f || theRobotPose.translation.y() < -2850.f || theRobotPose.translation.x() > 4350.f || theRobotPose.translation.x() < - 4350.f )
//			goto turn;    
//	}
//    action
//    {
//		FollowTheTarget(theBallModel.estimate.position.angle(), theLibCodeRelease.tilt);
//	    InWalkKick(WalkKickVariant(WalkKicks::forward, Legs::left), Pose2f(0.f, theBallModel.estimate.position.x(), theBallModel.estimate.position.y() - 100.f));
//		OUTPUT_TEXT("kickInWalk");
//	}
//  }
//  
//  state(kick)
//  {
//    transition
//    {
//		if(state_time > 10 && action_done)
//			goto walkForward;
//			
//		if(state_time > 9000)
//			goto searchForBall;
//			
//		//if(theBallModel.estimate.position.x() > 300.f || std::abs(theBallModel.estimate.position.y()) > 105.f)
//			//goto alignBehindBall;
//    }
//    action
//    {
//		FollowTheTarget(theBallModel.estimate.position.angle(), theLibCodeRelease.tilt);
//		Shoot(KickRequest::greatKickForward);//开大脚
//		OUTPUT_TEXT("Shoot");
//	}
//  }
//  
//  state(walkForward)
//  {
//    transition
//    {
//		if(theLibCodeRelease.timeSinceBallWasSeen > 3000.f && state_time > 3000.f)
//			goto searchForBall;
//			
//		if(theLibCodeRelease.timeSinceBallWasSeen < 300.f)
//			goto turnToBall;
//			
//		if(theRobotPose.translation.y() > 2850.f || theRobotPose.translation.y() < -2850.f || theRobotPose.translation.x() > 4350.f || theRobotPose.translation.x() < - 4350.f )
//			goto turn;
//    }
//    action
//    {
//        FollowTheTarget(theBallModel.estimate.position.angle() , theLibCodeRelease.tilt);
//		WalkToTarget(Pose2f(100.f, 100.f, 100.f), Pose2f(0.f, 1500.f, 0.f));
//		OUTPUT_TEXT("walkForward");
//	}
//  }  
//
//  state(searchForBall)
//  {
//    transition
//    {
//		if(theLibCodeRelease.timeSinceBallWasSeen < 300 && theLibCodeRelease.globalballx < 4500.f && std::abs(theLibCodeRelease.globalbally) < 3000.f)
//			goto turnToBall;
//			
//		if(state_time > 6000)//时间超过5秒
//			goto turnUpToSearch;
//			
//		if((theTeamBallModel.contributors == 1 || theTeamBallModel.contributors == 2) && theLibCodeRelease.ballx > 0)//如果使用通信并且此时另外的队友看到了球
//		      goto walkToGlobalBall;
//			  	
//		if((theTeamBallModel.contributors == 1 || theTeamBallModel.contributors == 2) && theLibCodeRelease.ballx < 0)//如果使用通信并且此时另外的队友看到了球
//		      goto turnToGlobalBall;
//    }
//    action
//    {
//		OUTPUT_TEXT("searchForBall");
//		LookForward();
//		WalkAtRelativeSpeed(Pose2f(1.f, 0.f, 0.f));
//    }
//  }
//  
//   state(walkToGlobalBall)
//  {
//    transition
//    {
//       if(theLibCodeRelease.timeSinceBallWasSeen < 300 && theLibCodeRelease.globalballx < 4500.f && std::abs(theLibCodeRelease.globalbally) < 3000.f)
//			goto turnToBall;
//		
//			
//		if(theLibCodeRelease.timeSinceBallWasSeen > theBehaviorParameters.ballNotSeenTimeOut || theLibCodeRelease.globalballx > 4500.f || std::abs(theLibCodeRelease.globalbally) > 3000.f)
//			goto searchForBall;
//		
//    }
//    action
//    {
//      LookForward(0.28f,0.f);
//      WalkToTarget(Pose2f(50.f, 50.f, 50.f), Pose2f(0.f,theLibCodeRelease.ballx,theLibCodeRelease.bally));
//	  OUTPUT_TEXT("walkToGlobalBall");
//    }
//  }
//  
//  state(turnUpToSearch)
//  {
//    transition
//    {
//		if(theLibCodeRelease.timeSinceBallWasSeen < 300 && theLibCodeRelease.globalballx < 4500.f && std::abs(theLibCodeRelease.globalbally) < 3000.f)
//			goto turnToBall;
//			
//		if(state_time > 6000)//时间超过5秒
//			goto turnLeft;
//		
//		if((theTeamBallModel.contributors == 1 || theTeamBallModel.contributors == 2) && theLibCodeRelease.ballx > 0)//如果使用通信并且此时另外的队友看到了球
//		      goto walkToGlobalBall;
//			  	
//		if((theTeamBallModel.contributors == 1 || theTeamBallModel.contributors == 2) && theLibCodeRelease.ballx < 0)//如果使用通信并且此时另外的队友看到了球
//		      goto turnToGlobalBall;
//    }
//    action
//    {
//		OUTPUT_TEXT("turnUpToSearch");
//		LookForward(0.25f);
//		WalkAtRelativeSpeed(Pose2f(1.f, 0.f, 0.f));
//    }
//  }
//  
//  state(turnLeft)
//  {
//	  transition
//	  {
//		  if(std::abs(90_deg - theRobotPose.rotation) < 5_deg)
//			  goto againSearchLeft;
//		  
//		  if(theLibCodeRelease.timeSinceBallWasSeen < 300 && theLibCodeRelease.globalballx < 4500.f && std::abs(theLibCodeRelease.globalbally) < 3000.f)
//			goto turnToBall; 
//			
//		if((theTeamBallModel.contributors == 1 || theTeamBallModel.contributors == 2) && theLibCodeRelease.ballx > 0)//如果使用通信并且此时另外的队友看到了球
//		      goto walkToGlobalBall;
//			  	
//		if((theTeamBallModel.contributors == 1 || theTeamBallModel.contributors == 2) && theLibCodeRelease.ballx < 0)//如果使用通信并且此时另外的队友看到了球
//		      goto turnToGlobalBall;
//	  }
//	  action
//	  {
//		  LookForward(0.25f);
//		  WalkToTarget(Pose2f(100.f, 50.f, 50.f), Pose2f(90_deg - theRobotPose.rotation, 0.f, 0.f));
//	  }
//  }
//  
//  state(againSearchLeft)
//  {
//	  transition
//	  {
//		if(theRobotPose.translation.y() > 1400.f)
//		  goto lookCircle;
//		  
//		if(theLibCodeRelease.timeSinceBallWasSeen < 300 && theLibCodeRelease.globalballx < 4500.f && std::abs(theLibCodeRelease.globalbally) < 3000.f)
//			goto turnToBall; 
//			
//		if(theRobotPose.translation.y() > 2850.f || theRobotPose.translation.y() < -2850.f || theRobotPose.translation.x() > 4350.f || theRobotPose.translation.x() < - 4350.f )
//			goto turn;
//			
//		if((theTeamBallModel.contributors == 1 || theTeamBallModel.contributors == 2) && theLibCodeRelease.ballx > 0)//如果使用通信并且此时另外的队友看到了球
//		      goto walkToGlobalBall;
//			  	
//		if((theTeamBallModel.contributors == 1 || theTeamBallModel.contributors == 2) && theLibCodeRelease.ballx < 0)//如果使用通信并且此时另外的队友看到了球
//		      goto turnToGlobalBall;
//	  }
//	  action
//	  {
//		LookLeftandRight();
//		if(std::abs(90_deg - theRobotPose.rotation) > 10_deg)
//			WalkToTarget(Pose2f(100.f, 40.f, 40.f), Pose2f(90_deg - theRobotPose.rotation, 0.f, 0.f));
//		else
//			WalkAtRelativeSpeed(Pose2f(0.f, 0.5f, 0.f));
//	  }
//  }
//  
//  state(turnRight)
//  {
//	  transition
//	  {
//		  if(std::abs(-90_deg - theRobotPose.rotation) < 5_deg)
//			  goto againSearchRight;
//		  
//		if(theLibCodeRelease.timeSinceBallWasSeen < 300 && theLibCodeRelease.globalballx < 4500.f && std::abs(theLibCodeRelease.globalbally) < 3000.f)
//			goto turnToBall; 
//			
//		if((theTeamBallModel.contributors == 1 || theTeamBallModel.contributors == 2) && theLibCodeRelease.ballx > 0)//如果使用通信并且此时另外的队友看到了球
//		      goto walkToGlobalBall;
//			  	
//		if((theTeamBallModel.contributors == 1 || theTeamBallModel.contributors == 2) && theLibCodeRelease.ballx < 0)//如果使用通信并且此时另外的队友看到了球
//		      goto turnToGlobalBall;
//	  }
//	  action
//	  {
//		  LookForward(0.25f);
//		  WalkToTarget(Pose2f(100.f, 50.f, 50.f), Pose2f(-90_deg - theRobotPose.rotation, 0.f, 0.f));
//	  }
//  }
//  
//  state(againSearchRight)
//  {
//	  transition
//	  {
//		if(theLibCodeRelease.timeSinceBallWasSeen < 300 && theLibCodeRelease.globalballx < 4500.f && std::abs(theLibCodeRelease.globalbally) < 3000.f)
//			goto turnToBall; 
//			
//		if(theRobotPose.translation.y() < -1400.f)
//			goto lookCircle;
//			
//		if(theRobotPose.translation.y() > 2850.f || theRobotPose.translation.y() < -2850.f || theRobotPose.translation.x() > 4350.f || theRobotPose.translation.x() < - 4350.f )
//			goto turn;
//			
//		if((theTeamBallModel.contributors == 1 || theTeamBallModel.contributors == 2) && theLibCodeRelease.ballx > 0)//如果使用通信并且此时另外的队友看到了球
//		      goto walkToGlobalBall;
//			  	
//		if((theTeamBallModel.contributors == 1 || theTeamBallModel.contributors == 2) && theLibCodeRelease.ballx < 0)//如果使用通信并且此时另外的队友看到了球
//		      goto turnToGlobalBall;
//	  }
//	  action
//	  {
//		LookLeftandRight();
//		if(std::abs(-90_deg - theRobotPose.rotation) > 10_deg)
//			WalkToTarget(Pose2f(100.f, 40.f, 40.f), Pose2f(-90_deg - theRobotPose.rotation, 0.f, 0.f));
//		else
//			WalkAtRelativeSpeed(Pose2f(0.f, 0.5f, 0.f));
//	  }
//  }
//
//  state(acrossrobot)
//  {
//	  transition
//	  {
//		if(theLibCodeRelease.timeSinceBallWasSeen > theBehaviorParameters.ballNotSeenTimeOut)
//			goto searchForBall;
//			
//		if(state_time > 3000)
//			goto walkToBall2;
//			
//		if(theRobotPose.translation.y() > 2850.f || theRobotPose.translation.y() < -2850.f || theRobotPose.translation.x() > 4350.f || theRobotPose.translation.x() < - 4350.f )
//			goto turn;
//	  }
//	  action
//	  {
//		  OUTPUT_TEXT("acrossrobot");
//		  if(theLibCodeRelease.obstacle.center.y() + theRobotPose.translation.y() > 2500)
//				WalkToTarget(Pose2f(100.f, 100.f, 100.f), Pose2f(-pi/2, theBallModel.estimate.position.x() - 150.f, theBallModel.estimate.position.y() + 155.f));
//				
//		  if(theLibCodeRelease.obstacle.center.y() + theRobotPose.translation.y() < -2500)
//				WalkToTarget(Pose2f(100.f, 100.f, 100.f), Pose2f(pi/2, theBallModel.estimate.position.x() - 150.f, theBallModel.estimate.position.y() + 155.f));
//				
//		  if(theLibCodeRelease.obstacle.center.y() + theRobotPose.translation.y() > 0.f)
//				WalkToTarget(Pose2f(100.f, 100.f, 100.f), Pose2f(-pi/3+std::atan(theLibCodeRelease.obstacle.center.y()/theLibCodeRelease.obstacle.center.x()), theBallModel.estimate.position.x() - 150.f, theBallModel.estimate.position.y() + 155.f));
//				
//		  if(theLibCodeRelease.obstacle.center.y() + theRobotPose.translation.y() < 0.f)
//				WalkToTarget(Pose2f(100.f, 100.f, 100.f),Pose2f(pi/3+std::atan(theLibCodeRelease.obstacle.center.y()/theLibCodeRelease.obstacle.center.x()), theBallModel.estimate.position.x() - 150.f, theBallModel.estimate.position.y() + 155.f));
//    }
//  }
//  
//  state(walkToBall2)
//  {
//	transition
//	{
//		if(theLibCodeRelease.timeSinceBallWasSeen > theBehaviorParameters.ballNotSeenTimeOut || theLibCodeRelease.globalballx > 4500.f || std::abs(theLibCodeRelease.globalbally) > 3000.f)
//			goto searchForBall;
//
//		if(theBallModel.estimate.position.norm() < 300.f)
//			goto kickInWalk;
//			
//		if(theRobotPose.translation.y() > 2850.f || theRobotPose.translation.y() < -2850.f || theRobotPose.translation.x() > 4350.f || theRobotPose.translation.x() < - 4350.f )
//			goto turn;
//	}
//	action 
//	{
//		OUTPUT_TEXT("walkToBall2");
//		WalkToTarget(Pose2f(100.f, 100.f, 100.f), theBallModel.estimate.position);
//	}
//  }
//    
//  state(backArea)
//  {
//	  transition
//	  {
//		  if(std::abs(1500.f-theRobotPose.translation.x()) < 100.f && std::abs(theRobotPose.translation.y()) < 100.f)
//			  goto searchForBall;
//			  
//		  if(theLibCodeRelease.timeSinceBallWasSeen < 300 && theLibCodeRelease.globalballx < 4500.f && std::abs(theLibCodeRelease.globalbally) < 3000.f)
//			  goto turnToBall;
//			  
//		 if(theRobotPose.translation.y() > 2850.f || theRobotPose.translation.y() < -2850.f || theRobotPose.translation.x() > 4350.f || theRobotPose.translation.x() < - 4350.f )
//			goto turn;
//	  }transition
//    {
//        if(std::abs(theRobotPose.rotation - pi) < 15_deg)
//			  goto back;
//    }
//    action
//    { 
//	  OUTPUT_TEXT("turn");
//	  if(theRobotPose.rotation >= 0_deg)
//	    WalkToTarget(Pose2f(50.f, 50.f, 50.f),Pose2f( pi - theRobotPose.rotation, 0.f, 0.f));
//	  if(theRobotPose.rotation < 0_deg)
//	    WalkToTarget(Pose2f(50.f, 50.f, 50.f),Pose2f( -(pi + theRobotPose.rotation), 0.f, 0.f));
//	  action
//	  {
//		  LookForward();
//		  //OUTPUT_TEXT(theRobotPose.translation.x());
//		  if(std::abs(theRobotPose.rotation) > 90_deg){
//			WalkToTarget(Pose2f(100.f, 100.f, 100.f), Pose2f(theLibCodeRelease.waitRotation, -1500.f+theRobotPose.translation.x(), theRobotPose.translation.y()));
//			OUTPUT_TEXT("backArea>90");
//		  }
//		  if(std::abs(theRobotPose.rotation) < 90_deg){
//			WalkToTarget(Pose2f(100.f, 100.f, 100.f), Pose2f(-theRobotPose.rotation, 1500.f-theRobotPose.translation.x(), 0.f-theRobotPose.translation.y()));
//			OUTPUT_TEXT("backArea<90");
//		  }
//	  }
//  }
//	
//  state(backAreaTurn)
//  {
//	  transition
//	  {
//		 if(theRobotPose.translation.y() > 2800.f || theRobotPose.translation.y() < -2800.f || theRobotPose.translation.x() > 4300.f || theRobotPose.translation.x() < - 4300.f )
//			goto turn;  if(std::abs(1500.f-theRobotPose.translation.x()) < 100.f && std::abs(theRobotPose.translation.y()) < 100.f)
//			  goto searchForBall;
//			  
//		  if(theLibCodeRelease.timeSinceBallWasSeen < 300 && theLibCodeRelease.globalballx < 4500.f && std::abs(theLibCodeRelease.globalbally) < 3000.f)
//			goto turnToBall; 
//			
//		if((std::abs(theRobotPose.rotation - pi) < 5_deg && (theRobotPose.translation.x() - 1500.f) > 0.f) || (std::abs(theRobotPose.rotation) < 5_deg && (theRobotPose.translation.x() - 1500.f) < 0.f))
//			goto backArea;
//	  }
//	  action
//	  {
//		  OUTPUT_TEXT("backAreaTurn");
//		  //OUTPUT_TEXT(theRobotPose.translation.x());
//		  if((theRobotPose.translation.x() - 1500.f) > 0.f){
//			WalkToTarget(Pose2f(100.f, 100.f, 100.f), Pose2f(theLibCodeRelease.waitRotation, 0.f, 0.f));
//		  }
//		  else{
//			WalkToTarget(Pose2f(100.f, 100.f, 100.f), Pose2f(-theRobotPose.rotation, 0.f, 0.f));
//		  }
//	  }
//  }
//  
//  state(lookCircle)
//  {
//	  transition
//	  {
//		  if(theLibCodeRelease.timeSinceBallWasSeen < 300 && theLibCodeRelease.globalballx < 4500.f && std::abs(theLibCodeRelease.globalbally) < 3000.f)
//			goto turnToBall;
// 
//		  if(state_time > 5000 && theRobotPose.translation.y() > 0.f)
//			goto turnRight;
//		  
//		  if(state_time > 5000 && theRobotPose.translation.y() < 0.f)
//			goto backAreaTurn;
//	  }
//	  action 
//	  {
//		  LookCircle();
//		  Stand();
//	  }
//  }
//  
//  state(turn)
//  {
//    transition
//    {
//        if(std::abs(theRobotPose.rotation - pi) < 15_deg)
//			  goto back;
//    }
//    action
//    { 
//	  OUTPUT_TEXT("turn");
//	  if(theRobotPose.rotation >= 0_deg)
//	    WalkToTarget(Pose2f(50.f, 50.f, 50.f),Pose2f( pi - theRobotPose.rotation, 0.f, 0.f));
//	  if(theRobotPose.rotation < 0_deg)
//	    WalkToTarget(Pose2f(50.f, 50.f, 50.f),Pose2f( -(pi + theRobotPose.rotation), 0.f, 0.f));
//    }
//  }
//  state(back)
//  {
//	  transition
//	  {
//	  if(theLibCodeRelease.timeSinceBallWasSeen < 300)
//        goto turnToBall;
//	  if(state_time > 15000)
//		goto searchForBall;
//	  }
//	  action 
//	  {
//		OUTPUT_TEXT("back");
//		WalkToTarget(Pose2f(80.f, 80.f, 80.f), Pose2f( 0.f , theRobotPose.translation.x() - 1000, theRobotPose.translation.y()));
//        LookLeftandRight();
//	  }
//  }
//  
//  state(turnToGlobalBall)
//  {
//	transition
//    {
//        if(std::abs(std::atan(theLibCodeRelease.bally / theLibCodeRelease.ballx)) < 15_deg)
//			  goto walkToGlobalBall;
//    }
//    action
//    { 
//	  OUTPUT_TEXT("turn");
//	  if(theRobotPose.rotation >= 0_deg)
//	    WalkToTarget(Pose2f(50.f, 50.f, 50.f),Pose2f( pi - theRobotPose.rotation + std::atan((theRobotPose.translation.y() - theLibCodeRelease.ballPosition.y()) / (theRobotPose.translation.x() - theLibCodeRelease.ballPosition.x())), 0.f, 0.f));
//	  if(theRobotPose.rotation < 0_deg)
//	    WalkToTarget(Pose2f(50.f, 50.f, 50.f),Pose2f( (-(pi + theRobotPose.rotation)) + std::atan((theRobotPose.translation.y() - theLibCodeRelease.ballPosition.y()) / (theRobotPose.translation.x() - theLibCodeRelease.ballPosition.x())), 0.f, 0.f));
//	}
//  }
//}
}
