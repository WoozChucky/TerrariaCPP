#include <map>

#include "Block.h"


class Mine{
	std::vector<Block> blocks;
	int rows, cols;
	static const int matrix = 5;
public:
	Mine();
	void Initialize(int Rows, int Cols);
	void Draw(Consola Console);
	bool isColliding(Miner myMiner, Block myBlock);
};