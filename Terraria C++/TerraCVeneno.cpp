#include "TerraCVeneno.h"


TerraCVeneno::TerraCVeneno(int X, int Y)
{
    _x = X;
    _y = Y;
    _breakeable = 1;
    _ticks = 2;
}

std::array<std::array<int, 5>, 5> TerraCVeneno::getDrawSequence() const
{
    std::array<std::array<int, 5>, 5> _terraCVeneno = {
        218, 196, 196, 196, 191,
        179, 247, 177, 247, 179,
        179, 177, 247, 177, 179,
        179, 247, 177, 247, 179,
        192, 196, 196, 196, 217};

	return _terraCVeneno;
}

/* Gets */
int TerraCVeneno::getX() const
{
    return _x;
}
int TerraCVeneno::getY() const
{
    return _y;
}
int TerraCVeneno::getTicks() const
{
    return _ticks;
}
int TerraCVeneno::getBreakeable() const
{
    return _breakeable;
}

/* Sets */
void TerraCVeneno::setX(int S)
{
    _x = S;
}
void TerraCVeneno::setY(int S)
{
    _y = S;
}
void TerraCVeneno::setTicks(int S)
{
    _ticks = S;
}
void TerraCVeneno::setBreakeable(int S)
{
    _breakeable = S;
}