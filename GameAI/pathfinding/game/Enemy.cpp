#include "Enemy.h"
#include "EventSystem.h"
#include "Game.h"
#include "AssetManager.h"
#include "Grid.h"
#include "GameEvent.h"
#include "SteeringComponent.h"
#include "EnemyAttackState.h"
#include "EnemyFleeState.h"
#include "EnemyIdleState.h"

Enemy::Enemy(GridGraph* gridGraph) :
	Unit(gridGraph, Game::getInstance()->getAssetManager()->getSprite("enemy_idle_sprite")),
	mpEnemyStateMachine(new StateMachine())
{
	initStateMachine();

	EventSystem::addListener(static_cast<Event::EnumEventType>(GameEvent::EnumGameEventType::_PLAYER_MOVED_EVENT), this);
}

Enemy::~Enemy()
{
	delete mpEnemyStateMachine;
	mpEnemyStateMachine = nullptr;

	delete mpEnemyIdleState;
	mpEnemyIdleState = nullptr;

	delete mpEnemyAttackState;
	mpEnemyAttackState = nullptr;

	delete mpEnemyFleeState;
	mpEnemyFleeState = nullptr;

	delete mpToEnemyIdleState;
	mpToEnemyIdleState = nullptr;

	delete mpToEnemyAttackState;
	mpToEnemyAttackState = nullptr;

	delete mpToEnemyFleeState;
	mpToEnemyFleeState = nullptr;

}

void Enemy::handleEvent(const Event& theEvent)
{

}

void Enemy::update(float deltaTime)
{
	mpEnemyStateMachine->update();
}

void Enemy::draw() const
{
	Unit::draw();
	//mpPathfinder->drawVisualization(mpGridGraph->getGrid());
}

void Enemy::updatePath(const PlayerMovedEvent& theEvent)
{
	//int playerIndex = theEvent.getPlayerGridIndex();
	//Grid* grid = mpGridGraph->getGrid();
	//
	//int toIndex = playerIndex;
	//int fromIndex = grid->getSquareIndexFromPosition(getPositionComponent()->getPosition());
	//Node* pToNode = mpGridGraph->getNode(toIndex);
	//Node* pFromNode = mpGridGraph->getNode(fromIndex);
	//
	//Path* path = mpPathfinder->findPath(pFromNode, pToNode);
	//setSteering(Steering::CONTINUOUS_PATH, getPositionComponent()->getPosition());
}

void Enemy::initStateMachine()
{
	mpEnemyIdleState = new EnemyIdleState(0, this);
	mpEnemyAttackState = new EnemyAttackState(1, this);
	mpEnemyFleeState = new EnemyFleeState(2, this);

	mpToEnemyIdleState = new StateTransition(ENEMY_IDLE_TRANSITION, 0);
	mpToEnemyAttackState = new StateTransition(ENEMY_ATTACK_TRANSITION, 1);
	mpToEnemyFleeState = new StateTransition(ENEMY_FLEE_TRANSITION, 2);

	mpEnemyIdleState->addTransition(mpToEnemyAttackState);
	mpEnemyIdleState->addTransition(mpToEnemyFleeState);

	mpEnemyAttackState->addTransition(mpToEnemyFleeState);
	
	mpEnemyFleeState->addTransition(mpToEnemyAttackState);

	mpEnemyStateMachine->addState(mpEnemyIdleState);
	mpEnemyStateMachine->addState(mpEnemyAttackState);
	mpEnemyStateMachine->addState(mpEnemyFleeState);

	mpEnemyStateMachine->setInitialStateID(0);
}