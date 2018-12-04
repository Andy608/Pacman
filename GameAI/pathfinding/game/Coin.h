#ifndef COIN_H_
#define COIN_H_

#include "Item.h"

class PlayerMovedEvent;

class Coin : public Item
{
	friend class UnitManager;

public:
	virtual void handleEvent(const Event& theEvent);

protected:
	Coin(GridGraph* gridGraph);
	virtual ~Coin();

	void checkIfPlayerInRadius(const PlayerMovedEvent& theEvent);
};

#endif