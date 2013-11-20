#include "Mine.h"

Mine::Mine()
{
	blocks = {
		Block({ "Rock", 1, 1, 2, 13 }),
		Block({ "Rock", 1, 1, 12, 13 }),
		Block({ "Rock", 1, 1, 2, 17 }),
		Block({ "Rock", 1, 1, 2, 9 }),
		Block({ "Rock", 1, 1, 22, 13 }),
		Block({ "Rock", 1, 1, 27, 13 }),
		Block({ "Rock", 1, 1, 32, 13 }),
		Block({ "Rock", 1, 1, 7, 13 })
	};

}

void Mine::Initialize(int Rows, int Cols)
{
	rows = Rows;
	cols = Cols;

	int matriz[matrix];
	//TODO: get new array method
}

void Mine::Draw(Consola Console)
{
	for (auto it : blocks)
		it.Draw(Console);
}

bool Mine::isColliding(Miner myMiner, Block myBlock)
{
	for (auto it : blocks)
	{
		//if (myMiner.X1 < it.X2 && myMiner.X2 > it.X1 && myMiner.Y1 < it.Y2 && myMiner.Y2 > it.Y1)
			return true;
	}
	return false;
}