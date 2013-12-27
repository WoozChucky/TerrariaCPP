#include "TerraCFrango.h"


TerraCFrango::TerraCFrango(int X, int Y)
{
    _breakeable = 1;
    _ticks = 2;
    _x = X;
    _y = Y;
}

//Quando escavado adiciona 20 pontos de energia ao mineiro

TerraCFrango::~TerraCFrango()
{
}

std::array<std::array<int, 5>, 5> TerraCFrango::getDrawSequence() const
{
    return
    {
        {
            { { 218, 196, 196, 196, 191 } },
            { { 179, 218, 196, 191, 179 } },
            { { 179, 179, 153, 179, 179 } },
            { { 179, 192, 196, 217, 179 } },
            { { 192, 196, 196, 196, 217 } }
        }
    };
}
