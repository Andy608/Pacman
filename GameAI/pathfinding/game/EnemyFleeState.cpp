#include "Game.h"
#include "EnemyFleeState.h"
#include <iostream>
#include "Enemy.h"
#include "EventSystem.h"
#include "GameEvent.h"
#include "Grid.h"
#include "UnitManager.h"
#include "AStarFleePathfinder.h"
#include "AssetManager.h"

using namespace std;

EnemyFleeState::EnemyFleeState(const SM_idType& id, Enemy* enemy) :
	StateMachineState(id),
	EventListener(EventSystem::getInstance()),
	mpEnemy(enemy),
	mKeepRunning(false)
{
	EventSystem::addListener(static_cast<Event::EnumEventType>(GameEvent::EnumGameEventType::_PLAYER_MOVED_EVENT), this);
}

void EnemyFleeState::onEntrance()
{
	cout << "\nEntering EnemyFleeState id:" << mID << endl;

	if (mpEnemy->mpPathfinder)
	{
		delete mpEnemy->mpPathfinder;
		mpEnemy->mpPathfinder = nullptr;
	}

	mpEnemy->mpSprite = Game::getInstance()->getAssetManager()->getSprite("enemy_flee_sprite");
	mpEnemy->mpPathfinder = new AStarFleePathfinder(mpEnemy->mpGridGraph, 2);

	mKeepRunning = true;
	updatePath(Game::getInstance()->getUnitManager()->getPlayerUnit()->getPositionComponent()->getPosition());
}

void EnemyFleeState::onExit()
{
	cout << "\nExitting EnemyFleeState id:" << mID << endl;
	mKeepRunning = false;
}

StateTransition* EnemyFleeState::update()
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

void EnemyFleeState::handleEvent(const Event& theEvent)
{
	if (mKeepRunning)
	{
		switch (theEvent.getType())
		{
		case GameEvent::EnumGameEventType::_PLAYER_MOVED_EVENT:
			Vector2D playerPosition = static_cast<const PlayerMovedEvent&>(theEvent).getPlayerPosition();
			updatePath(playerPosition);
			checkIfPlayerInRadius(playerPosition);
			break;
		}
	}
}

void EnemyFleeState::checkIfPlayerInRadius(const Vector2D& playerPosition)
{
	Grid* grid = mpEnemy->mpGridGraph->getGrid();
	Vector2D distance = playerPosition - mpEnemy->getPositionComponent()->getPosition();

	if (distance.getLengthSquared() < grid->getSquareSize() * grid->getSquareSize())
	{
		mpEnemy->mShouldDelete = true;
		//Send event that adds score to player.
		EventSystem::fireEvent(PlayerAteEnemy());
	}
}

void EnemyFleeState::updatePath(const Vector2D& playerPosition)
{
	Grid* grid = mpEnemy->mpGridGraph->getGrid();
	int playerIndex = grid->getSquareIndexFromPosition(playerPosition);
	
	int toIndex = playerIndex;
	int fromIndex = grid->getSquareIndexFromPosition(mpEnemy->getPositionComponent()->getPosition());
	Node* pToNode = mpEnemy->mpGridGraph->getNode(toIndex);
	Node* pFromNode = mpEnemy->mpGridGraph->getNode(fromIndex);
	
	Path* path = mpEnemy->mpPathfinder->findPath(pFromNode, pToNode);
	mpEnemy->setSteering(Steering::CONTINUOUS_PATH, mpEnemy->getPositionComponent()->getPosition());
}