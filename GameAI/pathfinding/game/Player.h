#ifndef PLAYER_H_
#define PLAYER_H_

#include "Unit.h"

class Player : public Unit
{
	friend class UnitManager;

public:
	virtual void handleEvent(const Event& theEvent);
	virtual void update(float deltaTime);
	virtual void draw() const;

	void initTargetPos(Vector2D targetPos) { mTargetPosition = targetPos; };

private:
	Player(GridGraph* gridGraph);
	virtual ~Player();

	Vector2D mTargetPosition;

	void handleInput(const KeyboardEvent& theEvent);
};

#endif