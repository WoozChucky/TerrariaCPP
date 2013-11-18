#include <iostream>
#include <istream>
#include <fstream>
#include <string>

#include "Menu.h"
#include "BlockTypes.h"



class Block {
	std::string name;
	int id;
	bool breakable;
	int x, y;
public:
	Block(Consola Console, std::string Name, int ID, bool Breakable, int X, int Y);
	void Draw(Consola Console);

};