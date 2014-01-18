#include "TerraCOuro.h"


TerraCOuro::TerraCOuro(int X, int Y)
{
    _breakeable = 1;
    _ticks = 4;
    _x = X;
    _y = Y;
}


std::array<std::array<int, 5>, 5> TerraCOuro::getDrawSequence() const
{
    std::array<std::array<int, 5>, 5> _terraCOuro = {
        218, 196, 196, 196, 191,
        179, 42, 176, 42, 179,
        179, 176, 42, 176, 179,
        179, 42, 176, 42, 179,
		192, 196, 196, 196, 217};

	return _terraCOuro;
}

/* Gets */
int TerraCOuro::getX() const
{
    return _x;
}
int TerraCOuro::getY() const
{
    return _y;
}
int TerraCOuro::getTicks() const
{
    return _ticks;
}
int TerraCOuro::getBreakeable() const
{
    return _breakeable;
}

/* Sets */
void TerraCOuro::setX(int S)
{
    _x = S;
}
void TerraCOuro::setY(int S)
{
    _y = S;
}
void TerraCOuro::setTicks(int S)
{
    _ticks = S;
}
void TerraCOuro::setBreakeable(int S)
{
    _breakeable = S;
}