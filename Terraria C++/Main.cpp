#include <iostream>
#include <istream>
#include <fstream>
#include <string>

#include "Game.h"
#include "Utensilio.h"

void main()
{
    Game *myGame = new Game();

    //TODO: Insert Utensilios into Game Class
    Utensilio Utensilios[NUM_UTENSILIOS];
    /* Loads utensilios data into array of objects*/
    LoadUtensilios(Utensilios);

    myGame->Start();
    delete myGame;
    return;
}