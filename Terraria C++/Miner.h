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
	Miner();
	void move(Consola Console, int X, int Y);
	void show(Consola Console, int X=10, int Y=10);
	void showStats(Consola Console);
	void setPosition(int x, int y);
	void setLife(int S);
	void setEnergy(int S);

	int getEnergy();
	int getCoins();
	int getLife();

	bool hasLifes();
	bool isAlive(Consola Console);
};

#endif