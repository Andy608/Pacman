#ifndef SYSTEM_H_
#define SYSTEM_H_

#include <Trackable.h>
#include "GraphicsSystem.h"
#include "InputSystem.h"

class System : public Trackable
{
public:
	static System* getInstance();
	static bool initInstance(const int& displayWidth, const int& displayHeight);
	static void cleanupInstance();

	InputSystem* getInputSystem() const;

	//Disable any form of copying for a System object.
	System(const System& copy) = delete;
	void operator=(const System& copy) = delete;

private:
	static System* smpInstance;

	InputSystem* mpInputSystem;
	bool mIsInitialized;

	System();
	~System();

	bool init(const int& displayWidth, const int& displayHeight);
	void cleanup();
};

#endif