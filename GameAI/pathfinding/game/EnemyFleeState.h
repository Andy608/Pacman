#ifndef ENEMY_FLEE_STATE_H_
#define ENEMY_FLEE_STATE_H_

#include "StateMachine.h"
#include "EventListener.h"

class Enemy;

class EnemyFleeState : public StateMachineState, public EventListener
{
public:
	EnemyFleeState(const SM_idType& id, Enemy* enemy, float fleeTime);

	virtual void onEntrance();
	virtual void onExit();
	virtual StateTransition* update(float deltaTime);

	virtual void handleEvent(const Event& theEvent);

	bool isPlayerInRadius(const Vector2D& playerPosition);
	void updatePath(const Vector2D& playerPosition);

private:
	Enemy* mpEnemy;
	bool mIsRunning;
	float mFleeTime;
	float mFleeCount;
};

#endif