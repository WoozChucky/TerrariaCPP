#pragma once
#include "Block.h"
class TerraCCarvao :
    public Block
{
public:
    TerraCCarvao(int X, int Y);
    virtual ~TerraCCarvao();

    std::array<std::array<int, 5>, 5> getDrawSequence() const;
};

