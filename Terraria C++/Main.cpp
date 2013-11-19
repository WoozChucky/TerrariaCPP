#include <iostream>
#include <istream>
#include <fstream>
#include <string>

#include "Game.h"
#include "Utensilio.h"

#define NUM_UTENSILIOS 19
#define UTENSILIOS_FILE_NAME "utensilios.txt"

void LoadUtensilios(Utensilio Utensilios[])
{
	std::ifstream utensiliosFile(UTENSILIOS_FILE_NAME, std::ifstream::in);
	std::string nome;
	int cost, K=0;

	if (utensiliosFile.is_open())
	{
		while (utensiliosFile >> nome >> cost) {
			Utensilios[K].setName(nome);
			Utensilios[K].setCost(cost);
			K++;
		}
	}
}

void main()
{
	Game *myGame = new Game();
	Utensilio Utensilios[NUM_UTENSILIOS];

	/* Loads utensilios data into array of objects*/
	LoadUtensilios(Utensilios);

	while (myGame->Status() != myGame->END)
		myGame->Start();

	myGame->Write("Game Over");

	system("pause");

	return;
}