#include "Heuristic.h"
#include "Game.h"
#include "Grid.h"
#include <Vector2D.h>

float Heuristic::estimateCost(GridGraph* gridGraph, Node* startNode)
{
	Grid* grid = gridGraph->getGrid();
	Vector2D fromGridPos = grid->getULCornerOfSquare(startNode->getId());
	Vector2D toGridPos = grid->getULCornerOfSquare(mGoalNode->getId());
	Vector2D dist = toGridPos - fromGridPos;
	return dist.getLengthSquared();
}