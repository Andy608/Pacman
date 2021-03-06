#include "Game.h"
#include "EnemyIdleState.h"
#include <iostream>
#include "Enemy.h"
#include "EventSystem.h"
#include "GameEvent.h"
#include "Grid.h"
#include "UnitManager.h"
#include "AssetManager.h"

using namespace std;

EnemyIdleState::EnemyIdleState(const SM_idType& id, Enemy* enemy) :
	StateMachineState(id),
	EventListener(EventSystem::getInstance()),
	mpEnemy(enemy),
	mKeepRunning(false)
{
	EventSystem::addListener(static_cast<Event::EnumEventType>(GameEvent::EnumGameEventType::_PLAYER_MOVED_EVENT), this);
}

void EnemyIdleState::onEntrance()
{
	cout << "\nEntering EnemyIdleState id:" << mID << endl;
	mKeepRunning = true;

	if (mpEnemy->mpPathfinder)
	{
		delete mpEnemy->mpPathfinder;
		mpEnemy->mpPathfinder = nullptr;
	}

	mpEnemy->mpSprite = Game::getInstance()->getAssetManager()->getSprite("enemy_idle_sprite");
}

void EnemyIdleState::onExit()
{
	cout << "\nExitting EnemyIdleState id:" << mID << endl;
	mKeepRunning = false;
}

StateTransition* EnemyIdleState::update(float deltaTime)
{
	if (!mKeepRunning)
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

void EnemyIdleState::handleEvent(const Event& theEvent)
{
	if (mKeepRunning)
	{
		switch (theEvent.getType())
		{
		case GameEvent::EnumGameEventType::_PLAYER_MOVED_EVENT:
		{
			stopRunning();
			break;
		}
		}
	}
}

void EnemyIdleState::updatePath(const PlayerMovedEvent& theEvent)
{
	mpEnemy->setSteering(Steering::INVALID_TYPE);
}