#include <vector>
#include <iostream>

class BlockTypes{
	std::vector<std::string> Name;
	std::vector<int> ID;
	std::vector<bool> Breakable;

public:
	BlockTypes(std::initializer_list<std::string> N, std::initializer_list<int> T, std::initializer_list<bool> B) : Name(N), ID(T), Breakable(B){};

	std::string getName(int ID){ return Name[ID];  }
	bool isBrekeable(int ID){ return Breakable[ID]; }
};