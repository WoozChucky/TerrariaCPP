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
    Remove();
    setCoordinates(X, Y);
    _energy--;
    isAlive();
}
void Miner::setCoordinates(int X, int Y)
{
    _x = X;
    _y = Y;
}

/* Draws */
void Miner::Show()
{
    setTextColor(PRETO);
    gotoxy(_x * 5, _y * 5);
    std::cout << (char)255 << (char)255 << (char)2 << (char)255 << (char)255;

    setTextColor(VERMELHO_CLARO);
    gotoxy(_x * 5, _y * 5 + 1);
    std::cout << (char)255 << (char)205 << (char)203 << (char)205 << (char)255;

    gotoxy(_x * 5, _y * 5 + 2);
    std::cout << (char)255 << (char)255 << (char)186 << (char)255 << (char)255;

    setTextColor(AZUL);
    gotoxy(_x * 5, _y * 5 + 3);
    std::cout << (char)255 << (char)255 << (char)202 << (char)255 << (char)255;

    gotoxy(_x * 5, _y * 5 + 4);
    std::cout << (char)255 << (char)188 << (char)255 << (char)200 << (char)255;
}
void Miner::Remove()
{
    gotoxy(_x * 5, _y * 5);
    std::cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)255;

    gotoxy(_x * 5, _y * 5 + 1);
    std::cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)255;

    gotoxy(_x * 5, _y * 5 + 2);
    std::cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)255;

    gotoxy(_x * 5, _y * 5 + 3);
    std::cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)255;

    gotoxy(_x * 5, _y * 5 + 4);
    std::cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)255;
}
void Miner::DeleteStats()
{
    gotoxy(2, 1);
    std::cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255;
    gotoxy(2, 2);
    std::cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255;
    gotoxy(2, 3);
    std::cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255;
    gotoxy(2, 4);
    std::cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255;
    gotoxy(0, 6);
    std::cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255;
}
void Miner::showStats()
{
    setTextColor(PRETO);
    gotoxy(1, 35);
    std::cout << "X: " << _x << " Y: " << _y << (char)255;

    gotoxy(1, 36);
    std::cout << "Lives: ";
    setTextColor(VERMELHO_CLARO);
    switch (_life)
        {
        case 3:
            std::cout << (char)3 << (char)3 << (char)3;
            break;
        case 2:
            std::cout << (char)3 << (char)3;
            break;
        case 1:
            std::cout << (char)3;
            break;
        }

    setTextColor(PRETO);
    gotoxy(1, 37);
    std::cout << "Energy: ";
    setTextColor(VERMELHO_CLARO);
    if (_energy == 100)
        {
            std::cout << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219;
        }
    else if (_energy >= 90)
        {
            std::cout << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)255;
        }
    else if (_energy >= 80)
        {
            std::cout << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)255 << (char)255;
        }
    else if (_energy >= 70)
        {
            std::cout << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)255 << (char)255 << (char)255;
        }
    else if (_energy >= 60)
        {
            std::cout << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)255 << (char)255 << (char)255 << (char)255;
        }
    else if (_energy >= 50)
        {
            std::cout << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255;
        }
    else if (_energy >= 40)
        {
            std::cout << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255;
        }
    else if (_energy >= 30)
        {
            std::cout << (char)219 << (char)219 << (char)219 << (char)219 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255;
        }
    else if (_energy >= 20)
        {
            std::cout << (char)219 << (char)219 << (char)219 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255;
        }
    else if (_energy >= 10)
        {
            std::cout << (char)219 << (char)219 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255;
        }
    std::cout << " " << _energy << "/100" << (char)255;

    setTextColor(PRETO);
    gotoxy(1, 38);
    std::cout << "Coins: ";
    setTextColor(AMARELO_CLARO);
    std::cout << _coins;
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