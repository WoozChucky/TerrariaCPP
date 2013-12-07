#include "Miner.h"

class Block : public Miner
{
    int _x, _y;
    std::string _id;
    int _ticks;
    int _breakeable;

public:
    /* Gets */
    int getX() const;
    int getY() const;
    std::string getID() const;
    int getTicks() const;
    int getBreakeable() const;

    /* Sets */
    void setX(int S);
    void setY(int S);
    void setID(std::string S);
    void setTicks(int S);
    void setBreakeable(int S);

    /* Draws */
    void DrawBlock(std::string id, int x, int y);
};