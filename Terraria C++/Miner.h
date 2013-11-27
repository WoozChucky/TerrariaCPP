#ifndef __MINER_H__
#define __MINER_H__

#include "Ponto.h"
#include "Consola.h"

class Miner {
	//std::vector<int, int> X1;
	//std::vector<int, int> X2;
	int x, y;
	int life;
	int energy;
	int coins;
	bool picareta;
	bool lanterna;
	bool escadas;
public:
	Miner(int Life, int Energy, int Coins);

	void Move(Consola Console, int X, int Y);
	void ResetStats();
	
	//Draws
	void Show(Consola Console, int X = 10, int Y = 10);
	void Remove(Consola Console);
	void showStats(Consola Console);
	void DeleteStats(Consola Console, int X);

	//Verifications
	bool hasLifes();
	void isAlive(Consola Console);

	//Sets
	void setPosition(int x, int y);
	void setLife(int S);
	void setEnergy(int S);
	
	//Stats
	int getEnergy();
	int getCoins();
	int getLife();

	//Positioning
	int getX();
	int getY();

	//Bounds
	int getX1();
	int getX2();
	int getY1();
	int getY2();

};

#endif