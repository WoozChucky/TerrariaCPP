#pragma once
#include "Block.h"
class TerraCFerro :
    public Block
{
public:
    TerraCFerro(int X, int Y);
    virtual ~TerraCFerro();

    std::array<std::array<int, 5>, 5> getDrawSequence() const;
};