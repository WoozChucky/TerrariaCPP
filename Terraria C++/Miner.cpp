#include <iostream>
#include "Miner.h"



Miner::Miner(int Life, int Energy, int Coins)
{
    this->energy = Energy;
    this->coins = Coins;
    this->life = Life;
    this->escadas = false;
    this->picareta = false;
    this->lanterna = false;
}

void Miner::ResetStats()
{
    energy = 100;
    coins = 0;
    life = 3;
}

bool Miner::hasLifes()
{
    if (this->life <= 0)
        return false;
    return true;
}

void Miner::isAlive(Consola Console)
{
    if (this->energy <= 0)
        {
            Console.clrscr();
            Console.gotoxy(4, 18);
            std::cout << "Perdeste toda a energia e 1 vida. Prima qualquer tecla para continuar.";
            this->setLife(this->getLife()-1);
            this->setEnergy(100);
        }
}

void Miner::setPosition(int X, int Y)
{
    this->x = X;
    this->y = Y;
}

void Miner::Show(Consola Console, int X, int Y)
{
    Console.gotoxy(X, Y);
    std::cout << (char)255 << (char)255 << (char)2 << (char)255 << (char)255;

    Console.gotoxy(X, Y + 1);
    std::cout << (char)255 << (char)205 << (char)203 << (char)205 << (char)255;

    Console.gotoxy(X, Y + 2);
    std::cout << (char)255 << (char)255 << (char)186 << (char)255 << (char)255;

    Console.gotoxy(X, Y + 3);
    std::cout << (char)255 << (char)255 << (char)202 << (char)255 << (char)255;

    Console.gotoxy(X, Y + 4);
    std::cout << (char)255 << (char)188 << (char)255 << (char)200 << (char)255;

}

void Miner::Move(Consola Console, int X, int Y)
{
    setPosition(X, Y);
    energy--;
    Remove(Console);
}

void Miner::Remove(Consola Console)
{
    int X = this->getX();
    int Y = this->getY();

    Console.gotoxy(X, Y);
    std::cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)255;

    Console.gotoxy(X, Y + 1);
    std::cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)255;

    Console.gotoxy(X, Y + 2);
    std::cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)255;

    Console.gotoxy(X, Y + 3);
    std::cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)255;

    Console.gotoxy(X, Y + 4);
    std::cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)255;
}

void Miner::DeleteStats(Consola Console, int X)
{
    Console.gotoxy(2, 1);
    std::cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255;
    Console.gotoxy(2, 2);
    std::cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255;
    Console.gotoxy(2, 3);
    std::cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255;
    Console.gotoxy(2, 4);
    std::cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255;
    Console.gotoxy(0, 6);
    std::cout << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255;
}

int Miner::getX()
{
    return x;
}

int Miner::getY()
{
    return y;
}

void Miner::showStats(Consola Console)
{
    Console.gotoxy(2, 1);
    std::cout << "X: " << this->getX() << " Y: " << this->getY() << (char)255;

    Console.gotoxy(2, 2);
    std::cout << "Lifes: ";
    switch (this->getLife())
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

    Console.gotoxy(2, 3);
    std::cout << "Energy: ";
    if (this->energy == 100)
        {
            std::cout << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219;
        }
    else if (this->energy >= 90)
        {
            std::cout << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)255;
        }
    else if (this->energy >= 80)
        {
            std::cout << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)255 << (char)255;
        }
    else if (this->energy >= 70)
        {
            std::cout << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)255 << (char)255 << (char)255;
        }
    else if (this->energy >= 60)
        {
            std::cout << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)255 << (char)255 << (char)255 << (char)255;
        }
    else if (this->energy >= 50)
        {
            std::cout << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255;
        }
    else if (this->energy >= 40)
        {
            std::cout << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255;
        }
    else if (this->energy >= 30)
        {
            std::cout << (char)219 << (char)219 << (char)219 << (char)219 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255;
        }
    else if (this->energy >= 20)
        {
            std::cout << (char)219 << (char)219 << (char)219 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255;
        }
    else if (this->energy >= 10)
        {
            std::cout << (char)219 << (char)219 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255 << (char)255;
        }
    std::cout << " " << this->getEnergy() << "/100" << (char)255;

    Console.gotoxy(2, 4);
    std::cout << "Coins: " << this->getCoins();

    Console.gotoxy(0, 6);
    std::cout << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205;
}

int Miner::getEnergy()
{
    return energy;
}

int Miner::getCoins()
{
    return coins;
}

int Miner::getLife()
{
    return life;
}

void Miner::setLife(int S)
{
    life = S;
}

void Miner::setEnergy(int S)
{
    energy = S;
}