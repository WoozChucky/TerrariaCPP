#pragma once
#include "Block.h"
class Viga :
    public Block
{
public:
    Viga(int X, int Y);
    virtual ~Viga();

    std::array<std::array<int, 5>, 5> getDrawSequence() const;
};

