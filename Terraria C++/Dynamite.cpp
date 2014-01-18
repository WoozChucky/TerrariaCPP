#include "Dynamite.h"


Dynamite::Dynamite(int X, int Y)
{
    _x = X;
    _y = Y;
    _breakeable = 1;
}
/* Gets */
int Dynamite::getX() const
{
    return _x;
}
int Dynamite::getY() const
{
    return _y;
}
int Dynamite::getTicks() const
{
    return _ticks;
}
int Dynamite::getBreakeable() const
{
    return _breakeable;
}
std::array<std::array<int, 5>, 5> Dynamite::getDrawSequence() const
{
    std::array<std::array<int, 5>, 5> _dynamite = {
		218, 196, 196, 196, 191,
		179, 218, 196, 191, 179,
		179, 179, 178, 179, 179,
		179, 192, 196, 217, 179,
		192, 196, 196, 196, 217};

	return _dynamite;
}

/* Sets */
void Dynamite::setX(int S)
{
    _x = S;
}
void Dynamite::setY(int S)
{
    _y = S;
}
void Dynamite::setTicks(int S)
{
    _ticks = S;
}
void Dynamite::setBreakeable(int S)
{
    _breakeable = S;
}