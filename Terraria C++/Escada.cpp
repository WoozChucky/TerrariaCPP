#include "Escada.h"


Escada::Escada(int X, int Y)
{
    _breakeable = 1;
    _x = X;
    _y = Y;
}

std::array<std::array<int, 5>, 5> Escada::getDrawSequence() const
{
	std::array<std::array<int, 5>, 5> _escada = {
		195, 45, 45, 45, 180,
		195, 45, 45, 45, 180,
		195, 45, 45, 45, 180,
		195, 45, 45, 45, 180,
		195, 45, 45, 45, 180};

	return _escada;
}
/* Gets */
int Escada::getX() const
{
    return _x;
}
int Escada::getY() const
{
    return _y;
}
int Escada::getTicks() const
{
    return _ticks;
}
int Escada::getBreakeable() const
{
    return _breakeable;
}

/* Sets */
void Escada::setX(int S)
{
    _x = S;
}
void Escada::setY(int S)
{
    _y = S;
}
void Escada::setTicks(int S)
{
    _ticks = S;
}
void Escada::setBreakeable(int S)
{
    _breakeable = S;
}
