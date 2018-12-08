#include "ComponentManager.h"
#include "SteeringComponent.h"
#include "ArriveSteering.h"
#include "PathSteering.h"
#include "GridPathSteering.h"
#include "ContinuousPathSteering.h"

SteeringComponent::SteeringComponent(const ComponentID& id, const ComponentID& physicsComponentID) :
	Component(id),
	mPhysicsComponentID(physicsComponentID),
	mpSteering(NULL)
{

}

SteeringComponent::~SteeringComponent()
{
	delete mpSteering;
}

void SteeringComponent::applySteering(PhysicsComponent& physicsComponent)
{
	if (mpSteering != NULL)
	{
		//allow Steering to run
		mpSteering->update();
		//set physics data to that of the Steering
		physicsComponent.setData(mpSteering->getData());
		//update component's data
		mData.targetLoc = mpSteering->getTargetLoc();
	}
}

void SteeringComponent::setData(const SteeringData& data)
{
	mData = data;

	switch (data.type)
	{
	case Steering::ARRIVE:
	{
		delete mpSteering;
		mpSteering = new ArriveSteering(data.ownerID, data.targetLoc, data.targetID);
		break;
	}
	case Steering::PATH:
	{
		delete mpSteering;
		mpSteering = new PathSteering(data.ownerID, data.targetLoc, data.targetID);
		break;
	}
	case Steering::CONTINUOUS_PATH:
	{
		delete mpSteering;
		mpSteering = new ContinuousPathSteering(data.ownerID, data.targetLoc, data.targetID);
		break;
	}
	case Steering::GRID_PATH:
	{
		delete mpSteering;
		mpSteering = new GridPathSteering(data.ownerID, data.targetLoc, data.targetID);
		break;
	}
	default:
	{
		if (mpSteering)
		{
			delete mpSteering;
			mpSteering = nullptr;
		}

		break;
	}
	};
}

