#include "Miner.h"

/* General */
Miner::Miner(int energy)
{
    myConsole = new Consola();
    _extraLiveCount = 1;
    _energy = energy;
    _coins = 15;

    _bagpackLevel = 1;
    _pickaxeLevel = 1;
    _lightLevel = 1;
    _energyRestoreLevel = 1;

    _ladderCount = 10;
    _beamCount = 5;

    _parachuteCount = 0;
    _dynamiteCount = 0;

    _capacity = 0;

    _teleport = false;

    ResetOreCount();

}
void Miner::ResetStats()
{
    _extraLiveCount = 1;
    _energy = 100;
    _coins = 15;

    _bagpackLevel = 1;
    _pickaxeLevel = 1;
    _lightLevel = 1;
    _energyRestoreLevel = 1;

    _ladderCount = 10;
    _beamCount = 5;
    ResetOreCount();
}
void Miner::ResetOreCount()
{
    _aluminiumCount = 0;
    _charcoalCount = 0;
    _ironCount = 0;
    _goldCount = 0;
    _diamondCount = 0;
}
void Miner::ReachSurface()
{
    switch (getEnergyRestoreLevel())
        {
        case 1:
            _energy = 80;
            break;
        case 2:
            _energy = 120;
            break;
        case 3:
            _energy = 160;
            break;
        case 4:
            _energy = 400;
            break;
        }

    _capacity = 0;

    _coins += (_aluminiumCount * 5) + (_charcoalCount * 8) + (_diamondCount * 25) + (_ironCount * 12) + (_goldCount * 18);

    ResetOreCount();

}

/* Verifications */
bool Miner::hasLives()
{
    if (_extraLiveCount <= 0)
        return false;
    return true;
}
bool Miner::canTeleport()
{
    return _teleport;
}
void Miner::isAlive()
{
    if (_energy <= 0)
        {
            myConsole->clrscr();
            myConsole->gotoxy(1, 4);
            std::cout << "Perdeste toda a energia e 1 vida. Prima qualquer tecla para recomecar.";
            _extraLiveCount -= 1;
            _energy = 100;
            myConsole->getch();
        }
}

/* Movement */
void Miner::Move(int X, int Y)
{
    setCoordinates(X, Y);
    _energy--;
    isAlive();
}
void Miner::setCoordinates(int X, int Y)
{
    _x = X;
    _y = Y;
}

/* Gets*/
int Miner::getEnergyLevel() const
{
    return _energy;
}
int Miner::getCoins() const
{
    return _coins;
}
int Miner::getExtraLiveCount() const
{
    return _extraLiveCount;
}
int Miner::getX() const
{
    return _x;
}
int Miner::getY() const
{
    return _y;
}
int Miner::getMaxCapacity() const
{
    switch (_bagpackLevel)
        {
        case 1:
            return 15;
            break;
        case 2:
            return 25;
            break;
        case 3:
            return 35;
            break;
        }
    return 0;
}
int Miner::getCapacity() const
{
    return _capacity;
}
int Miner::getBackpackLevel() const
{
    return _bagpackLevel;
}
int Miner::getPickaxeLevel() const
{
    return _pickaxeLevel;
}
int Miner::getParachuteCount() const
{
    return _parachuteCount;
}
int Miner::getEnergyRestoreLevel() const
{
    return _energyRestoreLevel;
}
int Miner::getLightLevel() const
{
    return _lightLevel;
}
int Miner::getLadderCount() const
{
    return _ladderCount;
}
int Miner::getBeamCount() const
{
    return _beamCount;
}
int Miner::getAluminumCount() const
{
    return _aluminiumCount;
}
int Miner::getCharcoalCount() const
{
    return _charcoalCount;
}
int Miner::getDiamondCount() const
{
    return _diamondCount;
}
int Miner::getIronCount() const
{
    return _ironCount;
}
int Miner::getGoldCount() const
{
    return _goldCount;
}
int Miner::getDynamiteCount() const
{
    return _dynamiteCount;
}

/* Sets */
void Miner::setTeleport(bool S)
{
    _teleport = S;
}
void Miner::setDynamiteCount(int S)
{
    _dynamiteCount = S;
}
void Miner::setCapacity(int S)
{
    _capacity = S;
}
void Miner::setExtraLiveCount(int S)
{
    _extraLiveCount = S;
}
void Miner::setEnergyLevel(int S)
{
    _energy = S;
}
void Miner::setPickaxeLevel(int S)
{
    _pickaxeLevel = S;
}
void Miner::setBagpackLevel(int S)
{
    _bagpackLevel = S;
}
void Miner::setEnergyRestoreLevel(int S)
{
    _energyRestoreLevel = S;
}
void Miner::setLightLevel(int S)
{
    _lightLevel = S;
}
void Miner::setParachuteCount(int S)
{
    _parachuteCount = S;
}
void Miner::setCoins(int S)
{
    _coins = S;
}
void Miner::setBeamCount(int S)
{
    _beamCount = S;
}
void Miner::setLadderCount(int S)
{
    _ladderCount = S;
}
void Miner::setAluminiumCount(int S)
{
    _aluminiumCount = S;
}
void Miner::setCharcoalCount(int S)
{
    _charcoalCount = S;
}
void Miner::setDiamondCount(int S)
{
    _diamondCount = S;
}
void Miner::setIronCount(int S)
{
    _ironCount = S;
}
void Miner::setGoldCount(int S)
{
    _goldCount = S;
}
