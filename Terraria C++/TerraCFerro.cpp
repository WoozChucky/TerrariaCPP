#include "TerraCFerro.h"


TerraCFerro::TerraCFerro(int X, int Y)
{
    _breakeable = 1;
    _ticks = 4;
    _x = X;
    _y = Y;
}

std::array<std::array<int, 5>, 5> TerraCFerro::getDrawSequence() const
{
    std::array<std::array<int, 5>, 5> _terraCFerro = {
        218, 196, 196, 196, 191,
        179, 236, 178, 236, 179,
		179, 178, 236, 178, 179,
		179, 236, 178, 236, 179,
		192, 196, 196, 196, 217};

	return _terraCFerro;
}

/* Gets */
int TerraCFerro::getX() const
{
    return _x;
}
int TerraCFerro::getY() const
{
    return _y;
}
int TerraCFerro::getTicks() const
{
    return _ticks;
}
int TerraCFerro::getBreakeable() const
{
    return _breakeable;
}

/* Sets */
void TerraCFerro::setX(int S)
{
    _x = S;
}
void TerraCFerro::setY(int S)
{
    _y = S;
}
void TerraCFerro::setTicks(int S)
{
    _ticks = S;
}
void TerraCFerro::setBreakeable(int S)
{
    _breakeable = S;
}