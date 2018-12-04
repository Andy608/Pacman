#include "GameScene.h"
#include "AssetManager.h"
#include "GraphicsSystem.h"

#include "ComponentManager.h"
#include "UnitManager.h"

#include "Player.h"
#include "Candy.h"
#include "Coin.h"
#include "Enemy.h"

GameScene::GameScene() : 
	Scene(EnumScene::GAME_SCENE),
	mpMapSettings(new SettingsFile("assets/data_files/tile_data.txt"))
{
	mpGameGrid = new Grid(mpMapSettings, GraphicsSystem::getDisplayWidth(), GraphicsSystem::getDisplayHeight());
	mpGridGraph = nullptr;
	mpGridVisualizer = nullptr;
}

void GameScene::start()
{
	GraphicsBuffer levelMap = *mpAssetManagerInstance->getBuffer("level_map");

	int gridWidth = mpGameGrid->getGridWidth();
	int gridHeight = mpGameGrid->getGridHeight();

	unsigned int tileCount = gridWidth * gridHeight;

	for (int y = 0; y < gridHeight; ++y)
	{
		for (int x = 0; x < gridWidth; ++x)
		{
			//Get the color of the img-pixel
			Color pixelColor = levelMap.getPixelColor(x, y);

			//Convert the color to string format
			std::string colorString = std::to_string(pixelColor.red) + "," + std::to_string(pixelColor.green) + "," + std::to_string(pixelColor.blue);

			//Get the tile name based on the color string
			std::string tileName = mpMapSettings->getKeyFromSetting(colorString);

			//Get the tile ID based on the tile name
			int tileValue = std::stoi(mpMapSettings->getKeyFromSetting(tileName));

			//Add the tile ID to the grid data
			//std::cout << "X: " << std::to_string(x) << ", Y: " << std::to_string(y) << " V: " << std::to_string(tileValue) << std::endl;
			mpGameGrid->setValueAtPixelXY(x * mpGameGrid->getSquareSize(), y * mpGameGrid->getSquareSize(), tileValue);
		}
	}

	mpGridGraph = new GridGraph(mpGameGrid);
	mpGridGraph->init();
	mpGridVisualizer = new GridVisualizer(mpGameGrid);

	Player* player = Game::getInstance()->getUnitManager()->createPlayerUnit(mpGridGraph);
	player->getPositionComponent()->setPosition(mpGameGrid->getULCornerOfSquare(mpGameGrid->getPlayerSpawn()));
	mpGameGrid->setIndexFree(mpGameGrid->getPlayerSpawn(), false);

	if (player)
	{
		player->initTargetPos(player->getPositionComponent()->getPosition());
		//player->setSteering(Steering::ARRIVE, player->getPositionComponent()->getPosition());
	}

	const std::vector<int>& candySpawns = mpGameGrid->getCandySpawns();
	for (unsigned int i = 0; i < candySpawns.size(); ++i)
	{
		Candy* candy = Game::getInstance()->getUnitManager()->createCandyUnit(mpGridGraph);
		candy->getPositionComponent()->setPosition(mpGameGrid->getULCornerOfSquare(candySpawns.at(i)));
		mpGameGrid->setIndexFree(candySpawns.at(i), false);
	}

	const float& coinPercent = mpGameGrid->getCoinCoveragePercent();
	const std::map<int, bool>& tilesMap = mpGameGrid->getTilesWithItemsMap();

	std::vector<int> freeTiles;

	for (unsigned int i = 0; i < tilesMap.size(); ++i)
	{
		if (mpGameGrid->isIndexFree(i))
		{
			freeTiles.push_back(i);
		}
	}

	int amountOfTiles = (int)(freeTiles.size() * coinPercent);
	std::vector<int> selectedIndexes;

	for (int i = 0; i < amountOfTiles; ++i)
	{
		int index = rand() % freeTiles.size();
		selectedIndexes.push_back(freeTiles.at(index));
		freeTiles.erase(freeTiles.begin() + index);
	}

	for (unsigned int i = 0; i < selectedIndexes.size(); ++i)
	{
		Coin* coin = Game::getInstance()->getUnitManager()->createCoinUnit(mpGridGraph);
		coin->getPositionComponent()->setPosition(mpGameGrid->getULCornerOfSquare(selectedIndexes.at(i)));

		//Store in a list eventually
		//Game::getInstance()->getUnitManager()->createRandomCoinUnit(mpGameGrid);
	}

	const std::vector<int>& enemySpawns = mpGameGrid->getEnemySpawns();
	for (unsigned int i = 0; i < enemySpawns.size(); ++i)
	{
		Enemy* enemy = Game::getInstance()->getUnitManager()->createEnemyUnit(mpGridGraph);
		enemy->getPositionComponent()->setPosition(mpGameGrid->getULCornerOfSquare(enemySpawns.at(i)));
		mpGameGrid->setIndexFree(enemySpawns.at(i), false);
	}

	mIsInitialized = true;
}

void GameScene::end()
{
	cleanup();
}

void GameScene::cleanup()
{
	delete mpMapSettings;
	mpMapSettings = nullptr;

	delete mpGridGraph;
	mpGridGraph = nullptr;

	delete mpGridVisualizer;
	mpGridVisualizer = nullptr;

	delete mpGameGrid;
	mpGameGrid = nullptr;


	mIsInitialized = false;
}

void GameScene::update(float deltaTime)
{
}

void GameScene::draw() 
{
	GraphicsSystem::drawScaledToFit(0, 0, *mpAssetManagerInstance->getBuffer("background_buffer"), GraphicsSystem::getDisplayWidth(), GraphicsSystem::getDisplayHeight());
	mpGridVisualizer->draw();

	Game::getInstance()->getUnitManager()->drawAll();
}

void GameScene::load() {}

void GameScene::save() {}