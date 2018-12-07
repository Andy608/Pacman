#ifndef GAME_EVENT_H_
#define GAME_EVENT_H_

#include "Event.h"

class GameEvent : public Event
{
public:
	enum EnumGameEventType : int
	{
		//Hot air balloons use fire to trap gas and make the balloons go up
		_LANGUAGE_CHANGED_EVENT = EnumEventType::_NUM_EVENT_TYPES + 1,
		_PLAYER_MOVED_EVENT,
		_PLAYER_ATE_CANDY_EVENT,
		_PLAYER_ATE_ENEMY_EVENT,
		_PLAYER_ATE_COIN_EVENT,
		_GAME_LOST_EVENT,
		_GAME_END_EVENT,
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

class PlayerAteCoin : public GameEvent
{
public:
	inline PlayerAteCoin() :
		GameEvent(GameEvent::EnumGameEventType::_PLAYER_ATE_COIN_EVENT)
	{};
};

class GameLost : public GameEvent
{
public:
	inline GameLost() :
		GameEvent(GameEvent::EnumGameEventType::_GAME_LOST_EVENT)
	{};
};

class GameEnded : public GameEvent
{
public:
	inline GameEnded(bool playerWin) :
		GameEvent(GameEvent::EnumGameEventType::_GAME_END_EVENT),
		mPlayerWin(playerWin)
	{};

	const bool& getPlayerWin() const { return mPlayerWin; };

private:
	bool mPlayerWin = false;
};

class LanguageChangedEvent : public GameEvent
{
public:
	inline LanguageChangedEvent() :
		GameEvent(GameEvent::EnumGameEventType::_LANGUAGE_CHANGED_EVENT) {};
};

#endif