#include "Grid.h"
#include "GraphicsSystem.h"
#include "Vector2D.h"
#include <memory.h>

Grid::Grid(SettingsFile* mapSettings, int width, int height) : 
	mMapSettings(mapSettings),
	mPixelWidth(width),
	mPixelHeight(height),
	mSquareSize(std::stoi(mMapSettings->getSettingFromKey("square_size"))),
	sFLOOR_ID(std::stoi(mMapSettings->getKeyFromSetting("floor_tile"))),
	sWALL_ID(std::stoi(mMapSettings->getKeyFromSetting("wall_tile"))),
	sCANDY_SPAWN_ID(std::stoi(mMapSettings->getKeyFromSetting("candy_tile"))),
	sPLAYER_SPAWN_ID(std::stoi(mMapSettings->getKeyFromSetting("player_tile"))),
	sENEMY_SPAWN_ID(std::stoi(mMapSettings->getKeyFromSetting("enemy_tile"))),
	mCoinCoveragePercent(std::stof(mMapSettings->getSettingFromKey("coin_map_coverage")))
{
	mGridWidth = mPixelWidth / mSquareSize;
	mGridHeight = mPixelHeight / mSquareSize;
	mpValues = new int[mGridWidth * mGridHeight];
	memset(mpValues, 0, sizeof(int) * mGridWidth * mGridHeight);

	if (mCoinCoveragePercent > 1.0f)
	{
		mCoinCoveragePercent = 1.0f;
	}
	else if (mCoinCoveragePercent < 0.0f)
	{
		mCoinCoveragePercent = 0.0f;
	}

	for (int i = 0; i < mGridWidth * mGridHeight; ++i)
	{
		mTilesWithItems.insert(std::make_pair(i, true));
	}
}

Grid::~Grid()
{
	delete[] mpValues;
}

int Grid::getSquareIndexFromPosition(const Vector2D& position) const
{
	return getSquareIndexFromPixelXY((int)position.getX(), (int)position.getY());
}

int Grid::getSquareIndexFromPixelXY(int x, int y) const
{
	x /= mSquareSize;
	y /= mSquareSize;
	return y * mGridWidth + x;
}

int Grid::getValueAtIndex(int index) const
{
	return *(mpValues + index);
}

int Grid::getValueAtPixelXY(int x, int y) const
{
	int index = getSquareIndexFromPixelXY(x, y);
	return getValueAtIndex(index);
}

int Grid::getValueAtPosition(const Vector2D& position) const
{
	int index = getSquareIndexFromPixelXY((int)position.getX(), (int)position.getY());
	return getValueAtIndex(index);
}

void Grid::setValueAtIndex(int index, int value)
{
	for (unsigned int i = 0; i < mCandySpawnIndexes.size(); ++i)
	{
		if (index == mCandySpawnIndexes.at(i))
		{
			mCandySpawnIndexes.erase(mCandySpawnIndexes.begin() + i);
		}
	}

	for (unsigned int i = 0; i < mEnemySpawnIndexes.size(); ++i)
	{
		if (index == mEnemySpawnIndexes.at(i))
		{
			mEnemySpawnIndexes.erase(mEnemySpawnIndexes.begin() + i);
		}
	}

	for (unsigned int i = 0; i < mFloorTileIndexes.size(); ++i)
	{
		if (index == mFloorTileIndexes.at(i))
		{
			mFloorTileIndexes.erase(mFloorTileIndexes.begin() + i);
		}
	}

	if (value == sPLAYER_SPAWN_ID)
	{
		mPlayerSpawnTileIndex = index;
	}
	else if (value == sCANDY_SPAWN_ID)
	{
		mCandySpawnIndexes.push_back(index);
	}
	else if (value == sFLOOR_ID)
	{
		mFloorTileIndexes.push_back(index);
	}
	else if (value == sENEMY_SPAWN_ID)
	{
		mEnemySpawnIndexes.push_back(index);
		setIndexFree(index, false);
	}
	else if (value == sWALL_ID)
	{
		setIndexFree(index, false);
	}

	*(mpValues + index) = value;
}

void Grid::setValueAtPixelXY(int x, int y, int value)
{
	int index = getSquareIndexFromPixelXY(x, y);
	setValueAtIndex(index, value);
}

Vector2D Grid::getULCornerOfSquare(int index) const
{
	int squareY = index / mGridWidth;
	int squareX = index % mGridWidth;
	Vector2D pos((float)(squareX * mSquareSize), (float)(squareY * mSquareSize));
	return pos;
}

//get adjacent grid square indices
std::vector<int> Grid::getAdjacentIndices(int theSquareIndex) const
{
	std::vector<int> indices;

	//static const int NUM_DIRS = 8;
	////						        N  NE	E  SE	S	SW	 W	NW
	//static int xMods[NUM_DIRS] = { 0,	1,	1,	1,	0,	-1,	-1,	-1 };
	//static int yMods[NUM_DIRS] = { -1, -1,	0,	1,	1,	 1,	 0,	-1 };

	static const int NUM_DIRS = 4;
	//						        N 	E  	S	 W	
	static int xMods[NUM_DIRS] = { 0,	1,	0,	-1, };
	static int yMods[NUM_DIRS] = { -1,	0,	1,	 0, };

	//find the x,y of the passed in index
	int x = theSquareIndex % mGridWidth;
	int y = theSquareIndex / mGridWidth;

	for (int i = 0; i<NUM_DIRS; i++)
	{
		//calc adjacent x,y
		int adjX = x + xMods[i];
		int adjY = y + yMods[i];

		//convert back to an index if on the Grid
		if (adjX >= 0 && adjX < mGridWidth && adjY >= 0 && adjY < mGridHeight)
		{
			int adjIndex = (adjY * mGridWidth) + adjX;

			//add to vector of indices
			indices.push_back(adjIndex);
		}
	}
	return indices;
}


void Grid::save(std::ofstream& file)
{
	int numSquares = mGridWidth * mGridHeight;
	for (int i = 0; i<numSquares; i++)
	{
		file << mpValues[i] << " ";
	}
}

void Grid::load(std::ifstream& file)
{
	int numSquares = mGridWidth * mGridHeight;
	for (int i = 0; i<numSquares; i++)
	{
		file >> mpValues[i];
	}
}

bool Grid::isIndexFree(int index)
{
	return mTilesWithItems.at(index);
}

void Grid::setIndexFree(int index, bool isFree)
{
	std::map<int, bool>::iterator it = mTilesWithItems.find(index);

	if (it != mTilesWithItems.end())
	{
		it->second = isFree;
	}
}