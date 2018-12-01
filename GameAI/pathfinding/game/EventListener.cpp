#include "EventListener.h"
#include "EventSystem.h"

EventListener::EventListener(EventSystem* pEventSystem) :
	mpEventSystem(pEventSystem)
{

}

EventListener::~EventListener()
{
	mpEventSystem->removeListenerFromAllEvents(this);
}
