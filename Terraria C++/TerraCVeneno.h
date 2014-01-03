#pragma once
#include "Block.h"
class TerraCVeneno :
    public Block
{
public:
    TerraCVeneno(int X, int Y);
    ~TerraCVeneno();

    std::array<std::array<int, 5>, 5> getDrawSequence() const;
};

