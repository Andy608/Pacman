#include "Coin.h"
#include "Game.h"
#include "AssetManager.h"
#include "GameEvent.h"
#include "Grid.h"
#include "UnitManager.h"
#include "EventSystem.h"

Coin::Coin(GridGraph* gridGraph) :
	Item(gridGraph, Game::getInstance()->getAssetManager()->getSprite("coin_sprite"))
{
	EventSystem::addListener(static_cast<Event::EnumEventType>(GameEvent::EnumGameEventType::_PLAYER_MOVED_EVENT), this);
}

Coin::~Coin()
{

}

void Coin::handleEvent(const Event& theEvent)
{
	switch (theEvent.getType())
	{
	case GameEvent::EnumGameEventType::_PLAYER_MOVED_EVENT:
		checkIfPlayerInRadius(static_cast<const PlayerMovedEvent&>(theEvent));
		break;
	}
}

void Coin::checkIfPlayerInRadius(const PlayerMovedEvent& theEvent)
{
	Grid* grid = mpGridGraph->getGrid();
	Vector2D playerPosition = theEvent.getPlayerPosition();
	Vector2D distance = playerPosition - getPositionComponent()->getPosition();

	if (distance.getLengthSquared() < grid->getSquareSize() * grid->getSquareSize())
	{
		mShouldDelete = true;
		//Send event that adds score to player.
	}
}