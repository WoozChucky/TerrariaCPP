#include "Block.h"

/* Gets */
int Block::getX()
{
    return _x;
}
int Block::getY()
{
    return _y;
}
std::string Block::getID()
{
    return _id;
}
int Block::getTicks()
{
    return _ticks;
}
int Block::getBreakeable()
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
    else if (id == "TD")
        {

        }
    else if (id == "TcA")
        {

        }
    else if (id == "TcC")
        {

        }
    else if (id == "TcO")
        {
            gotoxy(x, y);
            std::cout << (char)218 << (char)196 << (char)196 << (char)196 << (char)191;
            gotoxy(x, y + 1);
            std::cout << (char)179 << (char)42 << (char)176 << (char)42 << (char)179;
            gotoxy(x, y + 2);
            std::cout << (char)179 << (char)176 << (char)42 << (char)176 << (char)179;
            gotoxy(x, y + 3);
            std::cout << (char)179 << (char)42 << (char)176 << (char)42 << (char)179;
            gotoxy(x, y + 4);
            std::cout << (char)192 << (char)196 << (char)196 << (char)196 << (char)217;
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