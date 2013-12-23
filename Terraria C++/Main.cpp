#include "Game.h"

int main(void)
{
    Game *myGame = new Game();
    myGame->Start();
    delete myGame;
    return 0;
}