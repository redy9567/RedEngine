#pragma once
#include "MouseEvent.h"
#include "KeyboardEvent.h"

#include <string>
#include <sstream>

class Chicken;

class GameEvent : public Event
{
public:
    enum EventType
    {
        INVALID_EVENT_TYPE = -1,
        KEYBOARD_EVENT,
        MOUSE_EVENT,
        PLAYER_MOVE_EVENT,
        NUM_EVENT_TYPES
    };

    GameEvent(EventType type) : Event((Event::EventType)type) {};
    ~GameEvent() {};

    std::string getTypeName() const override { return "GameEvent"; }
    std::string getEventDetails() const override { return "None"; }

private:
    GameEvent() = delete;
    
};

union GameEventUnion
{
    const Event* event;
    const MouseEvent* mouseEvent;
    const KeyboardEvent* keyboardEvent;
};