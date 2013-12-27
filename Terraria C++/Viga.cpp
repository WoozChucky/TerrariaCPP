#include "Viga.h"


Viga::Viga(int X, int Y)
{
    _breakeable = 1;
    _x = X;
    _y = Y;
}


Viga::~Viga()
{
}

std::array<std::array<int, 5>, 5> Viga::getDrawSequence() const
{
    return
    {
        {
            { { 255, 203, 255, 203, 255 } },
            { { 255, 179, 255, 179, 255 } },
            { { 255, 255, 255, 255, 255 } },
            { { 255, 255, 255, 255, 255 } },
            { { 255, 255, 255, 255, 255 } }
        }
    };
}
