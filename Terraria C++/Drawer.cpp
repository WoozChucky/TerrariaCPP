#include "Drawer.h"

Drawer::Drawer()
{
    myConsole = new Consola();
}
Drawer::~Drawer()
{
    delete this;
}

void Drawer::Draw(Miner obj, int ACTION)
{
    switch (ACTION)
        {
        case SHOW:
            myConsole->setTextColor(myConsole->PRETO);
            myConsole->gotoxy(obj.getX() * 5, obj.getY() * 5);
            std::cout << (char)255 << (char)255 << (char)2 << (char)255 << (char)255;

            myConsole->setTextColor(myConsole->VERMELHO_CLARO);
            myConsole->gotoxy(obj.getX() * 5, obj.getY() * 5 + 1);
            std::cout << (char)255 << (char)205 << (char)203 << (char)205 << (char)255;

            myConsole->gotoxy(obj.getX() * 5, obj.getY() * 5 + 2);
            std::cout << (char)255 << (char)255 << (char)186 << (char)255 << (char)255;

            myConsole->setTextColor(myConsole->AZUL);
            myConsole->gotoxy(obj.getX() * 5, obj.getY() * 5 + 3);
            std::cout << (char)255 << (char)255 << (char)202 << (char)255 << (char)255;

            myConsole->gotoxy(obj.getX() * 5, obj.getY() * 5 + 4);
            std::cout << (char)255 << (char)188 << (char)255 << (char)200 << (char)255;
            break;
        case REMOVE:
            myConsole->setTextColor(myConsole->PRETO);

            myConsole->gotoxy(obj.getX() * 5, obj.getY() * 5);
            std::cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)255;

            myConsole->gotoxy(obj.getX() * 5, obj.getY() * 5 + 1);
            std::cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)255;

            myConsole->gotoxy(obj.getX() * 5, obj.getY() * 5 + 2);
            std::cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)255;

            myConsole->gotoxy(obj.getX() * 5, obj.getY() * 5 + 3);
            std::cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)255;

            myConsole->gotoxy(obj.getX() * 5, obj.getY() * 5 + 4);
            std::cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)255;
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
            std::cout << "X: " << obj.getX() << " Y: " << obj.getY() << (char)255;

            myConsole->gotoxy(1, 36);
            std::cout << "Lives: ";
            myConsole->setTextColor(myConsole->VERDE);
            switch (obj.getExtraLiveCount())
                {
                case 3:
                    std::cout << (char)3 << (char)3 << (char)3;
                    break;
                case 2:
                    std::cout << (char)3 << (char)3;
                    break;
                case 1:
                    std::cout << (char)3;
                    break;
                }

            myConsole->setTextColor(myConsole->PRETO);
            myConsole->gotoxy(1, 37);
            std::cout << "Energy: ";
            myConsole->setTextColor(myConsole->VERDE);
            if (obj.getEnergyLevel() == 100)
                {
                    std::cout << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219;
                }
            else if (obj.getEnergyLevel() >= 90)
                {
                    std::cout << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)255;
                }
            else if (obj.getEnergyLevel() >= 80)
                {
                    std::cout << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)255 << (char)255;
                }
            else if (obj.getEnergyLevel() >= 70)
                {
                    std::cout << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)255 << (char)255 << (char)255;
                }
            else if (obj.getEnergyLevel() >= 60)
                {
                    std::cout << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)255 << (char)255 << (char)255 << (char)255;
                }
            else if (obj.getEnergyLevel() >= 50)
                {
                    std::cout << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255;
                }
            else if (obj.getEnergyLevel() >= 40)
                {
                    std::cout << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255;
                }
            else if (obj.getEnergyLevel() >= 30)
                {
                    std::cout << (char)219 << (char)219 << (char)219 << (char)219 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255;
                }
            else if (obj.getEnergyLevel() >= 20)
                {
                    std::cout << (char)219 << (char)219 << (char)219 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255;
                }
            else if (obj.getEnergyLevel() >= 10)
                {
                    std::cout << (char)219 << (char)219 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255;
                }
            std::cout << " " << obj.getEnergyLevel() << "/100" << (char)255;

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

            break;
        case REMOVE:
            break;
        }
}
void Drawer::DrawMine(Block ***obj, Miner obj2, int startDrawX, int startDrawY, int Vision, int Colunas, int Linhas)
{
    int piX = (obj2.getX() - Vision > 0) ? obj2.getX() - Vision : 0; //Initial X
    int piY = (obj2.getY() - Vision > 0) ? obj2.getY() - Vision : 0; //Initial Y

    int pfX = (obj2.getX() + Vision < Colunas) ? obj2.getX() + Vision : obj2.getX() + (Colunas - obj2.getX()) - 1; //Final X
    int pfY = (obj2.getY() + Vision < Linhas) ? obj2.getY() + Vision : obj2.getY() + (Linhas - obj2.getY()) - 1; //Final Y

    for (startDrawY = piY; startDrawY <= pfY; startDrawY++)
        {
            for (startDrawX = piX; startDrawX <= pfX; startDrawX++)
                {
                    (startDrawY >= piY && startDrawY <= pfY && startDrawX >= piX && startDrawX <= pfX) ? DrawBlock(obj[startDrawY][startDrawX]->getDrawSequence(), obj[startDrawY][startDrawX]->getX(), obj[startDrawY][startDrawX]->getY()) : 0;
                }
        }
}
void Drawer::DrawBlock(std::array<std::array<int, 5>, 5> charSequence, int _y, int _x)
{

    for (int x = 0; x < 5; x++)
        {
            myConsole->gotoxy(_y * 5, _x * 5 + x);
            for (int y = 0; y < 5; y++)
                {
                    std::cout << (char)charSequence[x][y];
                }

            std::cout << std::endl;
        }
}
