#include "Game.h"

void main()
{
    Game *myGame = new Game();
    myGame->Start();
    delete myGame;
    return;
}