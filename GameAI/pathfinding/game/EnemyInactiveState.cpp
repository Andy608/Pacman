#include "Game.h"
#include "EnemyInactiveState.h"
#include <iostream>
#include "Enemy.h"
#include "EventSystem.h"
#include "GameEvent.h"
#include "Grid.h"
#include "UnitManager.h"
#include "AssetManager.h"

using namespace std;

EnemyInactiveState::EnemyInactiveState(const SM_idType& id, Enemy* enemy, Vector2D spawn, float respawnTime) :
	StateMachineState(id),
	EventListener(EventSystem::getInstance()),
	mpEnemy(enemy),
	mSpawn(spawn),
	mRespawnTime(respawnTime)
{

}

void EnemyInactiveState::onEntrance()
{
	cout << "\nEntering EnemyInactiveState id:" << mID << endl;

	if (mpEnemy->mpPathfinder)
	{
		delete mpEnemy->mpPathfinder;
		mpEnemy->mpPathfinder = nullptr;
	}

	mRespawnCount = 0.0f;

	mpEnemy->mpSprite = nullptr;
	mpEnemy->setSteering(Steering::INVALID_TYPE);
	mpEnemy->getPhysicsComponent()->setData(PhysicsData());
	mpEnemy->getPositionComponent()->setPosition(mSpawn);
}

void EnemyInactiveState::onExit()
{
	cout << "\nExitting EnemyInactiveState id:" << mID << endl;
}

StateTransition* EnemyInactiveState::update(float deltaTime)
{
	mRespawnCount += deltaTime;

	if (mRespawnCount >= mRespawnTime)
	{
		//find the right transition
		map<TransitionType, StateTransition*>::iterator iter = mTransitions.find(ENEMY_ATTACK_TRANSITION);
		if (iter != mTransitions.end())//found?
		{
			StateTransition* pTransition = iter->second;
			return pTransition;
		}
	}

	return NULL;//no transition
}

void EnemyInactiveState::handleEvent(const Event& theEvent)
{
}