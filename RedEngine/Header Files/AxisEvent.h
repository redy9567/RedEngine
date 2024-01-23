#pragma once

#include "Event.h"
#include "Vector2D.h"
#include <string>

enum class Axis
{
    Horizontal,
    Vertical
};

class AxisEvent : public Event
{

public:
    AxisEvent(Vector2D axisState);
    ~AxisEvent();

    Vector2D getState() const { return mState; }
    float getAxis(Axis a) const { (a == Axis::Horizontal) ? mState.getX() : mState.getY(); }

    std::string getTypeName() const override { return "AxisEvent"; }
    std::string getEventDetails() const override { return "Axis Event: " + mState.toString(); }

private:
    AxisEvent() = delete;

    Vector2D mState;

};