#include "Pedra.h"


Pedra::Pedra(int X, int Y)
{
    _breakeable = 0;
    _x = X;
    _y = Y;
}


Pedra::~Pedra()
{
}

std::array<std::array<int, 5>, 5> Pedra::getDrawSequence() const
{
    return
    {
        {
            { { 218, 196, 196, 196, 191 } },
            { { 179, 219, 219, 219, 179 } },
            { { 179, 219, 219, 219, 179 } },
            { { 179, 219, 219, 219, 179 } },
            { { 192, 196, 196, 196, 217 } }
        }
    };
}