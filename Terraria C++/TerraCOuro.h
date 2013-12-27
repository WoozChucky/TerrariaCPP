#pragma once
#include "Block.h"
class TerraCOuro :
    public Block
{
public:
    TerraCOuro(int X, int Y);
    virtual ~TerraCOuro();

    std::array<std::array<int, 5>, 5> getDrawSequence() const;
};

