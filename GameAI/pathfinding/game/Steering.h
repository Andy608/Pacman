#ifndef STEERING_H_
#define STEERING_H_

/*Steering - implementation of Steering class from "Artificial Intelligence for Games" - Millington and Funge
*/

#include <Vector2D.h>
#include <Trackable.h>

#include "defines.h"
#include "PhysicsComponent.h"

class Steering : public Trackable
{
public:
	enum SteeringType
	{
		INVALID_TYPE = -1,
		ARRIVE,
		PATH,
		GRID_PATH,
		CONTINUOUS_PATH
	};

	//constructors and destructors
	Steering(SteeringType type = INVALID_TYPE, const UnitID& ownerID = INVALID_UNIT_ID, const Vector2D& targetLoc = ZERO_VECTOR2D, const UnitID& targetID = INVALID_UNIT_ID) :
		mType(type),
		mOwnerID(ownerID),
		mTargetLoc(targetLoc),
		mTargetID(targetID),
		mData(ZERO_PHYSICS_DATA) {};

	virtual ~Steering() {};

	//getters
	const Vector2D& getTargetLoc() const { return mTargetLoc; };
	const UnitID& getTargetID() const { return mTargetID; };
	const PhysicsData& getData() const { return mData; };

	//setters
	void setTargetLoc(const Vector2D& loc) { mTargetLoc = loc; };
	void setTargetID(const UnitID& id) { mTargetID = id; };
	void setOwnerID(const UnitID& id) { mOwnerID = id; };

	void update();

	virtual Steering* getSteering() { return this; };//overridden by sub-classes

protected:
	SteeringType mType;
	Vector2D mTargetLoc;
	UnitID mTargetID;
	UnitID mOwnerID;
	PhysicsData mData;
};

#endif