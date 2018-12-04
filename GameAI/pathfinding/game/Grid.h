#ifndef GRID_H_
#define GRID_H_

#include <fstream>
#include <vector>
#include "Trackable.h"
#include "SettingsFile.h"

class Vector2D;

class Grid :public Trackable
{
public:
	Grid(SettingsFile* mapSettings, int width, int height);
	~Grid();

	int getSquareIndexFromPosition(const Vector2D& position) const;
	int getSquareIndexFromPixelXY(int x, int y) const;

	int getValueAtPosition(const Vector2D& position) const;
	int getValueAtIndex(int index) const;
	int getValueAtPixelXY(int x, int y) const;
	void setValueAtIndex(int index, int value);
	void setValueAtPixelXY(int x, int y, int value);
	Vector2D getULCornerOfSquare(int index) const;

	void setIndexFree(int index, bool isFree);
	bool isIndexFree(int index);

	//accessors
	int getPixelWidth() const { return mPixelWidth; };
	int getPixelHeight() const { return mPixelHeight; };
	int getGridWidth() const { return mGridWidth; };
	int getGridHeight() const { return mGridHeight; };
	int getSquareSize() const { return mSquareSize; };

	const int& getPlayerSpawn() const { return mPlayerSpawnTileIndex; };
	const std::vector<int>& getCandySpawns() const { return mCandySpawnIndexes; };
	const std::vector<int>& getEnemySpawns() const { return mEnemySpawnIndexes; };
	const float& getCoinCoveragePercent() const { return mCoinCoveragePercent; };
	const std::vector<int>& getFloorTileIndexes() const { return mFloorTileIndexes; };
	const std::map<int, bool>& getTilesWithItemsMap() const { return mTilesWithItems; };

	//get adjacent grid square indices
	std::vector<int> getAdjacentIndices(int theSquareIndex) const;

	void save(std::ofstream& file);
	void load(std::ifstream& file);

private:
	SettingsFile* mMapSettings;

	int mSquareSize;
	int mGridWidth;
	int mGridHeight;
	int* mpValues;
	int mPixelWidth;
	int mPixelHeight;

	int mPlayerSpawnTileIndex;
	std::vector<int> mCandySpawnIndexes;
	std::vector<int> mEnemySpawnIndexes;
	std::vector<int> mFloorTileIndexes;
	std::map<int, bool> mTilesWithItems;
	float mCoinCoveragePercent;

public:
	const int sFLOOR_ID;
	const int sWALL_ID;
	const int sCANDY_SPAWN_ID;
	const int sPLAYER_SPAWN_ID;
	const int sENEMY_SPAWN_ID;
};

#endif