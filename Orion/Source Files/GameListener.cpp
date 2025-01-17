#include "GameListener.h"
#include "KeyboardEvent.h"
#include "Game.h"

GameListener::GameListener()
{

}

GameListener::~GameListener()
{

}

void GameListener::handleEvent(const Event& evet)
{
    Game* game = Game::getInstance();

    // Cast away constness
    Event& nonConstBaseRef = const_cast<Event&>(evet);

    // Dynamic cast to Derived
    KeyboardEvent* keyEvent = dynamic_cast<KeyboardEvent*>(&nonConstBaseRef);

    switch (keyEvent->getKey())
    {
    case KeyCode::Num1:
        game->startScene1();
        break;

    case KeyCode::Num2:
        game->startScene2();
        break;

    case KeyCode::Num3:
        game->startScene3();
        break;
    }

}