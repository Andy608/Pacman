#ifndef ITEM_H_
#define ITEM_H_

#include "Unit.h"
#include "EventListener.h"

class Item : public Unit
{
public:
	virtual void handleEvent(const Event& theEvent);

protected:
	Item(GridGraph* gridGraph, Sprite* sprite);
	virtual ~Item();
};

#endif