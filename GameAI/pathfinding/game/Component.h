#ifndef COMPONENT_H_
#define COMPONENT_H_

#include <limits>
#include <Trackable.h>
#include <DeanLibDefines.h>

typedef Uint32 ComponentID;
const Uint32 INVALID_COMPONENT_ID = UINT_MAX;

class Component :public Trackable
{
public:
	inline Component(const ComponentID& id) : mID(id) {};
	inline virtual ~Component() {};

	inline ComponentID getID() { return mID; };

private:
	ComponentID mID;
};

#endif