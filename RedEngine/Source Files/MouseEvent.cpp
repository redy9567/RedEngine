#include "MouseEvent.h"

MouseEvent::MouseEvent(MouseAction button, ButtonState state, Vector2D mousePos, Vector2D scrollOffset)
    : Event(MOUSE_EVENT)
{
    mAction = button;
    mState = state;
    mMousePos = mousePos;
    mScrollOffset = scrollOffset;
}

MouseEvent::~MouseEvent()
{

}