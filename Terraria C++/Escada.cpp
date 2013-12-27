#include "Escada.h"


Escada::Escada(int X, int Y)
{
    _breakeable = 1;
    _x = X;
    _y = Y;
}

Escada::~Escada()
{
}

std::array<std::array<int, 5>, 5> Escada::getDrawSequence() const
{
    return
    {
        {
            { { 195, 45, 45, 45, 180 } },
            { { 195, 45, 45, 45, 180 } },
            { { 195, 45, 45, 45, 180 } },
            { { 195, 45, 45, 45, 180 } },
            { { 195, 45, 45, 45, 180 } }
        }
    };
}
