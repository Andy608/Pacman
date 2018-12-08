#include "GameScene.h"
#include "AssetManager.h"
#include "GraphicsSystem.h"

#include "ComponentManager.h"
#include "LocalizationMap.h"
#include "UnitManager.h"
#include "EventSystem.h"

#include "Player.h"
#include "Candy.h"
#include "Coin.h"
#include "Enemy.h"
#include "GameEvent.h"

GameScene::GameScene() : 
	Scene(EnumScene::GAME_SCENE),
	EventListener(EventSystem::getInstance()),
	mpMapSettings(new SettingsFile("assets/data_files/tile_data.txt"))
{
	mpGameGrid = new Grid(mpMapSettings, GraphicsSystem::getDisplayWidth(), GraphicsSystem::getDisplayHeight());
	mpGridGraph = nullptr;
	mpGridVisualizer = nullptr;

	EventSystem::addListener(static_cast<Event::EnumEventType>(GameEvent::EnumGameEventType::_PLAYER_ATE_ENEMY_EVENT), this);
	EventSystem::addListener(static_cast<Event::EnumEventType>(GameEvent::EnumGameEventType::_PLAYER_ATE_CANDY_EVENT), this);
	EventSystem::addListener(static_cast<Event::EnumEventType>(GameEvent::EnumGameEventType::_PLAYER_ATE_COIN_EVENT), this);
	EventSystem::addListener(static_cast<Event::EnumEventType>(GameEvent::EnumGameEventType::_GAME_LOST_EVENT), this);
}

void GameScene::start()
{
	mInGame = true;
	Game::getInstance()->setWon(false);

	const GraphicsBuffer& levelMap = *mpAssetManagerInstance->getBuffer("level_map");

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
	}

	const std::vector<int>& enemySpawns = mpGameGrid->getEnemySpawns();
	for (unsigned int i = 0; i < enemySpawns.size(); ++i)
	{
		Enemy* enemy = Game::getInstance()->getUnitManager()->createEnemyUnit(mpGridGraph, mpGameGrid->getULCornerOfSquare(enemySpawns.at(i)));
		enemy->getPositionComponent()->setPosition(mpGameGrid->getULCornerOfSquare(enemySpawns.at(i)));
		mpGameGrid->setIndexFree(enemySpawns.at(i), false);
	}

	mItemCount = selectedIndexes.size() + candySpawns.size();

	mIsInitialized = true;
}

void GameScene::end()
{
	mInGame = false;

	delete mpGridGraph;
	mpGridGraph = nullptr;

	delete mpGridVisualizer;
	mpGridVisualizer = nullptr;
}

void GameScene::cleanup()
{
	delete mpMapSettings;
	mpMapSettings = nullptr;

	delete mpGameGrid;
	mpGameGrid = nullptr;

	delete mpGridGraph;
	mpGridGraph = nullptr;

	delete mpGridVisualizer;
	mpGridVisualizer = nullptr;

	mIsInitialized = false;
}

void GameScene::handleEvent(const Event& theEvent)
{
	if (mInGame)
	{
		switch (theEvent.getType())
		{
		case GameEvent::EnumGameEventType::_PLAYER_ATE_ENEMY_EVENT:
		{
			Game::getInstance()->addScore((int)*mpAssetManagerInstance->getValue("eat_enemy_score"));
			break;
		}
		case GameEvent::EnumGameEventType::_PLAYER_ATE_CANDY_EVENT:
		{
			Game::getInstance()->addScore((int)*mpAssetManagerInstance->getValue("eat_candy_score"));
			mItemCount--;
			break;
		}
		case GameEvent::EnumGameEventType::_PLAYER_ATE_COIN_EVENT:
		{
			Game::getInstance()->addScore((int)*mpAssetManagerInstance->getValue("eat_coin_score"));
			mItemCount--;
			break;
		}
		case GameEvent::EnumGameEventType::_GAME_LOST_EVENT:
		{
			mInGame = false;
			Game::getInstance()->setWon(false);
			return;
		}
		}

		if (mItemCount <= 0)
		{
			mInGame = false;
			Game::getInstance()->setWon(true);
		}
	}
}

void GameScene::update(float deltaTime)
{
	if (!mInGame)
	{
		Game::getInstance()->getUnitManager()->deleteAllUnits();
		EventSystem::fireEvent(GameEnded(Game::getInstance()->getWon()));
	}
}

void GameScene::draw() 
{
	GraphicsSystem::drawScaledToFit(0, 0, *mpAssetManagerInstance->getBuffer("background_buffer"), GraphicsSystem::getDisplayWidth(), GraphicsSystem::getDisplayHeight());
	mpGridVisualizer->draw();

	GraphicsSystem::writeTextCenteredHorizontally(0, 
		*mpAssetManagerInstance->getFont("gui_font"), 
		*mpAssetManagerInstance->getColor("text_color"), 
		mpLocalizationInstance->getLocalizedString("game_scene_score") + std::to_string(Game::getInstance()->getScore()));

	Game::getInstance()->getUnitManager()->drawAll();
}

void GameScene::load() {}

void GameScene::save() {}