#pragma once

#include "EventListener.h"

class GameListener : EventListener
{
public:
    GameListener();
    ~GameListener();

    void handleEvent(const Event&) override;
};