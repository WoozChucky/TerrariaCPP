#include "TerraCCarvao.h"


TerraCCarvao::TerraCCarvao(int X, int Y)
{
    _breakeable = 1;
    _ticks = 3;
    _x = X;
    _y = Y;
}


TerraCCarvao::~TerraCCarvao()
{
}

std::array<std::array<int, 5>, 5> TerraCCarvao::getDrawSequence() const
{
    return
    {
        {
            { { 218, 196, 196, 196, 191 } },
            { { 179, 254, 176, 254, 179 } },
            { { 179, 176, 254, 176, 179 } },
            { { 179, 254, 176, 254, 179 } },
            { { 192, 196, 196, 196, 217 } }
        }
    };
}