#include "AxisEvent.h"

AxisEvent::AxisEvent(Vector2D axisState)
    : Event(AXIS_EVENT)
{
    mState = axisState;
}

AxisEvent::~AxisEvent()
{

}