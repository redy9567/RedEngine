#include "GameListener.h"
#include "Event.h"
#include "Game.h"
#include "GameEvents.h"

GameListener::GameListener()
{

}

GameListener::~GameListener()
{

}

void GameListener::handleEvent(const Event& ev)
{
	Game* game = Game::getInstance();

	GameEventUnion* eventUnion = new GameEventUnion();
	eventUnion->event = &ev;

	switch(ev.getType())
	{
	case Event::MOUSE_EVENT:

		if (eventUnion->mouseEvent->getMouseAction() == MouseAction::Move)
			game->onMouseMove(eventUnion->mouseEvent->getMousePosition());
		else
			game->onClick(*eventUnion->mouseEvent);

		break;

	case Event::KEYBOARD_EVENT:
		if (eventUnion->keyboardEvent->getButtonState() == KeyState::Down)
		{
			switch (eventUnion->keyboardEvent->getKey())
			{
			case KeyCode::F1:
				game->onToggleDrawMode();
				break;

			case KeyCode::F2:
				game->onToggleShaders();
				break;

			case KeyCode::F4:
				game->onShaderHotReload();
				break;

			case KeyCode::F5:
				game->onToggleDebugMode();
				break;
			}
		}
		break;

	case Event::AXIS_EVENT:
		game->onAxis(*eventUnion->axisEvent);
		break;
	}

	delete eventUnion;
}