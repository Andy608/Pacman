/*
* Author:		Andrew Rimpici, Tim Carbone
* Date:			5/4/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Final Project
* Certification of Authenticity: I certify that this assignment is entirely our own work.
*/

#include <MemoryTracker.h>
#include "EventSystem.h"
#include "Game.h"

using namespace std;

int main()
{
	//17 x 21 at 42px per tile
	const int DISPLAY_WIDTH = 714;
	const int DISPLAY_HEIGHT = 882;

	EventSystem::initInstance();
	Game::initInstance();
	Game::getInstance()->init(DISPLAY_WIDTH, DISPLAY_HEIGHT);

	Game::getInstance()->loop();

	Game::cleanupInstance();
	EventSystem::cleanupInstance();

	MemoryTracker::getInstance()->reportAllocations(cout);

	system("pause");
	return 0;
}