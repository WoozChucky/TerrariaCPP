#include "Vazio.h"


Vazio::Vazio(int X, int Y)
{
    _x = X;
    _y = Y;
    _breakeable = 1;
    _ticks = 0;
}

std::array<std::array<int, 5>, 5> Vazio::getDrawSequence() const
{
    std::array<std::array<int, 5>, 5> _vazio = {
        255, 255, 255, 255, 255,
        255, 255, 255, 255, 255,
        255, 255, 255, 255, 255,
        255, 255, 255, 255, 255,
        255, 255, 255, 255, 255};

	return _vazio;
}

/* Gets */
int Vazio::getX() const
{
    return _x;
}
int Vazio::getY() const
{
    return _y;
}
int Vazio::getTicks() const
{
    return _ticks;
}
int Vazio::getBreakeable() const
{
    return _breakeable;
}

/* Sets */
void Vazio::setX(int S)
{
    _x = S;
}
void Vazio::setY(int S)
{
    _y = S;
}
void Vazio::setTicks(int S)
{
    _ticks = S;
}
void Vazio::setBreakeable(int S)
{
    _breakeable = S;
}