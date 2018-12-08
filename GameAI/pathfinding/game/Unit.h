#ifndef UNIT_H_
#define UNIT_H_

#include <Trackable.h>
#include <DeanLibDefines.h>
#include <limits>
#include <Vector2D.h>

#include "Component.h"
#include "PositionComponent.h"
#include "Sprite.h"
#include "Steering.h"
#include "GridGraph.h"

#include "EventListener.h"
#include "GridPathfinder.h"

class PhysicsComponent;
class SteeringComponent;
class Sprite;
class UnitManager;

const Uint32 DEFAULT_QUEUE_CAPACITY = 8;

class Unit : public EventListener
{
public:
	virtual void handleEvent(const Event& theEvent);

	float getFacing() const;
	virtual void update(float deltaTime) {};
	virtual void draw() const;

	PositionComponent* getPositionComponent() const;
	PhysicsComponent* getPhysicsComponent() const;
	SteeringComponent* getSteeringComponent() const;
	inline GridPathfinder* getGridPathfinder() const { return mpPathfinder; };
	inline GridGraph* getGridGraph() const { return mpGridGraph; };

	float getMaxAcc() const { return mMaxAcc; };
	float getMaxSpeed() const { return mMaxSpeed; };
	float getMaxRotAcc() const { return mMaxRotAcc; };
	float getMaxRotVel() const { return mMaxRotVel; };

	void setShowTarget(bool val) { mShowTarget = val; };

	void setSteering(Steering::SteeringType type, Vector2D targetLoc = ZERO_VECTOR2D, UnitID targetUnitID = INVALID_UNIT_ID);

protected:
	UnitID mID;
	ComponentID mPhysicsComponentID;
	ComponentID mPositionComponentID;
	ComponentID mSteeringComponentID;
	PositionComponent* mpPositionComponent = nullptr;
	GridGraph* mpGridGraph;
	GridPathfinder* mpPathfinder = nullptr;
	Sprite* mpSprite;
	float mMaxAcc;
	float mMaxSpeed;
	float mMaxRotAcc;
	float mMaxRotVel;
	bool mShowTarget;
public:
	bool mShouldDelete = false;

	Unit(GridGraph* pGridGraph, Sprite* sprite);
	virtual ~Unit();

	Unit(Unit&);//invalidate copy constructor
	void operator=(Unit&);//invalidate assignment operator

	friend class UnitManager;
};

#endif