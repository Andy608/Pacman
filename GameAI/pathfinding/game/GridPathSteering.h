#ifndef GRID_PATH_STEERING_H_
#define GRID_PATH_STEERING_H_

#include <Trackable.h>

#include "Steering.h"
#include "Path.h"

class GridPathSteering : public Steering
{
public:
	GridPathSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID);
	virtual ~GridPathSteering();

	virtual Steering* getSteering();

	void resetPathIndex()
	{
		targetPathIndex = 0;
	}

protected:
	Vector2D currentPosition;
	int targetPathIndex;
};

#endif