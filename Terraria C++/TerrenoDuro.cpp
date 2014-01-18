#include "TerrenoDuro.h"


TerrenoDuro::TerrenoDuro(int X, int Y)
{
    _breakeable = 1;
    _ticks = 2;
    _x = X;
    _y = Y;
}

std::array<std::array<int, 5>, 5> TerrenoDuro::getDrawSequence() const
{
    std::array<std::array<int, 5>, 5> _terrenoDuro = {
        218, 196, 196, 196, 191,
        179, 178, 178, 178, 179,
        179, 178, 178, 178, 179,
        179, 178, 178, 178, 179,
		192, 196, 196, 196, 217};

	return _terrenoDuro;
}

/* Gets */
int TerrenoDuro::getX() const
{
    return _x;
}
int TerrenoDuro::getY() const
{
    return _y;
}
int TerrenoDuro::getTicks() const
{
    return _ticks;
}
int TerrenoDuro::getBreakeable() const
{
    return _breakeable;
}

/* Sets */
void TerrenoDuro::setX(int S)
{
    _x = S;
}
void TerrenoDuro::setY(int S)
{
    _y = S;
}
void TerrenoDuro::setTicks(int S)
{
    _ticks = S;
}
void TerrenoDuro::setBreakeable(int S)
{
    _breakeable = S;
}