#pragma once
#include "Drawer.h"
#include "INIReader.h"

class Mine
{

    Consola *myConsole;
    int _linhas, _colunas, _vision;

public:

    INIReader *reader;
    Drawer *myDrawer;
    Miner *myMiner;
    Block ***myMine;

    Mine(int Rows, int Cols);
    ~Mine();

    void setVision(int S);
    void setColunas(int S);
    void setLinhas(int S);

    int getVision() const;
    int getColunas() const;
    int getLinhas() const;

    void RemoveBlock(int &bX, int &bY, int DIRECTION);
    void insertLadder(int x, int y);
    void insertBeam(int x, int y);
    void insertDynamite(int x, int y);
    void blowDynamite();
    void MineOre(int x, int y);

};

