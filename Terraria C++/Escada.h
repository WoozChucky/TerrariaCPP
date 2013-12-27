#pragma once
#include "Block.h"
class Escada :
    public Block
{
public:
    Escada(int X, int Y);
    virtual ~Escada();

    std::array<std::array<int, 5>, 5> getDrawSequence() const;
};

