#pragma once
#include "Core.h"

class Block
{
protected:
    int _x, _y;
    std::string _id;
    int _ticks;
    int _breakeable;
public:

    /* Constructor */
    Block(int X=0, int Y=0);
    /* Destructor */
    ~Block();

    /* Gets */
    virtual int getX() const;
    virtual int getY() const;
    virtual std::string getID() const;
    virtual int getTicks() const;
    virtual int getBreakeable() const;
    virtual std::array<std::array<int, 5>, 5> getDrawSequence() const;

    /* Sets */
    virtual void setX(int S);
    virtual void setY(int S);
    virtual void setID(std::string S);
    virtual void setTicks(int S);
    virtual void setBreakeable(int S);

};