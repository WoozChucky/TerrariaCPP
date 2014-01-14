#pragma once
#include "Drawer.h"
#include "INIReader.h"

class Mine
{

    Consola *myConsole;
    int _linhas, _colunas, _vision;
    std::string _nome;

public:
    Drawer *myDrawer;
    Miner *myMiner;
    Block ***myMine;

    Mine(std::string Name, int Rows, int Cols);
    Mine(const Mine& Origin);
    ~Mine();

    const Mine& operator=(const Mine& Other);

    void setVision(int S);
    void setColunas(int S);
    void setLinhas(int S);
    void setName(std::string newName);

    int getVision() const;
    int getColunas() const;
    int getLinhas() const;
    std::string getName() const;

    void RemoveBlock(int &bX, int &bY, int DIRECTION);
    void insertLadder(int x, int y);
    void insertBeam(int x, int y);
    void insertDynamite(int x, int y);
    void blowDynamite();
    void MineOre(int x, int y);
    void Rockslide();

};

