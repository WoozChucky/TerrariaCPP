#include "Miner.h"

#define NUM_COMMANDS 10

class Menu {
public:
	int LoadMainMenu(Consola Console);
	void EscreverMainMenu(Consola Console);
	void NewGame(Consola Console);
	void LoadGame(Consola Console);
	void CommandMode(Consola Console);
};

