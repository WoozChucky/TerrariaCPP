#include "TerrenoDuro.h"


TerrenoDuro::TerrenoDuro(int X, int Y)
{
    _breakeable = 1;
    _ticks = 2;
    _x = X;
    _y = Y;
}


TerrenoDuro::~TerrenoDuro()
{
}

std::array<std::array<int, 5>, 5> TerrenoDuro::getDrawSequence() const
{
    return
    {
        {
            { { 218, 196, 196, 196, 191 } },
            { { 179, 178, 178, 178, 179 } },
            { { 179, 178, 178, 178, 179 } },
            { { 179, 178, 178, 178, 179 } },
            { { 192, 196, 196, 196, 217 } }
        }
    };
}

