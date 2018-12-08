#ifndef GAME_H_
#define GAME_H_

#include <Trackable.h>
#include "EventListener.h"
#include "Color.h"

class Timer;
class InputTranslator;
class Sprite;
class SettingsFile;
class Score;
class SceneManager;
class AssetManager;
class SaveManager;
class LocalizationMap;
class PerformanceTracker;

class ComponentManager;
class UnitManager;
class GridPathfinder;

extern PerformanceTracker* gpPerformanceTracker;

class Game : public EventListener
{
public:
	static Game* getInstance();
	static bool initInstance();
	static void cleanupInstance();

	//Disable any form of copying for a Game object.
	Game(const Game& copy) = delete;
	void operator=(const Game& copy) = delete;

	bool init(const int& displayWidth, const int& displayHeight);
	void cleanup();

	void loop();

	virtual void handleEvent(const Event& theEvent);

	inline AssetManager* getAssetManager() const { return mpAssetManager; };
	inline LocalizationMap* getLocalizationMap() const { return mpLocalizationMap; };
	inline SaveManager* getSaveManager() const { return mpSaveManager; };
	inline Vector2D getDisplayDimensions() const { return mDisplayDimensions; };
	inline SceneManager* getSceneManager() const { return mpSceneManager; }
	
	inline UnitManager* getUnitManager() const { return mpUnitManager; };
	inline ComponentManager* getComponentManager() const { return mpComponentManager; };

	inline bool isSoundOn() { return mIsSoundOn; };

	inline int getScore() const { return mScore; };
	inline void setScore(int score) { mScore = score; };
	inline void addScore(int score) { mScore += score; };
	inline void resetScore() { mScore = 0; };

	inline bool getWon() const { return mWon; };
	inline void setWon(bool won) { mWon = won; };

	void toggleSound(bool isOn);
	void requestQuitGame();

private:
	static Game* smpInstance;
	static const int ANIMATION_SPEED_OFFSET;
	static const float mFPS;
	static const float mUPDATE_TIME;//Timer is in milliseconds
	static const float mLAG_CAP;//Timer is in milliseconds

	static const int MAX_UNITS = 1000;

	const std::string mDRAW_TRACKER_NAME = "draw";
	int mFrames;

	bool mIsInitialized = false;
	bool mIsLoopRunning = false;
	bool mShouldShutdown = false;
	bool mIsSoundOn = true;

	Timer* mpTimer = nullptr;

	SettingsFile* mpMainSettingsFile = nullptr;
	AssetManager* mpAssetManager = nullptr;
	LocalizationMap* mpLocalizationMap = nullptr;
	SceneManager* mpSceneManager = nullptr;
	InputTranslator* mpInputTranslator = nullptr;
	SaveManager* mpSaveManager = nullptr;

	ComponentManager* mpComponentManager = nullptr;
	UnitManager* mpUnitManager = nullptr;

	Vector2D mDisplayDimensions;
	int mScore;
	bool mWon;

	Game();
	~Game();

	void update(float deltaTime);
	void render();
};

#endif