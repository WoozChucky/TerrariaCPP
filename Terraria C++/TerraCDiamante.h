#pragma once
#include "Block.h"
class TerraCDiamante :
    public Block
{
public:
    TerraCDiamante(int X, int Y);
    virtual ~TerraCDiamante();

    std::array<std::array<int, 5>, 5> getDrawSequence() const;
};

