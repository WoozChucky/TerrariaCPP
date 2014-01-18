#include "TerraCAluminio.h"


TerraCAluminio::TerraCAluminio(int X, int Y)
{
    _breakeable = 1;
    _ticks = 2;
    _x = X;
    _y = Y;
}

std::array<std::array<int, 5>, 5> TerraCAluminio::getDrawSequence() const
{
    std::array<std::array<int, 5>, 5> _terraCAluminio = {
        218, 196, 196, 196, 191,
		179, 247, 177, 247, 179,
        179, 177, 247, 177, 179,
        179, 247, 177, 247, 179,
        192, 196, 196, 196, 217};

	return _terraCAluminio;
}

/* Gets */
int TerraCAluminio::getX() const
{
    return _x;
}
int TerraCAluminio::getY() const
{
    return _y;
}
int TerraCAluminio::getTicks() const
{
    return _ticks;
}
int TerraCAluminio::getBreakeable() const
{
    return _breakeable;
}

/* Sets */
void TerraCAluminio::setX(int S)
{
    _x = S;
}
void TerraCAluminio::setY(int S)
{
    _y = S;
}
void TerraCAluminio::setTicks(int S)
{
    _ticks = S;
}
void TerraCAluminio::setBreakeable(int S)
{
    _breakeable = S;
}