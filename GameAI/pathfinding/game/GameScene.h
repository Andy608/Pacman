#ifndef GAME_SCENE_H_
#define GAME_SCENE_H_

#include "Scene.h"
#include "Grid.h"
#include "GridGraph.h"
#include "GridVisualizer.h"
#include "EventListener.h"

class GameScene : public Scene, public EventListener
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

	virtual void handleEvent(const Event& theEvent);

private:
	GameScene();
	inline virtual ~GameScene() { cleanup(); };

	SettingsFile* mpMapSettings;

	GridGraph* mpGridGraph;
	Grid* mpGameGrid;
	GridVisualizer* mpGridVisualizer;

	int mInGame = false;
	int mItemCount = 0;
};

#endif