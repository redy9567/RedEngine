#include "KeyboardEvent.h"


KeyboardEvent::KeyboardEvent(KeyCode key, KeyState state)
    : Event(KEYBOARD_EVENT)
{
    mKey = key;
    mState = state;
}

KeyboardEvent::~KeyboardEvent()
{

}
