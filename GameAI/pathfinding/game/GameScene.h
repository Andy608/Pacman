#ifndef GAME_SCENE_H_
#define GAME_SCENE_H_

#include "Scene.h"
#include "Grid.h"
#include "GridVisualizer.h"

class GameScene : public Scene
{
	friend class SceneManager;

public:
	virtual void start();
	virtual void end();

	virtual void cleanup();

	virtual void update(float deltaTime);
	virtual void draw();
	virtual void save();
	virtual void load();

private:
	GameScene();
	inline virtual ~GameScene() { cleanup(); };

	SettingsFile* mpMapSettings;

	Grid* mpGameGrid;
	GridVisualizer* mpGridVisualizer;
};

#endif