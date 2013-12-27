#pragma once
#include "Block.h"
class Dynamite :
    public Block
{
public:
    Dynamite(int X, int Y);
    virtual ~Dynamite();

    std::array<std::array<int, 5>, 5> getDrawSequence() const;
};

