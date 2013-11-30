#include <map>
#include "Block.h"

class Mine
{
    int **mina;
    std::vector<Block> blocks;
    int rows, cols, vision;
public:
    Mine();
    void Initialize(int Rows, int Cols, int Vision);
    void Draw();
    bool isColliding(Miner myMiner);
    void DrawBlock(int ID, int x, int y);
};