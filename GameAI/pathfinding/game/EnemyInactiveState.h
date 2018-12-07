#ifndef ENEMY_INACTIVE_STATE_H_
#define ENEMY_INACTIVE_STATE_H_

#include "StateMachine.h"
#include "EventListener.h"

class Enemy;

class EnemyInactiveState : public StateMachineState, public EventListener
{
public:
	EnemyInactiveState(const SM_idType& id, Enemy* enemy, Vector2D spawn, float respawnTime);

	virtual void onEntrance();
	virtual void onExit();
	virtual StateTransition* update(float deltaTime);

	virtual void handleEvent(const Event& theEvent);

private:
	Enemy* mpEnemy;
	Vector2D mSpawn;
	float mRespawnTime;
	float mRespawnCount;
};

#endif