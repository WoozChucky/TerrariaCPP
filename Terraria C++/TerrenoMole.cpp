#include "TerrenoMole.h"


TerrenoMole::TerrenoMole(int X, int Y)
{
    _breakeable = 1;
    _ticks = 1;
    _x = X;
    _y = Y;
}


TerrenoMole::~TerrenoMole()
{
}

std::array<std::array<int, 5>, 5> TerrenoMole::getDrawSequence() const
{
    return
    {
        {
            { { 218, 196, 196, 196, 191 } },
            { { 179, 176, 176, 176, 179 } },
            { { 179, 176, 176, 176, 179 } },
            { { 179, 176, 176, 176, 179 } },
            { { 192, 196, 196, 196, 217 } }
        }
    };
}
