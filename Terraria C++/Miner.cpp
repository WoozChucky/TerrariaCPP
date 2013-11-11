#include <iostream>
#include "Miner.h"

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
	this->show(Console, X, Y);
	//remove energy
	//bla bla bla
}