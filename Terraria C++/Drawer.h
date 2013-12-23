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
#include "Consola.h"

class Drawer
{
private:
    Consola *myConsole;

public:
    Drawer();
    ~Drawer();

    void Draw(Miner obj, int ACTION);
    void DrawStats(Miner obj, int ACTION);
    void Draw(Block ***obj, Miner *obj2, int startDrawX, int startDrawY, int Vision, int Colunas, int Linhas);
    void Draw(Block obj);
    void Draw(Pedra obj);
    void Draw(Escada obj);
    void Draw(Viga obj);
    void Draw(TerrenoDuro obj);
    void Draw(TerrenoMole obj);
    void Draw(TerraCAluminio obj);
    void Draw(TerraCCarvao obj);
    void Draw(TerraCFrango obj);
    void Draw(TerraCOuro obj);
    void Draw(TerraCDiamante obj);
    void Draw(TerraCFerro obj);


};

