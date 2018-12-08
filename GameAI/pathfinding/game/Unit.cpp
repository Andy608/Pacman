#include "Unit.h"
#include <assert.h>

#include "Game.h"
#include "GraphicsSystem.h"
#include "Component.h"
#include "PositionComponent.h"
#include "PhysicsComponent.h"
#include "SteeringComponent.h"
#include "ComponentManager.h"
#include "EventSystem.h"
#include "AStarPathfinder.h"

Unit::Unit(GridGraph* pGridGraph, Sprite* sprite) :
	EventListener(EventSystem::getInstance()),
	mpSprite(sprite),
	mPositionComponentID(INVALID_COMPONENT_ID),
	mPhysicsComponentID(INVALID_COMPONENT_ID),
	mSteeringComponentID(INVALID_COMPONENT_ID),
	mShowTarget(false),
	mpGridGraph(pGridGraph),
	mpPathfinder(new AStarPathfinder(mpGridGraph))
{

}

Unit::~Unit()
{
	if (mpPathfinder)
	{
		delete mpPathfinder;
		mpPathfinder = nullptr;
	}
}

void Unit::handleEvent(const Event& theEvent) {}

void Unit::draw() const
{
	PositionComponent* pPosition = getPositionComponent();
	assert(pPosition != NULL);
	const Vector2D& pos = pPosition->getPosition();

	if (mpSprite)
	{
		GraphicsSystem::getInstance()->draw(pos.getX(), pos.getY(), *mpSprite);
	}
}

float Unit::getFacing() const
{
	PositionComponent* pPosition = getPositionComponent();
	assert(pPosition != NULL);
	return pPosition->getFacing();
}

PositionComponent* Unit::getPositionComponent() const
{
	return mpPositionComponent;
}

PhysicsComponent* Unit::getPhysicsComponent() const
{
	PhysicsComponent* pComponent = Game::getInstance()->getComponentManager()->getPhysicsComponent(mPhysicsComponentID);
	return pComponent;
}

SteeringComponent* Unit::getSteeringComponent() const
{
	SteeringComponent* pComponent = Game::getInstance()->getComponentManager()->getSteeringComponent(mSteeringComponentID);
	return pComponent;
}

void Unit::setSteering(Steering::SteeringType type, Vector2D targetLoc /*= ZERO_VECTOR2D*/, UnitID targetUnitID /*= INVALID_UNIT_ID*/)
{
	SteeringComponent* pSteeringComponent = getSteeringComponent();
	if (pSteeringComponent != NULL)
	{
		pSteeringComponent->setData(SteeringData(type, targetLoc, mID, targetUnitID));
	}
}