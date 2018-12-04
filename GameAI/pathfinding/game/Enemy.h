#ifndef ENEMY_H_
#define ENEMY_H_

#include "Unit.h"
#include "EventListener.h"
#include "StateMachine.h"

class PlayerMovedEvent;
class EnemyAttackState;
class EnemyFleeState;
class EnemyIdleState;

class Enemy : public Unit
{
	friend class UnitManager;
	friend class EnemyAttackState;
	friend class EnemyFleeState;
	friend class EnemyIdleState;

public:
	virtual void handleEvent(const Event& theEvent);
	virtual void update(float deltaTime);
	virtual void draw() const;

	//void initTargetPos(Vector2D targetPos) { mTargetPosition = targetPos; };

private:
	Enemy(GridGraph* gridGraph);
	virtual ~Enemy();

	//Vector2D mTargetPosition;
	StateMachine* mpEnemyStateMachine;
	EnemyIdleState* mpEnemyIdleState;
	EnemyAttackState* mpEnemyAttackState;
	EnemyFleeState* mpEnemyFleeState;

	StateTransition* mpToEnemyIdleState;
	StateTransition* mpToEnemyAttackState;
	StateTransition* mpToEnemyFleeState;

	void updatePath(const PlayerMovedEvent& theEvent);
	void initStateMachine();
};

#endif