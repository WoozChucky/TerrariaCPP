#ifndef __MINER_H__
#define __MINER_H__

#include "Ponto.h"
#include "Consola.h"

class Miner {
	int x, y;
	int life;
	int energy;
	int coins;
	bool picareta;
	bool lanterna;
	bool escadas;
public:
	Miner(int X, int Y);
	void Move(Consola Console, int X, int Y);
	void Show(Consola Console, int X = 10, int Y = 10);
	void Remove(Consola Console);
	void showStats(Consola Console);
	void isAlive(Consola Console);
	void setPosition(int x, int y);
	void setLife(int S);
	void setEnergy(int S);

	int getEnergy();
	int getCoins();
	int getLife();
	int getX();
	int getY();

	bool hasLifes();
	
};

#endif