#pragma once
#include "Consola.h"
class Miner
{
private:
    Consola *myConsole;
    int _energy;
    int _coins;
    int _x, _y; //current coordinates
    int _pickaxeLevel, _energyRestoreLevel, _bagpackLevel, _lightLevel, _parachuteCount, _ladderCount, _beamCount, _extraLiveCount, _dynamiteCount; //Tools
    int _aluminiumCount, _charcoalCount, _ironCount, _goldCount, _diamondCount; //Ores
    int _capacity;
public:
    /* General */
    Miner(int energy);
    void ResetStats();
    void ResetOreCount();
    void ReachSurface();

    /* Verifications */
    bool hasLives();
    void isAlive();

    /* Movement */
    void Move(int X, int Y);
    void setCoordinates(int X, int Y);

    /*           Sets                 */
    void setEnergyLevel(int S);
    void setCoins(int S);
    void setCapacity(int S);
    /* Tools Level */
    void setExtraLiveCount(int S);
    void setPickaxeLevel(int S);
    void setBagpackLevel(int S);
    void setEnergyRestoreLevel(int S);
    void setLightLevel(int S);
    /* Tools Count */
    void setParachuteCount(int S);
    void setLadderCount(int S);
    void setBeamCount(int S);
    void setDynamiteCount(int S);
    /* Ores */
    void setAluminiumCount(int S);
    void setCharcoalCount(int S);
    void setIronCount(int S);
    void setGoldCount(int S);
    void setDiamondCount(int S);

    /* Gets */
    int getEnergyLevel() const;
    int getCoins() const;
    int getExtraLiveCount() const;
    int getX() const;
    int getY() const;
    int getMaxCapacity() const;
    int getCapacity() const;
    int getLightLevel() const;
    int getLadderCount() const;
    int getBeamCount() const;
    int getDynamiteCount() const;
    /* Ores */
    int getAluminumCount() const;
    int getCharcoalCount() const;
    int getDiamondCount() const;
    int getIronCount() const;
    int getGoldCount() const;

};