#include "Player.h"
#include "EventSystem.h"
#include "Game.h"
#include "AssetManager.h"
#include "InputSystem.h"
#include "Grid.h"
#include "GameEvent.h"
#include "SteeringComponent.h"
#include "PathSteering.h"

Player::Player(GridGraph* pGridGraph) :
	Unit(pGridGraph, Game::getInstance()->getAssetManager()->getSprite("player_sprite"))
{
	EventSystem::addListener(GameEvent::EnumEventType::_INPUT_EVENT, this);
}

Player::~Player()
{

}

void Player::handleEvent(const Event& theEvent)
{
	switch (theEvent.getType())
	{
	case Event::EnumEventType::_INPUT_EVENT:
		handleInput(static_cast<const KeyboardEvent&>(theEvent));
		break;
	}
}

void Player::update(float deltaTime) {}

void Player::draw() const
{
	Unit::draw();
}

void Player::handleInput(const KeyboardEvent& theEvent)
{
	if (!theEvent.isKeyDown() || !theEvent.isNewKeyPress())
	{
		return;
	}

	//Target Position
	Grid* grid = mpGridGraph->getGrid();
	Vector2D currentPlayerPosition = mpPositionComponent->getPosition()/* + grid->getSquareSize() / 2.0f*/;
	static const Vector2D UP = Vector2D(0, -grid->getSquareSize());
	static const Vector2D RIGHT = Vector2D(grid->getSquareSize(), 0);

	//For all cases, only add if it's a floor tile
	if (theEvent.getInputCode() == EnumKeyInput::W_KEY)
	{
		//Add up to target
		if (grid->getValueAtPosition(mTargetPosition + UP) != grid->sWALL_ID)
		{
			mTargetPosition += UP;
		}
	}
	
	if (theEvent.getInputCode() == EnumKeyInput::S_KEY)
	{
		//Add down to target
		if (grid->getValueAtPosition(mTargetPosition - UP) != grid->sWALL_ID)
		{
			mTargetPosition -= UP;
		}
	}

	if (theEvent.getInputCode() == EnumKeyInput::D_KEY)
	{
		//Add right to target
		if (grid->getValueAtPosition(mTargetPosition + RIGHT) != grid->sWALL_ID)
		{
			mTargetPosition += RIGHT;
		}
	}

	if (theEvent.getInputCode() == EnumKeyInput::A_KEY)
	{
		//Add left to target
		if (grid->getValueAtPosition(mTargetPosition - RIGHT) != grid->sWALL_ID)
		{
			mTargetPosition -= RIGHT;
		}
	}

	int targetIndex = grid->getSquareIndexFromPosition(mTargetPosition);

	//If target is not the same node we are on, create the path
	//to the next node
	if (targetIndex != grid->getSquareIndexFromPosition(currentPlayerPosition))
	{
		//Send a create path event so the player moves to the new target point.
		int toIndex = targetIndex;
		int fromIndex = grid->getSquareIndexFromPosition(currentPlayerPosition);
		Node* pToNode = mpGridGraph->getNode(toIndex);
		Node* pFromNode = mpGridGraph->getNode(fromIndex);

		Path* path = mpPathfinder->findPath(pFromNode, pToNode);

		getPositionComponent()->setPosition(mTargetPosition);
		EventSystem::fireEvent(PlayerMovedEvent(mTargetPosition));
	}
}