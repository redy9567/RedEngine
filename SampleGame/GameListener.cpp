#include "GameListener.h"
#include "PlayerMoveEvent.h"
#include "Game.h"

GameListener::GameListener()
{

}

GameListener::~GameListener()
{

}

void GameListener::handleEvent(const Event& event)
{
    if(event.getType() == PLAYER_MOVE_EVENT)
    {
        const PlayerMoveEvent& moveEvent = (const PlayerMoveEvent&)event;

        Game::getInstance()->DPlayerMove(moveEvent.getMoveLoc());
    }
}