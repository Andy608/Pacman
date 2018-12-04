#ifndef GAME_EVENT_H_
#define GAME_EVENT_H_

#include "Event.h"

class GameEvent : public Event
{
public:
	enum EnumGameEventType : int
	{
		//Hot air balloons use fire to trap gas and make the balloons go up
		_BURN_FUEL_EVENT = EnumEventType::_NUM_EVENT_TYPES + 1,
		_LANGUAGE_CHANGED_EVENT,
		_PLAYER_MOVED_EVENT,
		_PLAYER_ATE_CANDY_EVENT,
		_PLAYER_ATE_ENEMY_EVENT,
		_NUM_EVENT_TYPES
	};

	inline GameEvent(EnumGameEventType type)
		try : Event(static_cast<EnumEventType>(type))
	{

	}
	catch (...)
	{
		std::cout << "No event with type id: \'" << std::to_string(type) << "\'." << std::endl;
	}
};

class PlayerMovedEvent : public GameEvent
{
public:
	inline PlayerMovedEvent(Vector2D playerPosition) :
		GameEvent(GameEvent::EnumGameEventType::_PLAYER_MOVED_EVENT),
		mPlayerPosition(playerPosition)
	{};

	inline const Vector2D& getPlayerPosition() const { return mPlayerPosition; };

private:
	Vector2D mPlayerPosition;
};

class PlayerAteCandy : public GameEvent
{
public:
	inline PlayerAteCandy() :
		GameEvent(GameEvent::EnumGameEventType::_PLAYER_ATE_CANDY_EVENT)
	{};
};

class PlayerAteEnemy : public GameEvent
{
public:
	inline PlayerAteEnemy() :
		GameEvent(GameEvent::EnumGameEventType::_PLAYER_ATE_ENEMY_EVENT)
	{};
};

class BurnFuelEvent : public GameEvent
{
public:
	inline BurnFuelEvent(bool shouldBurnFuel) :
		GameEvent(GameEvent::EnumGameEventType::_BURN_FUEL_EVENT),
		mShouldBurnFuel(shouldBurnFuel)
	{};

	inline bool shouldBurnFuel() const { return mShouldBurnFuel; };

private:
	bool mShouldBurnFuel;
};

class LanguageChangedEvent : public GameEvent
{
public:
	inline LanguageChangedEvent() :
		GameEvent(GameEvent::EnumGameEventType::_LANGUAGE_CHANGED_EVENT) {};
};

#endif