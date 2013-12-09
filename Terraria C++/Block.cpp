#include "Block.h"

/* Gets */
int Block::getX() const
{
    return _x;
}
int Block::getY() const
{
    return _y;
}
std::string Block::getID() const
{
    return _id;
}
int Block::getTicks() const
{
    return _ticks;
}
int Block::getBreakeable() const
{
    return _breakeable;
}

/* Sets */
void Block::setX(int S)
{
    _x = S;
}
void Block::setY(int S)
{
    _y = S;
}
void Block::setID(std::string S)
{
    _id = S;
}
void Block::setTicks(int S)
{
    _ticks = S;
}
void Block::setBreakeable(int S)
{
    _breakeable = S;
}

/* Draws */
void Block::DrawBlock(std::string id, int x, int y)
{

    if (id == "M")
        {
            /*gotoxy(x, y);
            std::cout << (char)255 << (char)255 << (char)2 << (char)255 << (char)255;

            gotoxy(x, y + 1);
            std::cout << (char)255 << (char)205 << (char)203 << (char)205 << (char)255;

            gotoxy(x, y + 2);
            std::cout << (char)255 << (char)255 << (char)186 << (char)255 << (char)255;

            gotoxy(x, y + 3);
            std::cout << (char)255 << (char)255 << (char)202 << (char)255 << (char)255;

            gotoxy(x, y + 4);
            std::cout << (char)255 << (char)188 << (char)255 << (char)200 << (char)255;*/
        }
    else if (id == "TD")
        {

            setTextColor(PRETO);
            gotoxy(x, y);
            std::cout << (char)218 << (char)196 << (char)196 << (char)196 << (char)191;
            gotoxy(x, y + 1);
            std::cout << (char)179 << (char)178 << (char)178 << (char)178 << (char)179;
            gotoxy(x, y + 2);
            std::cout << (char)179 << (char)178 << (char)178 << (char)178 << (char)179;
            gotoxy(x, y + 3);
            std::cout << (char)179 << (char)178 << (char)178 << (char)178 << (char)179;
            gotoxy(x, y + 4);
            std::cout << (char)192 << (char)196 << (char)196 << (char)196 << (char)217;
        }

    else if (id == "P")
        {
            gotoxy(x, y);
            std::cout << (char)218 << (char)196 << (char)196 << (char)196 << (char)191;
            gotoxy(x, y + 1);
            std::cout << (char)179 << (char)219 << (char)219 << (char)219 << (char)179;
            gotoxy(x, y + 2);
            std::cout << (char)179 << (char)219 << (char)219 << (char)219 << (char)179;
            gotoxy(x, y + 3);
            std::cout << (char)179 << (char)219 << (char)219 << (char)219 << (char)179;
            gotoxy(x, y + 4);
            std::cout << (char)192 << (char)196 << (char)196 << (char)196 << (char)217;
        }
    else if (id == "TM")
        {
            setTextColor(PRETO);
            gotoxy(x, y);
            std::cout << (char)218 << (char)196 << (char)196 << (char)196 << (char)191;
            gotoxy(x, y + 1);
            std::cout << (char)179 << (char)176 << (char)176 << (char)176 << (char)179;
            gotoxy(x, y + 2);
            std::cout << (char)179 << (char)176 << (char)176 << (char)176 << (char)179;
            gotoxy(x, y + 3);
            std::cout << (char)179 << (char)176 << (char)176 << (char)176 << (char)179;
            gotoxy(x, y + 4);
            std::cout << (char)192 << (char)196 << (char)196 << (char)196 << (char)217;
        }
    else if (id == "TcD")
        {
            gotoxy(x, y);

            std::cout << (char)218 << (char)196 << (char)196 << (char)196 << (char)191;
            gotoxy(x, y + 1);
            std::cout << (char)179;
            setTextColor(AZUL_CLARO);
            std::cout << (char)254;
            setTextColor(PRETO);
            std::cout << (char)178;
            setTextColor(AZUL_CLARO);
            std::cout << (char)254;
            setTextColor(PRETO);
            std::cout << (char)179;
            gotoxy(x, y + 2);
            std::cout << (char)179 << (char)178;
            setTextColor(AZUL_CLARO);
            std::cout << (char)254;
            setTextColor(PRETO);
            std::cout << (char)178 << (char)179;
            gotoxy(x, y + 3);
            std::cout << (char)179;
            setTextColor(AZUL_CLARO);
            std::cout << (char)254;
            setTextColor(PRETO);
            std::cout << (char)178;
            setTextColor(AZUL_CLARO);
            std::cout << (char)254;
            setTextColor(PRETO);
            std::cout << (char)179;
            gotoxy(x, y + 4);
            std::cout << (char)192 << (char)196 << (char)196 << (char)196 << (char)217;

        }
    else if (id == "TcA")
        {
            gotoxy(x, y);

            std::cout << (char)218 << (char)196 << (char)196 << (char)196 << (char)191;
            gotoxy(x, y + 1);
            std::cout << (char)179;
            setTextColor(CINZENTO);
            std::cout << (char)247;
            setTextColor(PRETO);
            std::cout << (char)177;
            setTextColor(CINZENTO);
            std::cout << (char)247;
            setTextColor(PRETO);
            std::cout << (char)179;
            gotoxy(x, y + 2);
            std::cout << (char)179 << (char)177;
            setTextColor(CINZENTO);
            std::cout << (char)247;
            setTextColor(PRETO);
            std::cout << (char)177 << (char)179;
            gotoxy(x, y + 3);
            std::cout << (char)179;
            setTextColor(CINZENTO);
            std::cout << (char)247;
            setTextColor(PRETO);
            std::cout << (char)177;
            setTextColor(CINZENTO);
            std::cout << (char)247;
            setTextColor(PRETO);
            std::cout << (char)179;
            gotoxy(x, y + 4);
            std::cout << (char)192 << (char)196 << (char)196 << (char)196 << (char)217;

        }
    else if (id == "TcC")
        {
            gotoxy(x, y);

            std::cout << (char)218 << (char)196 << (char)196 << (char)196 << (char)191;
            gotoxy(x, y + 1);
            std::cout << (char)179;
            setTextColor(PRETO);
            std::cout << (char)254;
            setTextColor(PRETO);
            std::cout << (char)176;
            setTextColor(PRETO);
            std::cout << (char)254;
            setTextColor(PRETO);
            std::cout << (char)179;
            gotoxy(x, y + 2);
            std::cout << (char)179 << (char)176;
            setTextColor(PRETO);
            std::cout << (char)254;
            setTextColor(PRETO);
            std::cout << (char)176 << (char)179;
            gotoxy(x, y + 3);
            std::cout << (char)179;
            setTextColor(PRETO);
            std::cout << (char)254;
            setTextColor(PRETO);
            std::cout << (char)176;
            setTextColor(PRETO);
            std::cout << (char)254;
            setTextColor(PRETO);
            std::cout << (char)179;
            gotoxy(x, y + 4);
            std::cout << (char)192 << (char)196 << (char)196 << (char)196 << (char)217;

        }
    else if (id == "TcO")
        {
            gotoxy(x, y);

            std::cout << (char)218 << (char)196 << (char)196 << (char)196 << (char)191;
            gotoxy(x, y + 1);
            std::cout << (char)179;
            setTextColor(AMARELO_CLARO);
            std::cout << (char)42;
            setTextColor(PRETO);
            std::cout << (char)176;
            setTextColor(AMARELO_CLARO);
            std::cout << (char)42;
            setTextColor(PRETO);
            std::cout << (char)179;
            gotoxy(x, y + 2);
            std::cout << (char)179 << (char)176;
            setTextColor(AMARELO_CLARO);
            std::cout << (char)42;
            setTextColor(PRETO);
            std::cout << (char)176 << (char)179;
            gotoxy(x, y + 3);
            std::cout << (char)179;
            setTextColor(AMARELO_CLARO);
            std::cout << (char)42;
            setTextColor(PRETO);
            std::cout << (char)176;
            setTextColor(AMARELO_CLARO);
            std::cout << (char)42;
            setTextColor(PRETO);
            std::cout << (char)179;
            gotoxy(x, y + 4);
            std::cout << (char)192 << (char)196 << (char)196 << (char)196 << (char)217;
        }
    else if (id == "V")
        {
            gotoxy(x, y);
            std::cout << (char)255 << (char)203 << (char)255 << (char)203 << (char)255;
            gotoxy(x, y + 1);
            std::cout << (char)255 << (char)179 << (char)255 << (char)179 << (char)255;
            gotoxy(x, y + 2);
            std::cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)255;
            gotoxy(x, y + 3);
            std::cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)255;
            gotoxy(x, y + 4);
            std::cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)255;
        }
    else if (id == "TcF")
        {
            gotoxy(x, y);

            std::cout << (char)218 << (char)196 << (char)196 << (char)196 << (char)191;
            gotoxy(x, y + 1);
            std::cout << (char)179;
            setTextColor(VERDE);
            std::cout << (char)236;
            setTextColor(PRETO);
            std::cout << (char)178;
            setTextColor(VERDE);
            std::cout << (char)236;
            setTextColor(PRETO);
            std::cout << (char)179;
            gotoxy(x, y + 2);
            std::cout << (char)179 << (char)178;
            setTextColor(VERDE);
            std::cout << (char)236;
            setTextColor(PRETO);
            std::cout << (char)178 << (char)179;
            gotoxy(x, y + 3);
            std::cout << (char)179;
            setTextColor(VERDE);
            std::cout << (char)236;
            setTextColor(PRETO);
            std::cout << (char)178;
            setTextColor(VERDE);
            std::cout << (char)236;
            setTextColor(PRETO);
            std::cout << (char)179;
            gotoxy(x, y + 4);
            std::cout << (char)192 << (char)196 << (char)196 << (char)196 << (char)217;

        }
    else if (id == "E")
        {
            gotoxy(x, y);
            std::cout << (char)195 << (char)45 << (char)45 << (char)45 << (char)180;
            gotoxy(x, y + 1);
            std::cout << (char)195 << (char)45 << (char)45 << (char)45 << (char)180;
            gotoxy(x, y + 2);
            std::cout << (char)195 << (char)45 << (char)45 << (char)45 << (char)180;
            gotoxy(x, y + 3);
            std::cout << (char)195 << (char)45 << (char)45 << (char)45 << (char)180;
            gotoxy(x, y + 4);
            std::cout << (char)195 << (char)45 << (char)45 << (char)45 << (char)180;

        }
    else if (id == "NULL")
        {
            gotoxy(x, y);
            std::cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)255;
            gotoxy(x, y + 1);
            std::cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)255;
            gotoxy(x, y + 2);
            std::cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)255;
            gotoxy(x, y + 3);
            std::cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)255;
            gotoxy(x, y + 4);
            std::cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)255;
        }
}