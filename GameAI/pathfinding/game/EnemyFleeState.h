#ifndef ENEMY_FLEE_STATE_H_
#define ENEMY_FLEE_STATE_H_

#include "StateMachine.h"
#include "EventListener.h"

class Enemy;

class EnemyFleeState : public StateMachineState, public EventListener
{
public:
	EnemyFleeState(const SM_idType& id, Enemy* enemy);

	virtual void onEntrance();
	virtual void onExit();
	virtual StateTransition* update();

	inline void stopRunning() { mKeepRunning = false; };

	virtual void handleEvent(const Event& theEvent);

	void checkIfPlayerInRadius(const Vector2D& playerPosition);
	void updatePath(const Vector2D& playerPosition);

private:
	Enemy* mpEnemy;
	bool mKeepRunning;
};

#endif