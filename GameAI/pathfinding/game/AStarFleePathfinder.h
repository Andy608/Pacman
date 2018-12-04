#ifndef ASTAR_FLEE_PATHFINDER_H_
#define ASTAR_FLEE_PATHFINDER_H_

#include "GridPathfinder.h"

class AStarFleePathfinder : public GridPathfinder
{
public:
	AStarFleePathfinder(GridGraph* pGraph, int iterations, Node* pFrom = nullptr, Node* pTo = nullptr);
	virtual ~AStarFleePathfinder();

	Path* findPath(Node* pFrom, Node* pTo);

private:
	int mIterations;
};

#endif