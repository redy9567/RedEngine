#pragma once

#include "Event.h"
#include "Vector2D.h"
#include <string>

enum class MouseAction
{
    LeftClick,
    RightClick,
    MiddleClick,
    Move
};

enum class ButtonState
{
    None = -1,
    Down,
    Hold,
    Up,
};

class MouseEvent : public Event
{

public:
    MouseEvent(MouseAction button, ButtonState state, Vector2D mousePos);
    ~MouseEvent();

    MouseAction getMouseAction() const { return mAction; }
    ButtonState getButtonState() const { return mState; }
    Vector2D getMousePosition() const { return mMousePos; }

    std::string getTypeName() const override { return "MouseEvent"; }
    std::string getEventDetails() const override { return "Mouse Action: " + std::to_string((int)mAction) + " Button State: " + std::to_string((int)mState) + " Mouse Pos: " + mMousePos.toString(); }

private:
    MouseEvent() = delete;

    MouseAction mAction;
    ButtonState mState;
    Vector2D mMousePos;

};