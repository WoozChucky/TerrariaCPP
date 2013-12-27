#include "TerraCOuro.h"


TerraCOuro::TerraCOuro(int X, int Y)
{
    _breakeable = 1;
    _ticks = 4;
    _x = X;
    _y = Y;
}


TerraCOuro::~TerraCOuro()
{
}

std::array<std::array<int, 5>, 5> TerraCOuro::getDrawSequence() const
{
    return
    {
        {
            { { 218, 196, 196, 196, 191 } },
            { { 179, 42, 176, 42, 179 } },
            { { 179, 176, 42, 176, 179 } },
            { { 179, 42, 176, 42, 179 } },
            { { 192, 196, 196, 196, 217 } }
        }
    };
}
