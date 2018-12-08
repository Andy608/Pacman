#include <cassert>

#include "PathSteering.h"
#include "UnitManager.h"
#include "Game.h"
#include "Unit.h"
#include "GridPathfinder.h"
#include "GraphicsSystem.h"
#include "Grid.h"
#include "Node.h"

PathSteering::PathSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID) :
	Steering(Steering::PATH, ownerID, targetLoc, targetID),
	mArriveSteering(ArriveSteering(ownerID, targetLoc, targetID)),
	targetPathIndex(0)
{

}

PathSteering::~PathSteering()
{
}

Steering* PathSteering::getSteering()
{
	Unit* pOwner = Game::getInstance()->getUnitManager()->getUnit(mOwnerID);
	Grid* pGrid = pOwner->getGridGraph()->getGrid();
	PhysicsData data = pOwner->getPhysicsComponent()->getData();
	GridPathfinder* pPathfinder = pOwner->getGridPathfinder();
	Path* path = pPathfinder->getPath();

	if (path && path->getNumNodes() > 0)
	{
		pPathfinder->drawVisualization(pGrid);

		Vector2D direction = mTargetLoc - pOwner->getPositionComponent()->getPosition();
		float targetRadiusSquared = 60 * 60;

		if (direction.getLengthSquared() < targetRadiusSquared && path->peekNode(targetPathIndex) != nullptr)
		{
			Vector2D target = pGrid->getULCornerOfSquare(path->peekNode(targetPathIndex)->getId());
			setTargetLoc(target);
			mArriveSteering.setTargetLoc(target);
			++targetPathIndex;
		}
	}

	Steering* steering = mArriveSteering.getSteering();
	data.acc = steering->getData().acc;
	data.vel = steering->getData().vel;
	data.rotAcc = steering->getData().rotAcc;

	this->mData = data;
	return this;
}
