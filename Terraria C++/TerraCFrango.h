#pragma once
#include "Block.h"
class TerraCFrango :
    public Block
{
public:
    TerraCFrango(int X, int Y);
    virtual ~TerraCFrango();

    std::array<std::array<int, 5>, 5> getDrawSequence() const;
};

