#pragma once
#include "Block.h"
class TerrenoMole :
    public Block
{
public:
    TerrenoMole(int X, int Y);
    virtual ~TerrenoMole();

    std::array<std::array<int, 5>, 5> getDrawSequence() const;
};

