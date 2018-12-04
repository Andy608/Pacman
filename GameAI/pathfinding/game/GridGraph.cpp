#include "GridGraph.h"
#include "Connection.h"
#include "Node.h"
#include "Grid.h"
#include "Game.h"
#include <vector>
#include <Vector2D.h>

GridGraph::GridGraph(Grid* pGrid) :
	Graph(),
	mpGrid(pGrid)
{

}

GridGraph::~GridGraph()
{

}

void GridGraph::init()
{
	if (mpGrid != nullptr)
	{
		int numGridIndices = mpGrid->getGridWidth() * mpGrid->getGridHeight();

		//size the node vector
		mNodes.resize(numGridIndices, nullptr);

		//go through all elements of the grid and make Nodes for them - also add them to Node vector
		for (int i = 0; i < numGridIndices; i++)
		{
			//create a Node for this location
			Node* pNode = new Node(i);
			//add to NodeVector
			mNodes[i] = pNode;
		}

		//go through all elements of the grid - get adjacencies and create connections for each
		for (int i = 0; i < numGridIndices; i++)
		{
			//get the Node for this location
			Node* pFromNode = mNodes[i];

			//get all the adjacencies
			std::vector<int> adjacencies = mpGrid->getAdjacentIndices(i);

			//create a vector of Connections
			std::vector<Connection*> connections;

			//go through all adjacent indices, get the nodes for them, create connections, and add to connections map
			for (unsigned int adjIndex = 0; adjIndex < adjacencies.size(); adjIndex++)
			{
				//check for blocking terrain
				if (mpGrid->getValueAtIndex(adjacencies[adjIndex]) != mpGrid->sWALL_ID)
				{
					Node* pToNode = mNodes[adjacencies[adjIndex]];//find to node

																  //EXTRA CREDIT START

																  //Calculate the distance/weight between the grid pixels :)
					Vector2D fromGridPos = mpGrid->getULCornerOfSquare(pFromNode->getId());
					Vector2D toGridPos = mpGrid->getULCornerOfSquare(pToNode->getId());
					Vector2D dist = toGridPos - fromGridPos;

					Connection* pConnection = new Connection(pFromNode, pToNode, dist.getLengthSquared());//create a connection
																										  //EXTRA CREDIT END

																										  //add connection to connection vectors
					mConnections.push_back(pConnection);
					connections.push_back(pConnection);
				}
			}

			//put temp connection vector into map
			mConnectionMap[i] = connections;
		}
	}
}
