#ifndef ENEMY_IDLE_STATE_H_
#define ENEMY_IDLE_STATE_H_

#include "StateMachine.h"
#include "EventListener.h"

class Enemy;
class PlayerMovedEvent;

class EnemyIdleState : public StateMachineState, public EventListener
{
public:
	EnemyIdleState(const SM_idType& id, Enemy* enemy);

	virtual void onEntrance();
	virtual void onExit();
	virtual StateTransition* update(float deltaTime);

	inline void stopRunning() { mKeepRunning = false; };
	
	virtual void handleEvent(const Event& theEvent);

	void updatePath(const PlayerMovedEvent& theEvent);

private:
	Enemy* mpEnemy;
	bool mKeepRunning;
};

#endif