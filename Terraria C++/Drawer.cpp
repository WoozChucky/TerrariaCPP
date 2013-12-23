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
            myConsole->setTextColor(myConsole->VERMELHO_CLARO);
            switch (obj.getLife())
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
            myConsole->setTextColor(myConsole->VERMELHO_CLARO);
            if (obj.getEnergy() == 100)
                {
                    std::cout << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219;
                }
            else if (obj.getEnergy() >= 90)
                {
                    std::cout << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)255;
                }
            else if (obj.getEnergy() >= 80)
                {
                    std::cout << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)255 << (char)255;
                }
            else if (obj.getEnergy() >= 70)
                {
                    std::cout << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)255 << (char)255 << (char)255;
                }
            else if (obj.getEnergy() >= 60)
                {
                    std::cout << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)255 << (char)255 << (char)255 << (char)255;
                }
            else if (obj.getEnergy() >= 50)
                {
                    std::cout << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255;
                }
            else if (obj.getEnergy() >= 40)
                {
                    std::cout << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255;
                }
            else if (obj.getEnergy() >= 30)
                {
                    std::cout << (char)219 << (char)219 << (char)219 << (char)219 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255;
                }
            else if (obj.getEnergy() >= 20)
                {
                    std::cout << (char)219 << (char)219 << (char)219 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255;
                }
            else if (obj.getEnergy() >= 10)
                {
                    std::cout << (char)219 << (char)219 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255;
                }
            std::cout << " " << obj.getEnergy() << "/100" << (char)255;

            myConsole->setTextColor(myConsole->PRETO);
            myConsole->gotoxy(1, 38);
            std::cout << "Coins: ";
            myConsole->setTextColor(myConsole->VERDE);
            std::cout << obj.getCoins();
            myConsole->setTextColor(myConsole->PRETO);
            break;
        case REMOVE:
            myConsole->gotoxy(2, 1);
            std::cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255;
            myConsole->gotoxy(2, 2);
            std::cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255;
            myConsole->gotoxy(2, 3);
            std::cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255;
            myConsole->gotoxy(2, 4);
            std::cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255;
            myConsole->gotoxy(0, 6);
            std::cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255;
            break;
        }
}
void Drawer::Draw(Block ***obj, Miner *obj2, int startDrawX, int startDrawY, int Vision, int Colunas, int Linhas)
{
    int piX = (obj2->getX() - Vision > 0) ? obj2->getX() - Vision : 0; //Initial X
    int piY = (obj2->getY() - Vision > 0) ? obj2->getY() - Vision : 0; //Initial Y

    int pfX = (obj2->getX() + Vision < Colunas) ? obj2->getX() + Vision : obj2->getX() + (Colunas - obj2->getX()) - 1; //Final X
    int pfY = (obj2->getY() + Vision < Linhas) ? obj2->getY() + Vision : obj2->getY() + (Linhas - obj2->getY()) - 1; //Final Y

    for (startDrawY = piY; startDrawY <= pfY; startDrawY++)
        {
            for (startDrawX = piX; startDrawX <= pfX; startDrawX++)
                {
                    (startDrawY >= piY && startDrawY <= pfY && startDrawX >= piX && startDrawX <= pfX) ? Draw(*obj[startDrawY][startDrawX]) : 0;
                }
        }
}
void Drawer::Draw(Pedra obj)
{
    myConsole->gotoxy(obj.getX(), obj.getY());
    std::cout << (char)218 << (char)196 << (char)196 << (char)196 << (char)191;
    myConsole->gotoxy(obj.getX(), obj.getY() + 1);
    std::cout << (char)179 << (char)219 << (char)219 << (char)219 << (char)179;
    myConsole->gotoxy(obj.getX(), obj.getY() + 2);
    std::cout << (char)179 << (char)219 << (char)219 << (char)219 << (char)179;
    myConsole->gotoxy(obj.getX(), obj.getY() + 3);
    std::cout << (char)179 << (char)219 << (char)219 << (char)219 << (char)179;
    myConsole->gotoxy(obj.getX(), obj.getY() + 4);
    std::cout << (char)192 << (char)196 << (char)196 << (char)196 << (char)217;
}
void Drawer::Draw(Block obj)
{
    myConsole->gotoxy(obj.getX(), obj.getY());
    std::cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)255;
    myConsole->gotoxy(obj.getX(), obj.getY() + 1);
    std::cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)255;
    myConsole->gotoxy(obj.getX(), obj.getY() + 2);
    std::cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)255;
    myConsole->gotoxy(obj.getX(), obj.getY() + 3);
    std::cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)255;
    myConsole->gotoxy(obj.getX(), obj.getY() + 4);
    std::cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)255;
}
void Drawer::Draw(Escada obj)
{

}
void Drawer::Draw(Viga obj)
{

}
void Drawer::Draw(TerrenoDuro obj)
{

}
void Drawer::Draw(TerrenoMole obj)
{

}
void Drawer::Draw(TerraCAluminio obj)
{

}
void Drawer::Draw(TerraCCarvao obj)
{

}
void Drawer::Draw(TerraCCarvao obj)
{

}
void Drawer::Draw(TerraCFrango obj)
{

}
void Drawer::Draw(TerraCFerro obj)
{

}
void Drawer::Draw(TerraCDiamante obj)
{

}
void Drawer::Draw(TerraCOuro obj)
{

}
