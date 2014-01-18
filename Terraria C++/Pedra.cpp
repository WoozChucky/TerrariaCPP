#include "Pedra.h"


Pedra::Pedra(int X, int Y)
{
    _breakeable = 0;
    _x = X;
    _y = Y;
}

std::array<std::array<int, 5>, 5> Pedra::getDrawSequence() const
{
    std::array<std::array<int, 5>, 5> _pedra = {
        218, 196, 196, 196, 191,
        179, 219, 219, 219, 179,
        179, 219, 219, 219, 179,
        179, 219, 219, 219, 179,
		192, 196, 196, 196, 217};

	return _pedra;
}

/* Gets */
int Pedra::getX() const
{
    return _x;
}
int Pedra::getY() const
{
    return _y;
}
int Pedra::getTicks() const
{
    return _ticks;
}
int Pedra::getBreakeable() const
{
    return _breakeable;
}

/* Sets */
void Pedra::setX(int S)
{
    _x = S;
}
void Pedra::setY(int S)
{
    _y = S;
}
void Pedra::setTicks(int S)
{
    _ticks = S;
}
void Pedra::setBreakeable(int S)
{
    _breakeable = S;
}