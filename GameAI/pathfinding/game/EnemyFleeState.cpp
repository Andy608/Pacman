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

EnemyFleeState::EnemyFleeState(const SM_idType& id, Enemy* enemy, float fleeTime) :
	StateMachineState(id),
	EventListener(EventSystem::getInstance()),
	mpEnemy(enemy),
	mFleeTime(fleeTime),
	mIsRunning(false)
{
	EventSystem::addListener(static_cast<Event::EnumEventType>(GameEvent::EnumGameEventType::_PLAYER_MOVED_EVENT), this);
	EventSystem::addListener(static_cast<Event::EnumEventType>(GameEvent::EnumGameEventType::_PLAYER_ATE_CANDY_EVENT), this);
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

	updatePath(Game::getInstance()->getUnitManager()->getPlayerUnit()->getPositionComponent()->getPosition());
	mFleeCount = 0.0f;

	mIsRunning = true;
}

void EnemyFleeState::onExit()
{
	cout << "\nExitting EnemyFleeState id:" << mID << endl;
	mIsRunning = false;
}

StateTransition* EnemyFleeState::update(float deltaTime)
{
	map<TransitionType, StateTransition*>::iterator iter = mTransitions.end();

	mFleeCount += deltaTime;

	const Vector2D& pos = Game::getInstance()->getUnitManager()->getPlayerUnit()->getPositionComponent()->getPosition();
	if (isPlayerInRadius(pos))
	{
		iter = mTransitions.find(ENEMY_INACTIVE_TRANSITION);
		EventSystem::fireEvent(PlayerAteEnemy());
	}
	else if (mFleeCount >= mFleeTime)
	{
		iter = mTransitions.find(ENEMY_ATTACK_TRANSITION);
	}

	if (iter != mTransitions.end())//found?
	{
		StateTransition* pTransition = iter->second;
		return pTransition;
	}

	return NULL;//no transition
}

void EnemyFleeState::handleEvent(const Event& theEvent)
{
	if (mIsRunning)
	{
		switch (theEvent.getType())
		{
		case GameEvent::EnumGameEventType::_PLAYER_MOVED_EVENT:
		{
			Vector2D playerPosition = static_cast<const PlayerMovedEvent&>(theEvent).getPlayerPosition();
			updatePath(playerPosition);
			break;
		}
		case GameEvent::EnumGameEventType::_PLAYER_ATE_CANDY_EVENT:
		{
			mFleeCount = 0.0f;
		}
		}
	}
}

bool EnemyFleeState::isPlayerInRadius(const Vector2D& playerPosition)
{
	Grid* grid = mpEnemy->mpGridGraph->getGrid();
	Vector2D distance = playerPosition - mpEnemy->getPositionComponent()->getPosition();
	static const float RADIUS = grid->getSquareSize() * grid->getSquareSize() / 2.0f;

	if (distance.getLengthSquared() < RADIUS)
	{
		return true;
	}

	return false;
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