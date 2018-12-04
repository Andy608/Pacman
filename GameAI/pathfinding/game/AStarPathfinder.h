#ifndef ASTAR_PATHFINDER_H_
#define ASTAR_PATHFINDER_H_

#include "GridPathfinder.h"

class AStarPathfinder : public GridPathfinder
{
public:
	AStarPathfinder(GridGraph* pGraph, Node* pFrom = nullptr, Node* pTo = nullptr);
	virtual ~AStarPathfinder();

	Path* findPath(Node* pFrom, Node* pTo);
};

#endif