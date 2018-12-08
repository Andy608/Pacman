#include <MemoryTracker.h>
#include <PerformanceTracker.h>
#include "EventSystem.h"
#include "Game.h"

using namespace std;

PerformanceTracker* gpPerformanceTracker = nullptr;

int main()
{
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