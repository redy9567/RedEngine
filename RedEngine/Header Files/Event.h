#pragma once

#include "Trackable.h"

#include <string>

class Event : public Trackable
{

public:
    enum EventType
    {
        INVALID_EVENT_TYPE = -1,
        KEYBOARD_EVENT,
        MOUSE_EVENT,
        AXIS_EVENT,
        PLAYER_MOVE_EVENT,
        NUM_EVENT_TYPES
    };

    Event(EventType);
    virtual ~Event();

    EventType getType() const { return mType; }
    virtual std::string getTypeName() const { return "Event"; }
    virtual std::string getEventDetails() const = 0;

private:
    Event() = delete;

    EventType mType;

};