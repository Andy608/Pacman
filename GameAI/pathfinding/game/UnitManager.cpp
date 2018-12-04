#include <map>

#include "UnitManager.h"
#include "Unit.h"
#include "Game.h"
#include "ComponentManager.h"
#include "GraphicsSystem.h"
#include "GridGraph.h"
#include "Grid.h"
#include "Player.h"
#include "Candy.h"
#include "Coin.h"
#include "Enemy.h"

UnitID UnitManager::msNextUnitID = PLAYER_UNIT_ID + 1;

using namespace std;

UnitManager::UnitManager(Uint32 maxSize) //:
	//mPool(maxSize, sizeof(Unit))
{

}

Unit* UnitManager::createUnit(GridGraph* pGridGraph, Sprite* sprite, bool shouldWrap, const PositionData& posData /*= ZERO_POSITION_DATA*/, const PhysicsData& physicsData /*= ZERO_PHYSICS_DATA*/, const UnitID& id)
{
	Unit* pUnit = NULL;

	//Byte* ptr = mPool.allocateObject();
	//if (ptr != NULL)
	//{
		//create unit
		pUnit = new /*(ptr)*/Unit(pGridGraph, sprite);//placement new

		UnitID theID = id;
		if (theID == INVALID_UNIT_ID)
		{
			theID = msNextUnitID;
			msNextUnitID++;
		}

		//place in map
		mUnitMap[theID] = pUnit;

		//assign id and increment nextID counter
		pUnit->mID = theID;

		//create some components
		ComponentManager* pComponentManager = Game::getInstance()->getComponentManager();
		ComponentID compId = pComponentManager->allocatePositionComponent(posData, shouldWrap);
		pUnit->mPositionComponentID = compId;
		pUnit->mpPositionComponent = pComponentManager->getPositionComponent(compId);
		pUnit->mPhysicsComponentID = pComponentManager->allocatePhysicsComponent(pUnit->mPositionComponentID, physicsData);
		pUnit->mSteeringComponentID = pComponentManager->allocateSteeringComponent(pUnit->mPhysicsComponentID);

		//set max's
		pUnit->mMaxSpeed = MAX_SPEED;
		pUnit->mMaxAcc = MAX_ACC;
		pUnit->mMaxRotAcc = MAX_ROT_ACC;
		pUnit->mMaxRotVel = MAX_ROT_VEL;
	//}

	return pUnit;
}

Player* UnitManager::createPlayerUnit(GridGraph* pGridGraph, bool shouldWrap /*= true*/, const PositionData& posData /*= ZERO_POSITION_DATA*/, const PhysicsData& physicsData /*= ZERO_PHYSICS_DATA*/)
{
	Player* pUnit = NULL;

	auto iter = mUnitMap.find(PLAYER_UNIT_ID);
	if (iter != mUnitMap.end())
	{
		return static_cast<Player*>(iter->second);
	}

	/*Byte* ptr = mPool.allocateObject();
	if (ptr != NULL)
	{*/
		//create unit
		pUnit = new /*(ptr)*/Player(pGridGraph);

		//place in map
		mUnitMap[PLAYER_UNIT_ID] = pUnit;

		//assign id and increment nextID counter
		pUnit->mID = PLAYER_UNIT_ID;

		//create some components
		ComponentManager* pComponentManager = Game::getInstance()->getComponentManager();
		ComponentID compId = pComponentManager->allocatePositionComponent(posData, shouldWrap);
		pUnit->mPositionComponentID = compId;
		pUnit->mpPositionComponent = pComponentManager->getPositionComponent(compId);
		pUnit->mPhysicsComponentID = pComponentManager->allocatePhysicsComponent(pUnit->mPositionComponentID, physicsData);
		pUnit->mSteeringComponentID = pComponentManager->allocateSteeringComponent(pUnit->mPhysicsComponentID);

		//set max's
		pUnit->mMaxSpeed = MAX_SPEED;
		pUnit->mMaxAcc = MAX_ACC;
		pUnit->mMaxRotAcc = MAX_ROT_ACC;
		pUnit->mMaxRotVel = MAX_ROT_VEL;
	//}

	return pUnit;
}

Enemy* UnitManager::createEnemyUnit(GridGraph* pGridGraph, bool shouldWrap, const PositionData& posData /*= ZERO_POSITION_DATA*/, const PhysicsData& physicsData /*= ZERO_PHYSICS_DATA*/, const UnitID& id)
{
	Enemy* pUnit = NULL;

	/*Byte* ptr = mPool.allocateObject();
	if (ptr != NULL)
	{*/
		//create unit
		pUnit = new /*(ptr)*/Enemy(pGridGraph);//placement new

		UnitID theID = id;
		if (theID == INVALID_UNIT_ID)
		{
			theID = msNextUnitID;
			msNextUnitID++;
		}

		//place in map
		mUnitMap[theID] = pUnit;

		//assign id and increment nextID counter
		pUnit->mID = theID;

		//create some components
		ComponentManager* pComponentManager = Game::getInstance()->getComponentManager();
		ComponentID compId = pComponentManager->allocatePositionComponent(posData, shouldWrap);
		pUnit->mPositionComponentID = compId;
		pUnit->mpPositionComponent = pComponentManager->getPositionComponent(compId);
		pUnit->mPhysicsComponentID = pComponentManager->allocatePhysicsComponent(pUnit->mPositionComponentID, physicsData);
		pUnit->mSteeringComponentID = pComponentManager->allocateSteeringComponent(pUnit->mPhysicsComponentID);

		//set max's
		pUnit->mMaxSpeed = MAX_SPEED;
		pUnit->mMaxAcc = MAX_ACC;
		pUnit->mMaxRotAcc = MAX_ROT_ACC;
		pUnit->mMaxRotVel = MAX_ROT_VEL;
	//}

	return pUnit;
}

Candy* UnitManager::createCandyUnit(GridGraph* pGridGraph, bool shouldWrap /*= true*/, const PositionData& posData /*= ZERO_POSITION_DATA*/, const PhysicsData& physicsData /*= ZERO_PHYSICS_DATA*/, const UnitID& id)
{
	Candy* pUnit = NULL;

	/*Byte* ptr = mPool.allocateObject();
	if (ptr != NULL)
	{*/
		//create unit
		pUnit = new /*(ptr)*/Candy(pGridGraph);//placement new

		UnitID theID = id;
		if (theID == INVALID_UNIT_ID)
		{
			theID = msNextUnitID;
			msNextUnitID++;
		}

		//place in map
		mUnitMap[theID] = pUnit;

		//assign id and increment nextID counter
		pUnit->mID = theID;

		//create some components
		ComponentManager* pComponentManager = Game::getInstance()->getComponentManager();
		ComponentID compId = pComponentManager->allocatePositionComponent(posData, shouldWrap);
		pUnit->mPositionComponentID = compId;
		pUnit->mpPositionComponent = pComponentManager->getPositionComponent(compId);
		pUnit->mPhysicsComponentID = pComponentManager->allocatePhysicsComponent(pUnit->mPositionComponentID, physicsData);
		pUnit->mSteeringComponentID = pComponentManager->allocateSteeringComponent(pUnit->mPhysicsComponentID);

		//set max's
		pUnit->mMaxSpeed = MAX_SPEED;
		pUnit->mMaxAcc = MAX_ACC;
		pUnit->mMaxRotAcc = MAX_ROT_ACC;
		pUnit->mMaxRotVel = MAX_ROT_VEL;
	//}

	return pUnit;
}

Coin* UnitManager::createCoinUnit(GridGraph* pGridGraph, bool shouldWrap /*= true*/, const PositionData& posData /*= ZERO_POSITION_DATA*/, const PhysicsData& physicsData /*= ZERO_PHYSICS_DATA*/, const UnitID& id)
{
	Coin* pUnit = NULL;

	/*Byte* ptr = mPool.allocateObject();
	if (ptr != NULL)
	{*/
		//create unit
		pUnit = new /*(ptr)*/Coin(pGridGraph);//placement new

		UnitID theID = id;
		if (theID == INVALID_UNIT_ID)
		{
			theID = msNextUnitID;
			msNextUnitID++;
		}

		//place in map
		mUnitMap[theID] = pUnit;

		//assign id and increment nextID counter
		pUnit->mID = theID;

		//create some components
		ComponentManager* pComponentManager = Game::getInstance()->getComponentManager();
		ComponentID compId = pComponentManager->allocatePositionComponent(posData, shouldWrap);
		pUnit->mPositionComponentID = compId;
		pUnit->mpPositionComponent = pComponentManager->getPositionComponent(compId);
		pUnit->mPhysicsComponentID = pComponentManager->allocatePhysicsComponent(pUnit->mPositionComponentID, physicsData);
		pUnit->mSteeringComponentID = pComponentManager->allocateSteeringComponent(pUnit->mPhysicsComponentID);

		//set max's
		pUnit->mMaxSpeed = MAX_SPEED;
		pUnit->mMaxAcc = MAX_ACC;
		pUnit->mMaxRotAcc = MAX_ROT_ACC;
		pUnit->mMaxRotVel = MAX_ROT_VEL;
	//}

	return pUnit;
}

Coin* UnitManager::createRandomCoinUnit(GridGraph* pGridGraph, bool shouldWrap /*= true*/, const UnitID& id)
{
	Coin* pUnit = NULL;

	/*Byte* ptr = mPool.allocateObject();
	if (ptr != NULL)
	{*/
		//create unit
		pUnit = new /*(ptr)*/Coin(pGridGraph);//placement new

		UnitID theID = id;
		if (theID == INVALID_UNIT_ID)
		{
			theID = msNextUnitID;
			msNextUnitID++;
		}

		//place in map
		mUnitMap[theID] = pUnit;

		//assign id and increment nextID counter
		pUnit->mID = theID;

		int posX;
		int posY;
		Grid* grid = pGridGraph->getGrid();

		do
		{
			posX = (rand() % grid->getGridWidth()) * grid->getSquareSize();
			posY = (rand() % grid->getGridHeight()) * grid->getSquareSize();

		} while (/*grid->getValueAtPixelXY((int)posX, (int)posY) != grid->sFLOOR_ID && */!grid->isIndexFree(grid->getSquareIndexFromPixelXY(posX, posY)));

		grid->setIndexFree(grid->getSquareIndexFromPixelXY(posX, posY), false);

		//create some components
		ComponentManager* pComponentManager = Game::getInstance()->getComponentManager();
		ComponentID compId = pComponentManager->allocatePositionComponent(PositionData(Vector2D(posX, posY), shouldWrap));
		pUnit->mPositionComponentID = compId;
		pUnit->mpPositionComponent = pComponentManager->getPositionComponent(compId);
		pUnit->mPhysicsComponentID = pComponentManager->allocatePhysicsComponent(pUnit->mPositionComponentID, ZERO_PHYSICS_DATA);
		pUnit->mSteeringComponentID = pComponentManager->allocateSteeringComponent(pUnit->mPhysicsComponentID);

		//set max's
		pUnit->mMaxSpeed = MAX_SPEED;
		pUnit->mMaxAcc = MAX_ACC;
		pUnit->mMaxRotAcc = MAX_ROT_ACC;
		pUnit->mMaxRotVel = MAX_ROT_VEL;
	//}

	return pUnit;
}

Unit* UnitManager::createRandomUnit(GridGraph* pGridGraph, Sprite* sprite)
{
	int posX;
	int posY;
	Grid* grid = pGridGraph->getGrid();

	do
	{
		posX = (rand() % grid->getGridWidth()) * grid->getSquareSize();
		posY = (rand() % grid->getGridHeight()) * grid->getSquareSize();

	} while (grid->getValueAtPixelXY((int)posX, (int)posY) != grid->sFLOOR_ID);

	Unit* pUnit = createUnit(pGridGraph, sprite, true, PositionData(Vector2D(posX, posY), 0));

	if (pUnit != NULL)
	{
		pUnit->setSteering(Steering::PATH, Vector2D(rand() % GraphicsSystem::getInstance()->getDisplayWidth(), rand() % GraphicsSystem::getInstance()->getDisplayHeight()));
	}

	return pUnit;
}

Unit* UnitManager::getUnit(const UnitID& id) const
{
	auto it = mUnitMap.find(id);

	if (it != mUnitMap.end())//found?
	{
		return it->second;
	}
	else
	{
		return NULL;
	}
}

UnitManager::~UnitManager() 
{
	auto itr = mUnitMap.begin();
	while (itr != mUnitMap.end())
	{
		Unit* unit = itr->second;
		itr = mUnitMap.erase(itr);
		delete unit;
		unit = nullptr;
	}
}

void UnitManager::deleteUnit(const UnitID& id)
{
	auto it = mUnitMap.find(id);

	if (it != mUnitMap.end())//found?
	{
		Unit* pUnit = it->second;//hold for later

								 //remove from map
		mUnitMap.erase(it);

		//remove components
		ComponentManager* pComponentManager = Game::getInstance()->getComponentManager();
		pComponentManager->deallocatePhysicsComponent(pUnit->mPhysicsComponentID);
		pComponentManager->deallocatePositionComponent(pUnit->mPositionComponentID);
		pComponentManager->deallocateSteeringComponent(pUnit->mSteeringComponentID);

		//call destructor
		/*pUnit->~Unit();*/
		delete pUnit;
		pUnit = nullptr;

		//free the object in the pool
		//mPool.freeObject((Byte*)pUnit);
	}
}

void UnitManager::deleteRandomUnit()
{
	if (mUnitMap.size() >= 1)
	{
		Uint32 target = rand() % mUnitMap.size();
		//if (target == 0)//don't allow the 0th element to be deleted as it is the player unit
		//{
		//	target = 1;
		//}

		Uint32 cnt = 0;
		for (auto it = mUnitMap.begin(); it != mUnitMap.end(); ++it, cnt++)
		{
			if (cnt == target)
			{
				deleteUnit(it->first);
				break;
			}
		}
	}
}

void UnitManager::drawAll() const
{
	for (auto it = mUnitMap.begin(); it != mUnitMap.end(); ++it)
	{
		if (it == mUnitMap.begin()) continue;

		it->second->draw();
	}

	if (mUnitMap.begin() != mUnitMap.end())
	{
		mUnitMap.begin()->second->draw();
	}
}

void UnitManager::updateAll(float elapsedTime)
{
	for (auto it = mUnitMap.begin(); it != mUnitMap.end(); ++it)
	{
		if (it->second->mShouldDelete)
		{
			Unit* unit = it->second;
			it = mUnitMap.erase(it);
			delete unit;
			unit = nullptr;
		}
		else
		{
			it->second->update(elapsedTime);
		}
	}
}