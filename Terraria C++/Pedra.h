#pragma once
#include "Block.h"
class Pedra :  public Block
{
public:
    Pedra(int X, int Y);
    virtual ~Pedra();

    std::array<std::array<int, 5>, 5> getDrawSequence() const;
};

