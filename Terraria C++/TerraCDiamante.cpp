#include "TerraCDiamante.h"


TerraCDiamante::TerraCDiamante(int X, int Y)
{
    _breakeable = 1;
    _ticks = 5;
    _x = X;
    _y = Y;
}

std::array<std::array<int, 5>, 5> TerraCDiamante::getDrawSequence() const
{
    std::array<std::array<int, 5>, 5> _terraCDiamante = {
		218, 196, 196, 196, 191,
        179, 254, 178, 254, 179,
        179, 178, 254, 178, 179,
        179, 254, 178, 254, 179,
		192, 196, 196, 196, 217};

	return _terraCDiamante;
}

/* Gets */
int TerraCDiamante::getX() const
{
    return _x;
}
int TerraCDiamante::getY() const
{
    return _y;
}
int TerraCDiamante::getTicks() const
{
    return _ticks;
}
int TerraCDiamante::getBreakeable() const
{
    return _breakeable;
}

/* Sets */
void TerraCDiamante::setX(int S)
{
    _x = S;
}
void TerraCDiamante::setY(int S)
{
    _y = S;
}
void TerraCDiamante::setTicks(int S)
{
    _ticks = S;
}
void TerraCDiamante::setBreakeable(int S)
{
    _breakeable = S;
}