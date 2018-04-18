/**
 * @file Representations/MotionControl/ArmMotionRequest.h
 * This file declares a struct that represents the arm motions that can be requested from the robot.
 * @author <a href="mailto:jesse@tzi.de">Jesse Richter-Klug</a>
 */

#pragma once

#include "ArmKeyFrameRequest.h"
#include "Tools/RobotParts/Arms.h"
#include "Tools/Math/Eigen.h"

/**
 * @struct ArmMotionRequest
 * A struct that represents the arm motions that can be requested from the robot.
 * 
STREAMABLE (<class >,
{ <header >,
<comma - separated - declarations >,
})
header: Everything that can be part of a class body except for the attributes that should
be streamable and the default constructor. Please note that this part must not contain
commas that are not surrounded by parentheses, because C++ would consider it to be
more than a single macro parameter otherwise. A workaround is to use the macro COMMA
instead of an actual comma. However, the use of that macro should be avoided if possible,
e. g. by defining constructors with comma-separated initializer lists outside of the struct’s
body.
 */
STREAMABLE(ArmMotionRequest,
{
  ENUM(ArmRequest,
  {,
    none, /**< The motionengine provides which also provides the leg motions, provides also the arms */
    keyFrame,
  });

  ArmMotionRequest() { armMotion[Arms::left] = armMotion[Arms::right] = none; },   //constructor
  
    //<comma - separated - declarations >
  (ENUM_INDEXED_ARRAY((ArmMotionRequest) ArmRequest, (Arms) Arm)) armMotion, /**< The selected armmotion per arm .   (<type >) <var >*/  
  (ArmKeyFrameRequest) armKeyFrameRequest, /**< The key frame request, if it is the selected armmotion.  (<type >) <var >*/
});

struct ArmMotionInfo : public ArmMotionRequest {};
