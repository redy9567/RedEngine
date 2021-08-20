#include "GameListener.h"
#include "PlayerMoveEvent.h"
#include "KeyboardEvent.h"
#include "MouseEvent.h"
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
    else if(event.getType() == KEYBOARD_EVENT)
    {
        const KeyboardEvent& keyboardEvent = (const KeyboardEvent&)event;

        if(keyboardEvent.getButtonState() == BUTTON_DOWN)
        {
            Vector2D dir = Vector2D::Zero();

	        if(keyboardEvent.getKey() == Key_A)
	        {
		        dir += Vector2D::Left();
	        }
	        if(keyboardEvent.getKey() == Key_S)
	        {
		        dir += Vector2D::Down();
	        }
	        if(keyboardEvent.getKey() == Key_D)
	        {
		        dir += Vector2D::Right();
	        }
	        if(keyboardEvent.getKey() == Key_W)
	        {
		        dir += Vector2D::Up();
	        }

	        dir.normalize();

	        //cout << dir << endl;
	
	        Game::getInstance()->setPlayerMoveDir(dir);

            if(keyboardEvent.getKey() == Key_Escape)
	        {
                Game::getInstance()->quitGame();
	        }

            //Game::getInstance()->DKeyPress(keyboardEvent.getKey());
        }
        else if(keyboardEvent.getButtonState() == BUTTON_UP)
        {
            //Game::getInstance()->DKeyRelease(keyboardEvent.getKey());
        }
    }
    else if(event.getType() == MOUSE_EVENT)
    {
        const MouseEvent& mouseEvent = (const MouseEvent&)event;

        if(mouseEvent.getButtonState() == BUTTON_DOWN)
        {

            if(mouseEvent.getMouseButton() == 0)
	        {
		        Game::getInstance()->fireProj();
	        }

            //Game::getInstance()->DMousePress(mouseEvent.getMouseButton());
        }
        else if(mouseEvent.getButtonState() == BUTTON_UP)
        {
            //Game::getInstance()->DMouseRelease(mouseEvent.getMouseButton());
        }
    }
}