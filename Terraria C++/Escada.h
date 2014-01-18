#pragma once
#include "Block.h"
class Escada :
    public Block
{
public:
    Escada(int X, int Y);

    /* Gets */
    int getX() const;
    int getY() const;
    int getTicks() const;
    int getBreakeable() const;
    std::array<std::array<int, 5>, 5> getDrawSequence() const;

    /* Sets */
    void setX(int S);
    void setY(int S);
    void setTicks(int S);
    void setBreakeable(int S);
};

