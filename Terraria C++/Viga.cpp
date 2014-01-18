#include "Viga.h"


Viga::Viga(int X, int Y)
{
    _breakeable = 1;
    _x = X;
    _y = Y;
}

std::array<std::array<int, 5>, 5> Viga::getDrawSequence() const
{
    std::array<std::array<int, 5>, 5> _viga = {
        203, 255, 255, 255, 203,
        179, 255, 255, 255, 179,
        255, 255, 255, 255, 255,
        255, 255, 255, 255, 255,
		255, 255, 255, 255, 255};

	return _viga;
}

/* Gets */
int Viga::getX() const
{
    return _x;
}
int Viga::getY() const
{
    return _y;
}
int Viga::getTicks() const
{
    return _ticks;
}
int Viga::getBreakeable() const
{
    return _breakeable;
}

/* Sets */
void Viga::setX(int S)
{
    _x = S;
}
void Viga::setY(int S)
{
    _y = S;
}
void Viga::setTicks(int S)
{
    _ticks = S;
}
void Viga::setBreakeable(int S)
{
    _breakeable = S;
}