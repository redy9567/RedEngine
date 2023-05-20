#include "MouseEvent.h"

MouseEvent::MouseEvent(MouseAction button, ButtonState state, Vector2D mousePos)
    : Event(MOUSE_EVENT)
{
    mAction = button;
    mState = state;
    mMousePos = mousePos;
}

MouseEvent::~MouseEvent()
{

}