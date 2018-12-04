#include "ContinuousPathSteering.h"
#include "PathSteering.h"
#include "UnitManager.h"
#include "Game.h"
#include "Unit.h"
#include "GridPathfinder.h"
#include "GraphicsSystem.h"
#include "Grid.h"
#include "Node.h"

ContinuousPathSteering::ContinuousPathSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID) :
	PathSteering(ownerID, targetLoc, targetID)
{
	mType = Steering::CONTINUOUS_PATH;
}

ContinuousPathSteering::~ContinuousPathSteering()
{

}

Steering* ContinuousPathSteering::getSteering()
{
	PathSteering::getSteering();

	Unit* pOwner = Game::getInstance()->getUnitManager()->getUnit(mOwnerID);
	GridPathfinder* pPathfinder = pOwner->getGridPathfinder();
	Path* path = pPathfinder->getPath();

	if (path && targetPathIndex == path->getNumNodes())
	{
		Node* pFromNode = path->peekNode(path->getNumNodes() - 1);
		Node* pToNode = path->peekNode(0);
		path = pPathfinder->findPath(pFromNode, pToNode);
		targetPathIndex = 0;
	}

	return this;
}
