#pragma once
#include "Block.h"
class Vazio :
    public Block
{
public:
    Vazio(int X, int Y);
    virtual ~Vazio();

    std::array<std::array<int, 5>, 5> getDrawSequence() const;
};

