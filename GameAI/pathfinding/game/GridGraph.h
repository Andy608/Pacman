#ifndef GRID_GRAPH_H_
#define GRID_GRAPH_H_

#include "Graph.h"

class Grid;

class GridGraph : public Graph
{
public:
	GridGraph(Grid* pGrid);
	virtual ~GridGraph();

	void setGrid(Grid* pGrid) { mpGrid = pGrid; };
	void init();

	Grid* getGrid() const { return mpGrid; }

private:
	Grid* mpGrid;
};

#endif