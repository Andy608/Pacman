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
#include "EnemyInactiveState.h"

Enemy::Enemy(GridGraph* gridGraph, Vector2D spawn) :
	Unit(gridGraph, Game::getInstance()->getAssetManager()->getSprite("enemy_idle_sprite")),
	mpEnemyStateMachine(new StateMachine())
{
	EventSystem::addListener(static_cast<Event::EnumEventType>(GameEvent::EnumGameEventType::_PLAYER_MOVED_EVENT), this);

	float enemyRespawnTime = *Game::getInstance()->getAssetManager()->getValue("enemy_respawn_time");
	float enemyFleeTime = *Game::getInstance()->getAssetManager()->getValue("enemy_flee_time");


	mpEnemyIdleState = new EnemyIdleState(0, this);
	mpEnemyAttackState = new EnemyAttackState(1, this);
	mpEnemyFleeState = new EnemyFleeState(2, this, enemyFleeTime);
	mpEnemyInactiveState = new EnemyInactiveState(3, this, spawn, enemyRespawnTime);

	mpToEnemyIdleState = new StateTransition(ENEMY_IDLE_TRANSITION, 0);
	mpToEnemyAttackState = new StateTransition(ENEMY_ATTACK_TRANSITION, 1);
	mpToEnemyFleeState = new StateTransition(ENEMY_FLEE_TRANSITION, 2);
	mpToEnemyInactiveState = new StateTransition(ENEMY_INACTIVE_TRANSITION, 3);

	mpEnemyIdleState->addTransition(mpToEnemyAttackState);

	mpEnemyAttackState->addTransition(mpToEnemyFleeState);

	mpEnemyFleeState->addTransition(mpToEnemyAttackState);
	mpEnemyFleeState->addTransition(mpToEnemyInactiveState);

	mpEnemyInactiveState->addTransition(mpToEnemyAttackState);

	mpEnemyStateMachine->addState(mpEnemyIdleState);
	mpEnemyStateMachine->addState(mpEnemyAttackState);
	mpEnemyStateMachine->addState(mpEnemyFleeState);
	mpEnemyStateMachine->addState(mpEnemyInactiveState);

	mpEnemyStateMachine->setInitialStateID(0);
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

	delete mpEnemyInactiveState;
	mpEnemyInactiveState = nullptr;

	delete mpToEnemyIdleState;
	mpToEnemyIdleState = nullptr;

	delete mpToEnemyAttackState;
	mpToEnemyAttackState = nullptr;

	delete mpToEnemyFleeState;
	mpToEnemyFleeState = nullptr;

	delete mpToEnemyInactiveState;
	mpToEnemyInactiveState = nullptr;
}

void Enemy::handleEvent(const Event& theEvent)
{

}

void Enemy::update(float deltaTime)
{
	mpEnemyStateMachine->update(deltaTime);
}

void Enemy::draw() const
{
	Unit::draw();
}