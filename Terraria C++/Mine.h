#pragma once

#include "Drawer.h"

using namespace std;

class Mine
{
    Consola *myConsole;
    int _linhas, _colunas, _vision;
    std::string _nome;
    bool canFall;

public:
    Miner *myMiner;
    Block ***myMine;

    int vX, vY, pX, pY, offSetX, offSetY;

    Mine(std::string Name, int Rows, int Cols);

    Mine(const Mine& Origin);
    ~Mine();

    const Mine& operator=(const Mine& Origin);

    void setVision(int S);
    void setColunas(int S);
    void setLinhas(int S);
    void setName(std::string newName);
    void setFall(bool S);

    int getVision() const;
    int getColunas() const;
    int getLinhas() const;
    std::string getName() const;
    bool getFall() const;

    void RemoveBlock(int &bX, int &bY, int DIRECTION);
    void insertLadder(int x, int y);
    void insertBeam(int x, int y);
    void insertDynamite(int x, int y);
    void blowDynamite();
    void MineOre(int x, int y);
    void Rockslide();

};

