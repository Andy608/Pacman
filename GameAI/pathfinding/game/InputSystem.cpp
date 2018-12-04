#include "InputSystem.h"
#include "System.h"
#include "Event.h"
#include "EventSystem.h"

InputSystem::InputSystem() :
	mIsInitialized(false)
{

}

InputSystem::~InputSystem()
{
	cleanup();
}

bool InputSystem::init()
{
	mIsInitialized = true;
	return mIsInitialized;
}

void InputSystem::cleanup()
{
	mIsInitialized = false;
}

void InputSystem::update(float deltaTime)
{
	while (SDL_PollEvent(&mpEventQueue))
	{
		switch (mpEventQueue.type)
		{
		case SDL_KEYDOWN:
			EventSystem::getInstance()->fireEvent(KeyboardEvent(mpEventQueue.key.keysym.sym, true, mIsNewKeyPress));
			
			if (mIsNewKeyPress)
			{
				mIsNewKeyPress = false;
			}

			break;
		case SDL_KEYUP:
			EventSystem::getInstance()->fireEvent(KeyboardEvent(mpEventQueue.key.keysym.sym, false, mIsNewKeyPress));
			mIsNewKeyPress = true;
			break;
		case SDL_MOUSEBUTTONDOWN:
			mIsMouseDown = true;
			EventSystem::getInstance()->fireEvent(MouseEvent(mpEventQueue.button.button, mIsMouseDown, mIsNewMousePress, mpEventQueue.button.x, mpEventQueue.button.y));

			if (mIsNewMousePress)
			{
				mIsNewMousePress = false;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			mIsMouseDown = false;
			EventSystem::getInstance()->fireEvent(MouseEvent(mpEventQueue.button.button, mIsMouseDown, mIsNewMousePress, mpEventQueue.button.x, mpEventQueue.button.y));
			mIsNewMousePress = true;
			break;
		case SDL_MOUSEMOTION:
			EventSystem::getInstance()->fireEvent(MouseEvent(mpEventQueue.button.button, mIsMouseDown, mIsNewMousePress, mpEventQueue.button.x, mpEventQueue.button.y));
			break;
		case SDL_QUIT:
			EventSystem::getInstance()->fireEvent(WindowClosedEvent());
			break;
		}
	}
}

SDL_Event InputSystem::getEventQueue() const
{
	return mpEventQueue;
}

Vector2D InputSystem::getMousePosition() const
{
	int x, y;
	SDL_GetMouseState(&x, &y);

	return Vector2D(x, y);
}