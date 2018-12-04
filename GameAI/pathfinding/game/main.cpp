/*
* Author:		Andrew Rimpici, Tim Carbone
* Date:			5/4/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Final Project
* Certification of Authenticity: I certify that this assignment is entirely our own work.
*/

#include <MemoryTracker.h>
#include <PerformanceTracker.h>
#include "EventSystem.h"
#include "Game.h"

using namespace std;

PerformanceTracker* gpPerformanceTracker = nullptr;

int main()
{
	//17 x 21 at 42px per tile
	//const int DISPLAY_WIDTH = 714;
	//const int DISPLAY_HEIGHT = 882;

	//27 x 31 at 32px per tile
	//const int DISPLAY_WIDTH = 864;
	//const int DISPLAY_HEIGHT = 992;

	//15 x 17 at 60px per tile
	const int DISPLAY_WIDTH = 900;
	const int DISPLAY_HEIGHT = 1020;

	gpPerformanceTracker = new PerformanceTracker();

	EventSystem::initInstance();
	Game::initInstance();
	Game::getInstance()->init(DISPLAY_WIDTH, DISPLAY_HEIGHT);

	Game::getInstance()->loop();

	Game::cleanupInstance();
	EventSystem::cleanupInstance();

	delete gpPerformanceTracker;

	MemoryTracker::getInstance()->reportAllocations(cout);

	system("pause");
	return 0;
}