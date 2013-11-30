#include <iostream>
#include <istream>
#include <fstream>
#include <string>

#include "Game.h"
#include "Utensilio.h"

void main()
{
    Game *myGame = new Game();
    Utensilio Utensilios[NUM_UTENSILIOS];

    /* Loads utensilios data into array of objects*/
    LoadUtensilios(Utensilios);

    while (myGame->Status() != myGame->END)
        {
            myGame->Start();
        }
    myGame->Write("Game Over");
    system("pause");
    return;
}