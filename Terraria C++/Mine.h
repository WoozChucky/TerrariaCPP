#include <map>

#include "Block.h"


class Mine{
	int **mina;
	std::vector<Block> blocks;
	int rows, cols;
public:
	Mine();
	void Initialize(int Rows, int Cols);
	void Draw();
	bool isColliding(Miner myMiner);
	void DrawBlock(int ID, int x, int y);
};