#include "Block.h"

/* Constructor */
Block::Block(int X, int Y)
{
    _breakeable = 1;
    _x = X;
    _y = Y;
}
/* Destructor */
Block::~Block()
{

}

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
std::array<std::array<int, 5>, 5> Block::getDrawSequence() const
{
    return
    {
        {
            { { 255, 255, 255, 255, 255 } },
            { { 255, 255, 255, 255, 255 } },
            { { 255, 255, 255, 255, 255 } },
            { { 255, 255, 255, 255, 255 } },
            { { 255, 255, 255, 255, 255 } }
        }
    };
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
