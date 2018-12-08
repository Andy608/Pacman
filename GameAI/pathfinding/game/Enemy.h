#ifndef ENEMY_H_
#define ENEMY_H_

#include "Unit.h"
#include "EventListener.h"
#include "StateMachine.h"

class PlayerMovedEvent;
class EnemyAttackState;
class EnemyFleeState;
class EnemyIdleState;
class EnemyInactiveState;

class Enemy : public Unit
{
	friend class UnitManager;
	friend class EnemyAttackState;
	friend class EnemyFleeState;
	friend class EnemyIdleState;
	friend class EnemyInactiveState;

public:
	virtual void handleEvent(const Event& theEvent);
	virtual void update(float deltaTime);
	virtual void draw() const;

private:
	Enemy(GridGraph* gridGraph, Vector2D spawn);
	virtual ~Enemy();

	StateMachine* mpEnemyStateMachine;
	EnemyIdleState* mpEnemyIdleState;
	EnemyAttackState* mpEnemyAttackState;
	EnemyFleeState* mpEnemyFleeState;
	EnemyInactiveState* mpEnemyInactiveState;

	StateTransition* mpToEnemyIdleState;
	StateTransition* mpToEnemyAttackState;
	StateTransition* mpToEnemyFleeState;
	StateTransition* mpToEnemyInactiveState;
};

#endif