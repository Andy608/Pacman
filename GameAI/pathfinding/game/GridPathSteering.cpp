#include <cassert>

#include "GridPathSteering.h"
#include "UnitManager.h"
#include "Game.h"
#include "Unit.h"
#include "GridPathfinder.h"
#include "GraphicsSystem.h"
#include "Grid.h"
#include "Node.h"

GridPathSteering::GridPathSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID) :
	Steering(Steering::PATH, ownerID, targetLoc, targetID),
	targetPathIndex(0)
{
	Unit* pOwner = Game::getInstance()->getUnitManager()->getUnit(mOwnerID);
	currentPosition = pOwner->getPositionComponent()->getPosition();
}

GridPathSteering::~GridPathSteering()
{
}

Steering* GridPathSteering::getSteering()
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
		float targetRadiusSquared = (float)pGrid->getSquareSize();

		//Vector2D target = pGrid->getULCornerOfSquare(path->peekNode(0)->getId());
		//mArriveSteering.setTargetLoc(target);

		Vector2D distance = mTargetLoc - currentPosition;
		std::cout << "distance: " << distance.getLengthSquared() << std::endl;

		if (distance.getLengthSquared() > targetRadiusSquared)
		{
			direction.normalize();
			direction *= 2.0f;
			currentPosition += direction;
		}
		else
		{
			pOwner->getPositionComponent()->setPosition(mTargetLoc);
			currentPosition = mTargetLoc;

			if (path->peekNode(targetPathIndex) != nullptr)
			{
				Vector2D target = pGrid->getULCornerOfSquare(path->peekNode(targetPathIndex)->getId());
				setTargetLoc(target);
				++targetPathIndex;
			}
		}

		pPathfinder->setPath(path);
	}

	//this->mData = data;
	return this;
}
