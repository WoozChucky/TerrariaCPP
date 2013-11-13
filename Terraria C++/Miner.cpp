#include <iostream>
#include "Miner.h"

Miner::Miner()
{
	this->energy = 100;
	this->coins = 0;
	this->life = 3;
	this->escadas = false;
	this->picareta = false;
	this->lanterna = false;
}

bool Miner::hasLifes()
{
	if (this->life <= 0)
		return false;
	return true;
}

bool Miner::isAlive(Consola Console)
{
	if (this->energy <= 0)
	{
		Console.clrscr();
		Console.gotoxy(10, 18);
		std::cout << "Perdeste toda a energia e 1 vida. Prima qualquer tecla para continuar.";
		this->setLife(this->getLife()-1);
		this->setEnergy(100);
		return true;
	}
	return true;
}

void Miner::setPosition(int X, int Y)
{
	this->x = X;
	this->y = Y;
}

void Miner::show(Consola Console, int X, int Y)
{
	Console.gotoxy(X, Y-1);
	std::cout << (char)219;
	Console.gotoxy(X+1, Y);
	std::cout << (char)196;
	Console.gotoxy(X, Y);
	std::cout << (char)179;
	Console.gotoxy(X-1, Y);
	std::cout << (char)196;
	Console.gotoxy(X, Y+1);
	std::cout << (char)179;
	Console.gotoxy(X-1, Y+2);
	std::cout << (char)47;
	Console.gotoxy(X+1, Y+2); 
	std::cout << (char)92;
}

void Miner::move(Consola Console, int X, int Y)
{
	Console.clrscr();
	this->energy--;
	this->setPosition(X, Y);
	this->showStats(Console);
	this->show(Console, X, Y);
	this->show(Console, X, Y);
}

void Miner::showStats(Consola Console)
{
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
		std::cout << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219;
	}
	else if (this->energy >= 80)
	{
		std::cout << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219;
	}
	else if (this->energy >= 70)
	{
		std::cout << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219;
	}
	else if (this->energy >= 60)
	{
		std::cout << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219;
	}
	else if (this->energy >= 50)
	{
		std::cout << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219;
	}
	else if (this->energy >= 40)
	{
		std::cout << (char)219 << (char)219 << (char)219 << (char)219 << (char)219;
	}
	else if (this->energy >= 30)
	{
		std::cout << (char)219 << (char)219 << (char)219 << (char)219;
	}
	else if (this->energy >= 20)
	{
		std::cout << (char)219 << (char)219 << (char)219;
	}
	else if (this->energy >= 10)
	{
		std::cout << (char)219 << (char)219;
	}
	std::cout << " " << this->getEnergy() << "/100";

	Console.gotoxy(2, 4);
	std::cout << "Coins: " << this->getCoins();
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