#include "TerraCDiamante.h"


TerraCDiamante::TerraCDiamante(int X, int Y)
{
    _breakeable = 1;
    _ticks = 5;
    _x = X;
    _y = Y;
}


TerraCDiamante::~TerraCDiamante()
{
}

std::array<std::array<int, 5>, 5> TerraCDiamante::getDrawSequence() const
{
    return
    {
        {
            { { 218, 196, 196, 196, 191 } },
            { { 179, 254, 178, 254, 179 } },
            { { 179, 178, 254, 178, 179 } },
            { { 179, 254, 178, 254, 179 } },
            { { 192, 196, 196, 196, 217 } }
        }
    };
}