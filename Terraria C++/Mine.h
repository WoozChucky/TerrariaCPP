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

    int getVision();
    int getColunas();
    int getLinhas();

    void RemoveBlock(int &bX, int &bY, int DIRECTION);
    void insertLadder(int x, int y);
    void insertBeam(int x, int y);
    void insertDynamite(int x, int y);
    void blowDynamite();
    void MineOre(int x, int y);

};

