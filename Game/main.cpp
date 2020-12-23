#include "Game.h"

int main()
{

	Game* theGame = new Game();

	theGame->init();
	theGame->doLoop();
	theGame->cleanup();

	return 0;

}