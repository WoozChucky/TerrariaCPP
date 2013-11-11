#ifndef __MINER_H__
#define __MINER_H__

#include "Ponto.h"
#include "Consola.h"

class Miner {
	int energy;
	int money;
	bool picareta;
	bool lanterna;
	bool escadas;
	Ponto posicao;
public:
	void move(Consola Console, int X, int Y);
	void show(Consola Console, int X=10, int Y=10);
};

#endif