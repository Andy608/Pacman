#ifndef ENEMY_ATTACK_STATE_H_
#define ENEMY_ATTACK_STATE_H_

#include "StateMachine.h"
#include "EventListener.h"

class Enemy;
class PlayerMovedEvent;

class EnemyAttackState : public StateMachineState, public EventListener
{
public:
	EnemyAttackState(const SM_idType& id, Enemy* enemy);

	virtual void onEntrance();
	virtual void onExit();
	virtual StateTransition* update();

	inline void stopRunning() { mKeepRunning = false; };

	virtual void handleEvent(const Event& theEvent);

	void updatePath(const Vector2D& playerPosition);

private:
	Enemy* mpEnemy;
	bool mKeepRunning;
};

#endif