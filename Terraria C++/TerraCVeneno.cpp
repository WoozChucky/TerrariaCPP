#include "TerraCVeneno.h"


TerraCVeneno::TerraCVeneno(int X, int Y)
{
    _x = X;
    _y = Y;
    _breakeable = 1;
    _ticks = 2;
}


TerraCVeneno::~TerraCVeneno()
{
}

std::array<std::array<int, 5>, 5> TerraCVeneno::getDrawSequence() const
{
    return
    {
        {
            { { 218, 196, 196, 196, 191 } },
            { { 179, 247, 177, 247, 179 } },
            { { 179, 177, 247, 177, 179 } },
            { { 179, 247, 177, 247, 179 } },
            { { 192, 196, 196, 196, 217 } }
        }
    };
}
