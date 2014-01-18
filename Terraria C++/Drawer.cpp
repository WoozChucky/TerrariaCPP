#include "Drawer.h"

Drawer::Drawer()
{
    myConsole = new Consola();
}
Drawer::~Drawer()
{
    delete myConsole;
}

void Drawer::Draw(Miner obj, int datX, int datY, int ACTION, int SPECIAL)
{
    switch (ACTION)
        {
        case SHOW:
            switch (SPECIAL)
                {
                case 0:
                    myConsole->setTextColor(myConsole->PRETO);
                    myConsole->gotoxy(datX, datY);
                    std::cout << (char)255 << (char)255 << (char)2 << (char)255 << (char)255;

                    myConsole->gotoxy(datX, datY + 1);
                    std::cout << (char)255 << (char)205 << (char)203 << (char)205 << (char)255;

                    myConsole->gotoxy(datX, datY + 2);
                    std::cout << (char)255 << (char)255 << (char)186 << (char)255 << (char)255;

                    myConsole->gotoxy(datX, datY + 3);
                    std::cout << (char)255 << (char)255 << (char)202 << (char)255 << (char)255;

                    myConsole->gotoxy(datX, datY + 4);
                    std::cout << (char)255 << (char)188 << (char)255 << (char)200 << (char)255;
                    break;
                case 1: //Ladder
                    myConsole->setTextColor(myConsole->PRETO);
                    myConsole->gotoxy(datX, datY);
                    std::cout << (char)45 << (char)255 << (char)2 << (char)45 << (char)180;

                    myConsole->gotoxy(datX, datY + 1);
                    std::cout << (char)195 << (char)205 << (char)203 << (char)205 << (char)180;

                    myConsole->gotoxy(datX, datY + 2);
                    std::cout << (char)195 << (char)45 << (char)186 << (char)45 << (char)180;

                    myConsole->gotoxy(datX, datY + 3);
                    std::cout << (char)195 << (char)45 << (char)202 << (char)45 << (char)180;

                    myConsole->gotoxy(datX, datY + 4);
                    std::cout << (char)195 << (char)188 << (char)45 << (char)200 << (char)180;
                    break;
                case 2: //Beam
                    myConsole->setTextColor(myConsole->PRETO);
                    myConsole->gotoxy(datX, datY);
                    std::cout << (char)203 << (char)255 << (char)2 << (char)255 << (char)203;

                    myConsole->gotoxy(datX, datY + 1);
                    std::cout << (char)179 << (char)205 << (char)203 << (char)205 << (char)179;

                    myConsole->gotoxy(datX, datY + 2);
                    std::cout << (char)255 << (char)255 << (char)186 << (char)255 << (char)255;

                    myConsole->gotoxy(datX, datY + 3);
                    std::cout << (char)255 << (char)255 << (char)202 << (char)255 << (char)255;

                    myConsole->gotoxy(datX, datY + 4);
                    std::cout << (char)255 << (char)188 << (char)255 << (char)200 << (char)255;
                    break;
                }
            break;
        case REMOVE:
            break;
        }

}
void Drawer::DrawStats(Miner obj, int ACTION)
{
    switch (ACTION)
        {
        case SHOW:
            myConsole->setTextColor(myConsole->PRETO);
            myConsole->gotoxy(1, 35);
            std::cout << "X: " << obj.getX() << " Y: " << obj.getY();

            myConsole->gotoxy(1, 36);
            std::cout << "Lives: ";
            myConsole->setTextColor(myConsole->VERDE);
            for (int i = 0; i < obj.getExtraLiveCount(); i++)
                std::cout << (char)3;

            myConsole->setTextColor(myConsole->PRETO);
            myConsole->gotoxy(1, 37);
            std::cout << "Energy: ";
            myConsole->setTextColor(myConsole->VERDE);
            std::cout << obj.getEnergyLevel();
            myConsole->setTextColor(myConsole->PRETO);
            myConsole->gotoxy(1, 38);
            std::cout << "Coins: ";
            myConsole->setTextColor(myConsole->VERDE);
            std::cout << obj.getCoins();
            myConsole->gotoxy(1, 39);
            myConsole->setTextColor(myConsole->PRETO);
            std::cout << "Bag: ";
            myConsole->setTextColor(myConsole->VERDE);
            std::cout << obj.getCapacity() << "/" << obj.getMaxCapacity();
            myConsole->gotoxy(1, 40);
            myConsole->setTextColor(myConsole->PRETO);
            std::cout << "Ladders: ";
            myConsole->setTextColor(myConsole->VERDE);
            std::cout << obj.getLadderCount();
            myConsole->gotoxy(1, 41);
            myConsole->setTextColor(myConsole->PRETO);
            std::cout << "Beams: ";
            myConsole->setTextColor(myConsole->VERDE);
            std::cout << obj.getBeamCount();
            myConsole->setTextColor(myConsole->PRETO);
            myConsole->gotoxy(1, 42);
            myConsole->setTextColor(myConsole->PRETO);
            std::cout << "Dynamites: ";
            myConsole->setTextColor(myConsole->VERDE);
            std::cout << obj.getDynamiteCount();
            myConsole->setTextColor(myConsole->PRETO);
            myConsole->gotoxy(1, 43);
            std::cout << "Parachutes: ";
            myConsole->setTextColor(myConsole->VERDE);
            std::cout << obj.getParachuteCount();
            myConsole->setTextColor(myConsole->PRETO);
            break;
        case REMOVE:
            break;
        }
}
void Drawer::DrawMine(Block ***obj, Miner obj2, int startDrawX, int startDrawY, int Vision, int Colunas, int Linhas)
{

    int rMinimum = (obj2.getY() - Vision > 0) ? obj2.getY() - Vision : 0;
    int rMaximum = (obj2.getY() + Vision < Linhas) ? obj2.getY() + Vision : obj2.getY() + (Linhas - obj2.getY());

    int cMinimum = (obj2.getX() - Vision > 0) ? obj2.getX() - Vision : 0;
    int cMaximum = (obj2.getX() + Vision < Colunas) ? obj2.getX() + Vision : obj2.getX() + (Colunas - obj2.getX());

    for (int r = 0, mineR = startDrawY; r < 7; r++, mineR++)
        {
            for (int c = 0, mineC = startDrawX; c < 7; c++, mineC++)
                {
                    if (obj2.getX() == mineC && obj2.getY() == mineR)
                        {
                            if (typeid(*obj[mineR][mineC]).name() == typeid(Escada).name())
                                {
                                    Draw(obj2, c * 5, r * 5, SHOW, 1);
                                }
                            else if (typeid(*obj[mineR][mineC]).name() == typeid(Viga).name())
                                {
                                    Draw(obj2, c * 5, r * 5, SHOW, 2);
                                }
                            else
                                Draw(obj2, c * 5, r * 5, SHOW, 0);
                        }
                    else if (mineR >= rMinimum && mineR <= rMaximum && mineC >= cMinimum && mineC <= cMaximum)
                        {
                            DrawBlock(obj[mineR][mineC]->getDrawSequence(), c * 5, r * 5);
                        }
                }
        }
}
void Drawer::DrawBlock(std::array<std::array<int, 5>, 5> charSequence, int _y, int _x)
{
    for (int x = 0; x < 5; x++)
        {
            myConsole->gotoxy(_y, _x + x);
            for (int y = 0; y < 5; y++)
                {
                    std::cout << (char)charSequence[x][y];
                }

            std::cout << std::endl;
        }
}
void Drawer::DrawPauseMenu()
{
    myConsole->gotoxy(14, 2);
    std::cout << " -----Pause-----";
    myConsole->gotoxy(10, 8);
    std::cout << "** Choose an option **";
    myConsole->gotoxy(10, 10);
    std::cout << "Continue";
    myConsole->gotoxy(10, 12);
    std::cout << "Sound";
    myConsole->gotoxy(10, 14);
    std::cout << "Main Menu";
}