#ifndef HEURISTIC_H_
#define HEURISTIC_H_

#include <Trackable.h>
#include "Node.h"
#include "GridGraph.h"

class Heuristic : public Trackable
{
public:
	inline Heuristic(Node* goalNode) :
		mGoalNode(goalNode) {};

	float estimateCost(GridGraph* gridGraph, Node* startNode);

private:
	Node* mGoalNode;
};

#endif