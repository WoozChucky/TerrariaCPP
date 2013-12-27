#pragma once
#include "Block.h"
class TerraCAluminio :
    public Block
{
public:
    TerraCAluminio(int X, int Y);
    virtual ~TerraCAluminio();

    std::array<std::array<int, 5>, 5> getDrawSequence() const;
};

