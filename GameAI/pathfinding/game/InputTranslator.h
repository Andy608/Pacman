#ifndef INPUT_TRANSLATOR_H_
#define INPUT_TRANSLATOR_H_

#include "EventListener.h"
#include <map>

class InputTranslator : public EventListener
{
public:
	InputTranslator();
	~InputTranslator();

	bool init();
	void cleanup();

	virtual void handleEvent(const Event& theEvent);

private:
	bool mIsInitialized;
	std::map<const int, Event::EnumEventType> mInputMap;

	Event::EnumEventType getEventFromMapping(int originalMapping);
	void fireTranslatedEvent(const Event& theEvent);
};

#endif