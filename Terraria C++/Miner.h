#ifndef __MINER_H__
#define __MINER_H__

#include "Consola.h"

class Miner : public Consola
{
    int _life;
    int _energy;
    int _coins;
    int _x, _y; //current coordinates
public:
    /* General */
    Miner(int life = START_LIVES, int energy = START_ENERGY, int coins = START_GOLD);
    void ResetStats();

    /* Verifications */
    bool hasLifes();
    void isAlive();

    /* Movement */
    void Move(int X, int Y);
    void setCoordinates(int X, int Y);

    /* Draws */
    void Show();
    void Remove();
    void showStats();
    void DeleteStats();

    /* Sets */
    void setLife(int S);
    void setEnergy(int S);
    void setCoins(int S);

    /* Gets */
    int getEnergy() const;
    int getCoins() const;
    int getLife() const;
    int getX() const;
    int getY() const;

};

#endif