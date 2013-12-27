#pragma once
#include "Block.h"
class TerrenoDuro :
    public Block
{
public:
    TerrenoDuro(int X, int Y);
    virtual ~TerrenoDuro();

    std::array<std::array<int, 5>, 5> getDrawSequence() const;
};

