#include "Game.h"

#include "MemoryTracker.h"
#include "Timer.h"

#include <iostream>

//TEST INCLUDE
#include <RTTI.h>

const int screenWidth = 800;
const int screenHeight = 450;

int main()
{

    //Initialize runtime timer
    Timer t;
    t.start();
    
    //TEST CODE
    TestObject tes(true, 2, 4.4, "helmo");

    RTTISystem* rttiSys = RTTISystem::getInstance();

    rttiSys->update();

    //Play Game
    Game::getInstance()->init(screenWidth, screenHeight, 60, true);
    Game::getInstance()->startGame();
    Game::getInstance()->cleanup();
    Game::cleanupInstance();

    //Track Memory Leaks
    MemoryTracker::cleanupInstance();

    //Output runtime
    std::cout << "----------Total runtime: " << t.getElapsedTime() << std::endl;

    std::string temp;
    std::cin >> temp;

    return 0;
}
