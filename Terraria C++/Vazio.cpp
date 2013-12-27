#include "Vazio.h"


Vazio::Vazio(int X, int Y)
{
    _x = X;
    _y = Y;
    _breakeable = 1;
    _ticks = 0;
}


Vazio::~Vazio()
{
}

std::array<std::array<int, 5>, 5> Vazio::getDrawSequence() const
{
    return
    {
        {
            { { 255, 255, 255, 255, 255 } },
            { { 255, 255, 255, 255, 255 } },
            { { 255, 255, 255, 255, 255 } },
            { { 255, 255, 255, 255, 255 } },
            { { 255, 255, 255, 255, 255 } }
        }
    };
}
