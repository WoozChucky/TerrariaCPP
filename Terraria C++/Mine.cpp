#include "Mine.h"

Mine::Mine()
{
    blocks =
    {
        Block({ 0, false, NULL }),
        Block({ 0, true, 10 })
    };

}

void Mine::Initialize(int Rows, int Cols, int Vision)
{
    rows = Rows;
    cols = Cols;
    vision = Vision;

    /*Create Mine Array Dinamically*/
    mina = new int*[rows];
    for (int r = 0; r < rows; r++)
        mina[r] = new int[cols];

    /* Populate Mine Array Automatically*/
    for (int x = 0; x < rows; x++)
        {
            for (int y = 0; y < cols; y++)
                {
                    int random = rand() % 1;
                    mina[x][y] = random; //ID Bloco
                    // AI da Mine
                }
        }

    Draw();

}

void Mine::DrawBlock(int ID, int x, int y)
{
    Consola Console; //REMOVE
    switch (ID)
        {
        case 0:
            Console.gotoxy(x, y);
            std::cout << (char)218 << (char)196 << (char)196 << (char)196 << (char)191;

            Console.gotoxy(x, y + 1);
            std::cout << (char)179 << (char)219 << (char)219 << (char)219 << (char)179;

            Console.gotoxy(x, y + 2);
            std::cout << (char)179 << (char)219 << (char)219 << (char)219 << (char)179;

            Console.gotoxy(x, y + 3);
            std::cout << (char)179 << (char)219 << (char)219 << (char)219 << (char)179;

            Console.gotoxy(x, y + 4);
            std::cout << (char)192 << (char)196 << (char)196 << (char)196 << (char)217;
            break;
        case 1:
            break;
        case 2:
            break;

        }
}

void Mine::Draw()
{
    for (int x = 0; x < rows; x++)
        {
            for (int y = 0; y < cols; y++)
                {
                    DrawBlock(mina[x][y], y * 5, x * 5);
                }
        }
}

bool Mine::isColliding(Miner myMiner)
{
    //for (auto it : blocks)
    //{
    //	if (myMiner.X1 < it.X2 && myMiner.X2 > it.X1 && myMiner.Y1 < it.Y2 && myMiner.Y2 > it.Y1)
    //		return true;
    //}
    //return false;
    return false;
}