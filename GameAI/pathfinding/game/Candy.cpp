#include "Candy.h"
#include "Game.h"
#include "AssetManager.h"
#include "GameEvent.h"
#include "EventSystem.h"
#include "Grid.h"

Candy::Candy(GridGraph* gridGraph) :
	Item(gridGraph, Game::getInstance()->getAssetManager()->getSprite("candy_sprite"))
{
	EventSystem::addListener(static_cast<Event::EnumEventType>(GameEvent::EnumGameEventType::_PLAYER_MOVED_EVENT), this);
}

Candy::~Candy()
{

}

void Candy::handleEvent(const Event& theEvent)
{
	switch (theEvent.getType())
	{
	case GameEvent::EnumGameEventType::_PLAYER_MOVED_EVENT:
		checkIfPlayerInRadius(static_cast<const PlayerMovedEvent&>(theEvent).getPlayerPosition());
		break;
	}
}

void Candy::checkIfPlayerInRadius(const Vector2D& playerPosition)
{
	Grid* grid = mpGridGraph->getGrid();
	Vector2D distance = playerPosition - getPositionComponent()->getPosition();

	if (distance.getLengthSquared() < grid->getSquareSize() * grid->getSquareSize())
	{
		mShouldDelete = true;
		//Send event that adds score to player.
		EventSystem::fireEvent(PlayerAteCandy());
	}
}