#pragma once
#include "Core.h"

class Block
{
protected:
    int _x, _y;
    int _ticks;
    int _breakeable;
public:

    /* Gets */
    virtual int getX() const = 0;
    virtual int getY() const = 0;
    virtual int getTicks() const = 0;
    virtual int getBreakeable() const = 0;
    virtual std::array<std::array<int, 5>, 5> getDrawSequence() const = 0;

    /* Sets */
    virtual void setX(int S) = 0;
    virtual void setY(int S) = 0;
    virtual void setTicks(int S) = 0;
    virtual void setBreakeable(int S) = 0;

};