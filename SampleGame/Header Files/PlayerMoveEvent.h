#pragma once

#include "Event.h"
#include "Vector2D.h"

class PlayerMoveEvent : public Event
{

public:
    PlayerMoveEvent(Vector2D loc);
    ~PlayerMoveEvent();

    Vector2D getMoveLoc() const { return moveLoc; }

    virtual std::string getTypeName() const { return "PlayerMoveEvent"; }
    virtual std::string getEventDetails() const;

private:
    PlayerMoveEvent() = delete;

    Vector2D moveLoc;

};