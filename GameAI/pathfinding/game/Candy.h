#ifndef CANDY_H_
#define CANDY_H_

#include "Item.h"

class PlayerMovedEvent;

class Candy : public Item
{
	friend class UnitManager;

public:
	virtual void handleEvent(const Event& theEvent);
	void checkIfPlayerInRadius(const Vector2D& theEvent);

protected:
	Candy(GridGraph* gridGraph);
	virtual ~Candy();
};

#endif