#include "SceneManager.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "OptionsScene.h"
#include "EndScene.h"

SceneManager::SceneManager() :
	mIsInitialized(false),
	mpCurrentScene(nullptr)
{

}

SceneManager::~SceneManager()
{
	if (mIsInitialized)
	{
		auto iter = mSceneList.begin();
		for (; iter != mSceneList.end(); ++iter)
		{
			if (iter->second->mIsInitialized)
			{
				iter->second->save();
			}

			delete iter->second;
		}

		mSceneList.clear();

		mIsInitialized = false;
	}
}

bool SceneManager::initScenes()
{
	if (!mIsInitialized)
	{
		mSceneList.insert(std::make_pair(EnumScene::TITLE_SCENE, new TitleScene()));
		mSceneList.insert(std::make_pair(EnumScene::GAME_SCENE, new GameScene()));
		mSceneList.insert(std::make_pair(EnumScene::OPTIONS_SCENE, new OptionsScene()));
		mSceneList.insert(std::make_pair(EnumScene::END_SCENE, new EndScene()));

		mIsInitialized = true;

		try
		{
			setCurrentScene(EnumScene::TITLE_SCENE);
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
			mIsInitialized = false;
		}
	}

	return mIsInitialized;
}

void SceneManager::update(float deltaTime)
{
	mpCurrentScene->update(deltaTime);
}

void SceneManager::draw()
{
	mpCurrentScene->draw();
}

void SceneManager::save()
{
	mpCurrentScene->save();
}

void SceneManager::setCurrentScene(EnumScene scene)
{
	auto iter = mSceneList.begin();
	for (; iter != mSceneList.end(); ++iter)
	{
		if (iter->first == scene)
		{
			if (mpCurrentScene)
			{
				mpCurrentScene->end();
			}

			mpCurrentScene = iter->second;
			mpCurrentScene->start();
			return;
		}
	}

	std::cout << "Unable to find scene with id: " + (int)scene << std::endl;
}