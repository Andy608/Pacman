#include "Game.h"
#include "EnemyAttackState.h"
#include <iostream>
#include "Enemy.h"
#include "Grid.h"
#include "GameEvent.h"
#include "EventSystem.h"
#include "AStarPathfinder.h"
#include "UnitManager.h"
#include "AssetManager.h"

using namespace std;

EnemyAttackState::EnemyAttackState(const SM_idType& id, Enemy* enemy) :
	StateMachineState(id),
	EventListener(EventSystem::getInstance()),
	mpEnemy(enemy),
	mKeepRunning(false)
{
	EventSystem::addListener(static_cast<Event::EnumEventType>(GameEvent::EnumGameEventType::_PLAYER_MOVED_EVENT), this);
	EventSystem::addListener(static_cast<Event::EnumEventType>(GameEvent::EnumGameEventType::_PLAYER_ATE_CANDY_EVENT), this);
}

void EnemyAttackState::onEntrance()
{
	cout << "\nEntering EnemyAttackState id:" << mID << endl;
	
	if (mpEnemy->mpPathfinder)
	{
		delete mpEnemy->mpPathfinder;
	}

	mpEnemy->mpSprite = Game::getInstance()->getAssetManager()->getSprite("enemy_attack_sprite");
	mpEnemy->mpPathfinder = new AStarPathfinder(mpEnemy->mpGridGraph);
	mKeepRunning = true;
	updatePath(Game::getInstance()->getUnitManager()->getPlayerUnit()->getPositionComponent()->getPosition());
}

void EnemyAttackState::onExit()
{
	cout << "\nExitting EnemyAttackState id:" << mID << endl;
	mKeepRunning = false;
}

StateTransition* EnemyAttackState::update()
{
	if (!mKeepRunning)
	{
		//find the right transition
		map<TransitionType, StateTransition*>::iterator iter = mTransitions.find(ENEMY_FLEE_TRANSITION);
		if (iter != mTransitions.end())//found?
		{
			StateTransition* pTransition = iter->second;
			return pTransition;
		}
	}

	return NULL;//no transition
}

void EnemyAttackState::handleEvent(const Event& theEvent)
{
	if (mKeepRunning)
	{
		switch (theEvent.getType())
		{
		case GameEvent::EnumGameEventType::_PLAYER_MOVED_EVENT:
			updatePath(static_cast<const PlayerMovedEvent&>(theEvent).getPlayerPosition());
			break;
		case GameEvent::EnumGameEventType::_PLAYER_ATE_CANDY_EVENT:
			stopRunning();
			break;
		}
	}
}

void EnemyAttackState::updatePath(const Vector2D& playerPosition)
{
	Grid* grid = mpEnemy->getGridGraph()->getGrid();

	int toIndex = grid->getSquareIndexFromPosition(playerPosition);
	int fromIndex = grid->getSquareIndexFromPosition(mpEnemy->getPositionComponent()->getPosition());
	Node* pToNode = mpEnemy->getGridGraph()->getNode(toIndex);
	Node* pFromNode = mpEnemy->getGridGraph()->getNode(fromIndex);

	Path* path = mpEnemy->getGridPathfinder()->findPath(pFromNode, pToNode);
	mpEnemy->setSteering(Steering::CONTINUOUS_PATH, mpEnemy->getPositionComponent()->getPosition());
}