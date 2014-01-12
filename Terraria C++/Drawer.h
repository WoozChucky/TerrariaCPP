#pragma once

#include "Miner.h"
#include "Block.h"
#include "Pedra.h"
#include "TerrenoMole.h"
#include "TerrenoDuro.h"
#include "Escada.h"
#include "Viga.h"
#include "TerraCAluminio.h"
#include "TerraCCarvao.h"
#include "TerraCDiamante.h"
#include "TerraCFerro.h"
#include "TerraCFrango.h"
#include "TerraCOuro.h"
#include "Vazio.h"
#include "Dynamite.h"
#include "TerraCVeneno.h"

class Drawer
{
private:
    Consola *myConsole;

public:
    Drawer();
    ~Drawer();

    void Draw(Miner obj, int ACTION, int SPECIAL = NULL);
    void DrawStats(Miner obj, int ACTION);
    void DrawMine(Block ***obj, Miner obj2, int startDrawX, int startDrawY, int Vision, int Colunas, int Linhas);
    void DrawBlock(std::array<std::array<int, 5>, 5> drawSequence, int _y, int _x);
    void DrawPauseMenu();
    void DrawMainMenu();


};

