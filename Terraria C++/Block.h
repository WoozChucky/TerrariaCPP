#include <iostream>
#include <istream>
#include <fstream>
#include <string>
#include <vector>

#include "Miner.h"

class BlockTypes{
	std::vector<std::string> Name;
	std::vector<int> ID;
	std::vector<bool> Breakable;

public:
	BlockTypes() :
		Name({ "Pedra", "Terreno duro", "Terreno mole", "Ouro", "Lava" }),
		ID({ 0, 1, 2, 3, 4 }),
		Breakable({ false, true, true, true, false })	{};

	std::string getName(int ID){ return Name[ID]; }
	bool isBrekeable(int ID){ return Breakable[ID]; }
};

class Block {
	std::string name;
	int id;
	bool breakable;
	int x, y;
public:
	Block(std::string Name, int ID, bool Breakable, int X, int Y);
	void Draw(Consola Console);

};