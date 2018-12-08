#include "GridPathfinder.h"
#include "GridGraph.h"
#include "GridVisualizer.h"
#include "Path.h"
#include "Game.h"
#include "GraphicsBuffer.h"
#include "Color.h"
#include <cassert>
#include <iostream>

using namespace std;

GridPathfinder::GridPathfinder(GridGraph* pGraph, Node* pFrom, Node* pTo) :
	Pathfinder(pGraph),
	mTimeElapsed(0.0),
	mpFrom(pFrom),
	mpTo(pTo)
{
#ifdef VISUALIZE_PATH
	mpVisualizer = NULL;
	mpPath = NULL;
#endif
}

GridPathfinder::~GridPathfinder()
{
#ifdef VISUALIZE_PATH
	delete mpVisualizer;
#endif
}

float lerp(int value, int start, int end)
{
	//returns float representing how far value is between start and end
	assert(start <= end);

	float lerpVal = 0.0f;

	if (start <= end)
	{
		int range = end - start;
		lerpVal = value / (float)range;
	}
	return lerpVal;
}


#ifdef VISUALIZE_PATH
void GridPathfinder::drawVisualization(Grid* pGrid)
{
	delete mpVisualizer;
	mpVisualizer = new GridVisualizer(pGrid);
	static Color startPathColor = Color(255, 117, 2);
	static Color endPathColor = Color(255, 255, 255);
	static Color visitedColor = Color(0, 255, 0);
	static Color startColor = Color(1, 255, 128);
	static Color stopColor = Color(1, 128, 255);

	if (mpPath != nullptr)
	{
		Color currentPathColor = startPathColor;
		int numNodes = mpPath->getNumNodes();

		for (int i = 1; i < numNodes - 1; i++)
		{
			mpVisualizer->addColor(mpPath->peekNode(i)->getId(), Color(255, 255, 255));
			currentPathColor = Color(255, 255, 255);
		}

		if (numNodes > 0)
		{
			//add beginning and ending color
			mpVisualizer->addColor(mpPath->peekNode(0)->getId(), startColor);
			mpVisualizer->addColor(mpPath->peekNode(mpPath->getNumNodes() - 1)->getId(), stopColor);
		}

	}

	mpVisualizer->draw();
}
#endif