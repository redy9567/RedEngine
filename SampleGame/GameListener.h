#pragma once

#include "EventListener.h"

class GameListener : public EventListener
{

public:
    GameListener();
    ~GameListener();

    void handleEvent(const Event&);

};