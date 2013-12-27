#include "TerraCFerro.h"


TerraCFerro::TerraCFerro(int X, int Y)
{
    _breakeable = 1;
    _ticks = 4;
    _x = X;
    _y = Y;
}


TerraCFerro::~TerraCFerro()
{
}

std::array<std::array<int, 5>, 5> TerraCFerro::getDrawSequence() const
{
    return
    {
        {
            { { 218, 196, 196, 196, 191 } },
            { { 179, 236, 178, 236, 179 } },
            { { 179, 178, 236, 178, 179 } },
            { { 179, 236, 178, 236, 179 } },
            { { 192, 196, 196, 196, 217 } }
        }
    };
}