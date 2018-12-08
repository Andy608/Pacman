#include <PerformanceTracker.h>
#include <list>
#include <vector>
#include <algorithm>

#include "AStarFleePathfinder.h"
#include "Path.h"
#include "GridGraph.h"
#include "Game.h"

#include "Heuristic.h"
#include "PathfindingList.h"

AStarFleePathfinder::AStarFleePathfinder(GridGraph* pGraph, int iterations, Node* pFrom, Node* pTo) :
	GridPathfinder(dynamic_cast<GridGraph*>(pGraph), pFrom, pTo),
	mIterations(iterations)
{
#ifdef VISUALIZE_PATH
	mpPath = NULL;

	if (mpFrom && mpTo)
	{
		findPath(mpFrom, mpTo);
	}
#endif
}

AStarFleePathfinder::~AStarFleePathfinder()
{
#ifdef VISUALIZE_PATH
	delete mpPath;
#endif
}

Path* AStarFleePathfinder::findPath(Node* pFrom, Node* pTo)
{
	gpPerformanceTracker->clearTracker("path");
	gpPerformanceTracker->startTracking("path");

	if (!pFrom || !pTo) return nullptr;

	setNodes(pFrom, pTo);

	Heuristic heuristic = Heuristic(pTo);
	NodeRecord startRecord = NodeRecord(pFrom, nullptr, 0.0f, -heuristic.estimateCost(mpGraph, pFrom));

	PathfindingList openList;
	openList.addBasedOnEstimate(startRecord);

	PathfindingList closedList;

#ifdef VISUALIZE_PATH
	delete mpPath;
	mVisitedNodes.clear();
	mVisitedNodes.push_back(pFrom);
#endif

	Path* pPath = new Path();
	NodeRecord current;
	int iter = 0;

	while (iter < mIterations)
	{
		openList.getSmallestElement(current);

		std::vector<Connection*> connections = mpGraph->getConnections(current.node->getId());

		for (Connection* currentConnection : connections)
		{
			Node* endNode = currentConnection->getToNode();
			float endNodeCost = current.costSoFar + currentConnection->getCost();
			float endNodeHeuristic;
			NodeRecord endNodeRecord;

			if (closedList.contains(endNode))
			{
				closedList.find(endNode, endNodeRecord);

				if (endNodeRecord.costSoFar <= endNodeCost)
				{
					continue;
				}

				closedList -= endNodeRecord;

				endNodeHeuristic = -heuristic.estimateCost(mpGraph, endNode);
			}
			else if (openList.contains(endNode))
			{
				openList.find(endNode, endNodeRecord);

				if (endNodeRecord.costSoFar <= endNodeCost)
				{
					continue;
				}

				endNodeHeuristic = -heuristic.estimateCost(mpGraph, endNode);
			}
			else
			{
				endNodeRecord = NodeRecord();
				endNodeRecord.node = endNode;

				endNodeHeuristic = -heuristic.estimateCost(mpGraph, endNode);
			}

			endNodeRecord.costSoFar = endNodeCost;
			endNodeRecord.connection = currentConnection;
			endNodeRecord.estimatedTotalCost = endNodeCost + endNodeHeuristic;

			if (!openList.contains(endNode))
			{
				openList.addBasedOnEstimate(endNodeRecord);
			}

#ifdef VISUALIZE_PATH
			mVisitedNodes.push_back(endNodeRecord.node);
#endif
		}

		openList -= current;
		closedList.addBasedOnEstimate(current);

		++iter;
	}

	NodeRecord temp = current;

	while (temp.node != pFrom)
	{
		pPath->addNode(temp.node);
		closedList.find(temp.connection->getFromNode(), temp);
	}

	pPath->addNode(pFrom);

	Path* reversePath = new Path();
	for (int i = pPath->getNumNodes() - 1; i >= 0; --i)
	{
		reversePath->addNode(pPath->peekNode(i));
	}

	delete pPath;
	pPath = reversePath;

	if (pPath->getNumNodes() == 0)
	{
		delete pPath;
		pPath = nullptr;
	}

	gpPerformanceTracker->stopTracking("path");
	mTimeElapsed = gpPerformanceTracker->getElapsedTime("path");

#ifdef VISUALIZE_PATH
	mpPath = pPath;
#endif
	return pPath;
}