#include "PlayerMoveEvent.h"

PlayerMoveEvent::PlayerMoveEvent(Vector2D loc)
    : Event(PLAYER_MOVE_EVENT)
{
    moveLoc = loc;
}

PlayerMoveEvent::~PlayerMoveEvent()
{
    
}

std::string PlayerMoveEvent::getEventDetails() const
{
    return moveLoc.toString();
}