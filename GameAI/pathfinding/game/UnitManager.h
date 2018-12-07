#ifndef UNIT_MANAGER_H_
#define UNIT_MANAGER_H_

#include <Trackable.h>
#include <DeanLibDefines.h>
#include <MemoryPool.h>
#include <map>

#include "PositionComponent.h"
#include "PhysicsComponent.h"
#include "Unit.h"

class Unit;
class GridGraph;
class Sprite;
struct PositionData;
struct PhysicsData;

class Player;
class Candy;
class Coin;
class Enemy;

const UnitID PLAYER_UNIT_ID = 0;

class UnitManager : public Trackable
{
public:
	UnitManager(Uint32 maxSize);
	~UnitManager();

	Unit* createUnit(GridGraph* pGridGraph, Sprite* sprite, bool shouldWrap = true, const PositionData& posData = ZERO_POSITION_DATA, const PhysicsData& physicsData = ZERO_PHYSICS_DATA, const UnitID& id = INVALID_UNIT_ID);
	Enemy* createEnemyUnit(GridGraph* pGridGraph, Vector2D spawn, bool shouldWrap = true, const PositionData& posData = ZERO_POSITION_DATA, const PhysicsData& physicsData = ZERO_PHYSICS_DATA, const UnitID& id = INVALID_UNIT_ID);
	Player* createPlayerUnit(GridGraph* pGridGraph, bool shouldWrap = true, const PositionData& posData = ZERO_POSITION_DATA, const PhysicsData& physicsData = ZERO_PHYSICS_DATA);
	Candy* createCandyUnit(GridGraph* pGridGraph, bool shouldWrap = true, const PositionData& posData = ZERO_POSITION_DATA, const PhysicsData& physicsData = ZERO_PHYSICS_DATA, const UnitID& id = INVALID_UNIT_ID);


	Coin* createCoinUnit(GridGraph* pGridGraph, bool shouldWrap = true, const PositionData& posData = ZERO_POSITION_DATA, const PhysicsData& physicsData = ZERO_PHYSICS_DATA, const UnitID& id = INVALID_UNIT_ID);
	Coin* createRandomCoinUnit(GridGraph* pGridGraph, bool shouldWrap = true, const UnitID& id = INVALID_UNIT_ID);

	Unit* createRandomUnit(GridGraph* pGridGraph, Sprite* sprite);

	Unit* getUnit(const UnitID& id) const;
	void deleteUnit(const UnitID& id);
	void deleteRandomUnit();
	void deleteAllUnits();

	inline const std::map<UnitID, Unit*>& getUnitMap() const { return mUnitMap; };
	inline const int& getUnitCount() const { return mUnitMap.size(); };

	void drawAll() const;
	void updateAll(float elapsedTime);

	Unit* getPlayerUnit() const { return getUnit(PLAYER_UNIT_ID); };

private:
	static UnitID msNextUnitID;
	//MemoryPool mPool;
	std::map<UnitID, Unit*> mUnitMap;
};

#endif
