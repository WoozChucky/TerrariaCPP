#include "TerraCFrango.h"


TerraCFrango::TerraCFrango(int X, int Y)
{
    _breakeable = 1;
    _ticks = 2;
    _x = X;
    _y = Y;
}

std::array<std::array<int, 5>, 5> TerraCFrango::getDrawSequence() const
{
    std::array<std::array<int, 5>, 5> _terraCFrango = {
        218, 196, 196, 196, 191,
        179, 218, 196, 191, 179,
        179, 179, 153, 179, 179,
        179, 192, 196, 217, 179,
        192, 196, 196, 196, 217};

	return _terraCFrango;
}

/* Gets */
int TerraCFrango::getX() const
{
    return _x;
}
int TerraCFrango::getY() const
{
    return _y;
}
int TerraCFrango::getTicks() const
{
    return _ticks;
}
int TerraCFrango::getBreakeable() const
{
    return _breakeable;
}

/* Sets */
void TerraCFrango::setX(int S)
{
    _x = S;
}
void TerraCFrango::setY(int S)
{
    _y = S;
}
void TerraCFrango::setTicks(int S)
{
    _ticks = S;
}
void TerraCFrango::setBreakeable(int S)
{
    _breakeable = S;
}