#ifndef CONTINUOUS_PATH_STEERING_H_
#define CONTINUOUS_PATH_STEERING_H_

#include <Trackable.h>

#include "Steering.h"
#include "PathSteering.h"
#include "Path.h"

class ContinuousPathSteering : public PathSteering
{
public:
	ContinuousPathSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID);
	virtual ~ContinuousPathSteering();

	virtual Steering* getSteering();
};

#endif