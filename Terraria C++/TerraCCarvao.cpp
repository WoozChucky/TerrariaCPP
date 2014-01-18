#include "TerraCCarvao.h"


TerraCCarvao::TerraCCarvao(int X, int Y)
{
    _breakeable = 1;
    _ticks = 3;
    _x = X;
    _y = Y;
}

std::array<std::array<int, 5>, 5> TerraCCarvao::getDrawSequence() const
{
    std::array<std::array<int, 5>, 5> _terraCCarvao = {
        218, 196, 196, 196, 191,
		179, 254, 176, 254, 179,
		179, 176, 254, 176, 179,
        179, 254, 176, 254, 179,
		192, 196, 196, 196, 217};

	return _terraCCarvao;
}

/* Gets */
int TerraCCarvao::getX() const
{
    return _x;
}
int TerraCCarvao::getY() const
{
    return _y;
}
int TerraCCarvao::getTicks() const
{
    return _ticks;
}
int TerraCCarvao::getBreakeable() const
{
    return _breakeable;
}

/* Sets */
void TerraCCarvao::setX(int S)
{
    _x = S;
}
void TerraCCarvao::setY(int S)
{
    _y = S;
}
void TerraCCarvao::setTicks(int S)
{
    _ticks = S;
}
void TerraCCarvao::setBreakeable(int S)
{
    _breakeable = S;
}