#include "Dynamite.h"


Dynamite::Dynamite(int X, int Y)
{
    _x = X;
    _y = Y;
    _breakeable = 1;
}


Dynamite::~Dynamite()
{
}

std::array<std::array<int, 5>, 5> Dynamite::getDrawSequence() const
{
    return
    {
        {
            { { 218, 196, 196, 196, 191 } },
            { { 179, 218, 196, 191, 179 } },
            { { 179, 179, 178, 179, 179 } },
            { { 179, 192, 196, 217, 179 } },
            { { 192, 196, 196, 196, 217 } }
        }
    };
}
