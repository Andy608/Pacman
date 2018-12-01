#include "GameScene.h"
#include "AssetManager.h"
#include "GraphicsSystem.h"

GameScene::GameScene() : 
	Scene(EnumScene::GAME_SCENE),
	mpMapSettings(new SettingsFile("assets/data_files/tile_data.txt")),
	mpGameGrid(new Grid(GraphicsSystem::getDisplayWidth(), GraphicsSystem::getDisplayHeight(), std::stoi(mpMapSettings->getSettingFromKey("square_size")))),
	mpGridVisualizer(new GridVisualizer(mpGameGrid))
{

}

void GameScene::start()
{
	GraphicsBuffer levelMap = *mpAssetManagerInstance->getBuffer("level_map");

	int gridWidth = levelMap.getWidth();
	int gridHeight = levelMap.getHeight();

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
}

void GameScene::load() {}

void GameScene::save() {}