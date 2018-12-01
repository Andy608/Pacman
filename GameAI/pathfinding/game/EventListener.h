#ifndef EVENT_LISTENER_H_
#define EVENT_LISTENER_H_

#include <Trackable.h>
#include "Event.h"

class EventSystem;

class EventListener : public Trackable
{
public:
	EventListener(EventSystem* pEventSystem);
	virtual ~EventListener();

	virtual void handleEvent(const Event& theEvent) = 0;

protected:
	EventSystem* getEventSystem() const { return mpEventSystem; };

private:
	EventSystem* mpEventSystem;
};

#endif