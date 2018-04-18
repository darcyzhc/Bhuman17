/**
 * @file LibCodeReleaseProvider.h
 */

#include "Tools/Module/Module.h"
#include "Representations/BehaviorControl/Libraries/LibCodeRelease.h"
#include "Representations/Infrastructure/FrameInfo.h"
#include "Representations/Modeling/BallModel.h"
#include "Representations/Modeling/RobotPose.h"
#include "Representations/Modeling/ObstacleModel.h"
#include "Representations/Configuration/FieldDimensions.h"

#include "Representations/Communication/TeamData.h"
#include "Representations/Perception/PlayersPercepts/PlayersImagePercept.h"
#include "Representations/Perception/PlayersPercepts/PlayersFieldPercept.h"
#include "Representations/Sensing/ArmContactModel.h"
//#include "Representations/Customized/GlobalBallPosition.h"
#include "Representations/Modeling/TeamPlayersModel.h"
#include "Representations/Perception/BallPercepts/BallPercept.h"
#include "Representations/Modeling/TeamBallModel.h"
MODULE(LibCodeReleaseProvider,
{,
  REQUIRES(BallModel),
  REQUIRES(FieldDimensions),
  REQUIRES(FrameInfo),
  REQUIRES(RobotPose),
  REQUIRES(TeamData),
  
  REQUIRES(PlayersFieldPercept),
  REQUIRES(PlayersImagePercept),
  REQUIRES(ObstacleModel),
  REQUIRES(ArmContactModel),
  REQUIRES(TeamPlayersModel),
  REQUIRES(BallPercept),
  REQUIRES(TeamBallModel),
  
  PROVIDES(LibCodeRelease),
  
 // PROVIDES(GlobalBallPosition),
});

class LibCodeReleaseProvider : public LibCodeReleaseProviderBase
{
  void update(LibCodeRelease& libCodeRelease);
};
