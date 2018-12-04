#ifndef PATHFINDER_H_
#define PATHFINDER_H_

#include <vector>
#include <Trackable.h>

class GridGraph;
class Path;
class Node;
class GraphicsBuffer;
class Grid;

#define VISUALIZE_PATH 1

class Pathfinder : public Trackable
{
public:
	Pathfinder(GridGraph* pGraph);
	virtual ~Pathfinder();

	virtual Path* findPath(Node* pFrom, Node* pTo) = 0;

protected:
	GridGraph* mpGraph;
};

#endif