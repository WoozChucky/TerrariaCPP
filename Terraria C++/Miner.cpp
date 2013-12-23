#include "Miner.h"

/* General */
Miner::Miner(int lives, int energy, int coins)
{
    _life = lives;
    _energy = energy;
    _coins = coins;
}
void Miner::ResetStats()
{
    _energy = 100;
    _coins = 0;
    _life = 3;
}

/* Verifications */
bool Miner::hasLifes()
{
    if (_life <= 0)
        return false;
    return true;
}
void Miner::isAlive()
{
    if (_energy <= 0)
        {
            clrscr();
            gotoxy(1, 6);
            std::cout << "Perdeste toda a energia e 1 vida. Prima qualquer tecla para recomecar.";
            _life -= 1;
            _energy = 100;
            getch();
        }
}

/* Movement */
void Miner::Move(int X, int Y)
{
    setCoordinates(X, Y);
    _energy--;
    isAlive();
}
void Miner::setCoordinates(int X, int Y)
{
    _x = X;
    _y = Y;
}

/* Gets*/
int Miner::getEnergy() const
{
    return _energy;
}
int Miner::getCoins() const
{
    return _coins;
}
int Miner::getLife() const
{
    return _life;
}
int Miner::getX() const
{
    return _x;
}
int Miner::getY() const
{
    return _y;
}

/* Sets */
void Miner::setLife(int S)
{
    _life = S;
}
void Miner::setEnergy(int S)
{
    _energy = S;
}
void Miner::setCoins(int S)
{
    _coins = S;
}