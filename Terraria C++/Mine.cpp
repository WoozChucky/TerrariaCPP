#include "Mine.h"


Mine::Mine(std::string Name, int Rows, int Cols)
{
    myConsole = new Consola();
    myMiner = new Miner(80);

    _nome = Name;
    _linhas = Rows;
    _colunas = Cols;
    canFall = false;
    pY = 0;
    pX = 0;
    vX = 0;
    vY = 0;
    offSetX = -3;
    offSetY = -3;
    _vision = myMiner->getLightLevel();

    srand((unsigned int)time(NULL)); //Randomize

    /* Create Mine Array Dinamically */
    myMine = new Block**[_linhas];
    for (int r = 0; r < _linhas; r++)
        {
            myMine[r] = new Block*[_colunas];
            for (int c = 0; c < _colunas; c++)
                myMine[r][c] = new Vazio(r, c);
        }

    //floor -
    //ceil +
    //round +-

    double NinetyPercent = (10 * _colunas / 100);
    double EightyPercent = (20 * _colunas / 100);
    double SeventyPercent = (30 * _colunas / 100);
    double SixtyPercent = (40 * _colunas / 100);
    double FiftyPercent = (50 * _colunas / 100);
    double FourtyPercent = (60 * _colunas / 100);
    double ThirtyPercent = (70 * _colunas / 100);
    double TwentyPercent = (80 * _colunas / 100);
    double TenPercent = (90 * _colunas / 100);

    /* Populate Mine Array Automatically */
    for (int r = 0; r < _linhas; r++)
        {
            for (int c = 0; c < _colunas; c++)
                {

                    if (r == 0) //first row empty
                        {
                            myMine[r][c] = new Vazio(c, r);
                        }
                    else if (r == _linhas - 1) //last row with stone
                        {
                            myMine[r][c] = new Pedra(c, r);
                        }
                    else if (r == 1 && c == 0) //pedra under spawn
                        {
                            myMine[r][c] = new Pedra(c, r);
                        }
                    else if (r < NinetyPercent)
                        {
                            int poss = rand() % 8 + 0;
                            if (poss == 2)
                                myMine[r][c] = new TerrenoMole(c, r);
                            else if (poss == 8)
                                myMine[r][c] = new TerraCVeneno(c, r);
                            else
                                myMine[r][c] = new TerrenoDuro(c, r);
                        }
                    else if (r < EightyPercent)
                        {
                            int poss = rand() % 9 + 0;
                            if (poss == 8)
                                myMine[r][c] = new TerraCAluminio(c, r);
                            else
                                myMine[r][c] = new TerrenoMole(c, r);
                        }
                    else if (r < SeventyPercent)
                        {
                            int poss = rand() % 6 + 0;
                            if (poss == 6)
                                myMine[r][c] = new TerraCAluminio(c, r);
                            else if (poss == 0)
                                myMine[r][c] = new TerraCVeneno(c, r);
                            else
                                myMine[r][c] = new TerrenoDuro(c, r);
                        }
                    else if (r < SixtyPercent)
                        {
                            int poss = rand() % 9 + 0;
                            if (poss == 8)
                                myMine[r][c] = new TerraCCarvao(c, r);
                            else
                                myMine[r][c] = new TerrenoMole(c, r);
                        }
                    else if (r < FiftyPercent)
                        {
                            int poss = rand() % 6 + 0;
                            if (poss == 6)
                                myMine[r][c] = new TerraCCarvao(c, r);
                            else if (poss == 0)
                                myMine[r][c] = new TerraCVeneno(c, r);
                            else
                                myMine[r][c] = new TerrenoDuro(c, r);
                        }
                    else if (r < FourtyPercent)
                        {
                            int poss = rand() % 8 + 0;
                            if (poss == 8)
                                myMine[r][c] = new TerraCFerro(c, r);
                            else if (poss == 3)
                                myMine[r][c] = new TerraCFrango(c, r);
                            else
                                myMine[r][c] = new TerrenoMole(c, r);
                        }
                    else if (r < ThirtyPercent)
                        {
                            int poss = rand() % 8 + 0;
                            if (poss == 8)
                                myMine[r][c] = new TerraCFerro(c, r);
                            else if (poss == 3)
                                myMine[r][c] = new TerraCVeneno(c, r);
                            else
                                myMine[r][c] = new TerrenoDuro(c, r);
                        }
                    else if (r < TwentyPercent)
                        {
                            int poss = rand() % 8 + 0;
                            if (poss == 8)
                                myMine[r][c] = new TerraCOuro(c, r);
                            else if (poss == 3)
                                myMine[r][c] = new TerraCFrango(c, r);
                            else
                                myMine[r][c] = new TerrenoMole(c, r);
                        }
                    else if (r < TenPercent)
                        {
                            int poss = rand() % 10 + 0;
                            if (poss == 5)
                                myMine[r][c] = new TerraCDiamante(c, r);
                            else if (poss == 3)
                                myMine[r][c] = new TerraCFrango(c, r);
                            else
                                myMine[r][c] = new TerrenoDuro(c, r);
                        }
                    else
                        {
                            int poss = rand() % 10 + 0;
                            if (poss == 5)
                                myMine[r][c] = new TerraCDiamante(c, r);
                            else if (poss == 3)
                                myMine[r][c] = new TerraCOuro(c, r);
                            else
                                myMine[r][c] = new TerrenoMole(c, r);
                        }
                }
        }
}
Mine::Mine(const Mine& Origin)
{
    this->_colunas = Origin._colunas;
    this->_linhas = Origin._linhas;
    this->_nome = Origin._nome;
    this->canFall = Origin.canFall;
    this->pY = Origin.pY;
    this->pX = Origin.pX;
    this->vX = Origin.vX;
    this->vY = Origin.vY;
    this->offSetX = Origin.offSetX;
    this->offSetY = Origin.offSetY;

    this->myMiner = new Miner(Origin.myMiner->getEnergyLevel());
    this->myMiner->setAluminiumCount(Origin.myMiner->getAluminumCount());
    this->myMiner->setBagpackLevel(Origin.myMiner->getBackpackLevel());
    this->myMiner->setBeamCount(Origin.myMiner->getBeamCount());
    this->myMiner->setCapacity(Origin.myMiner->getCapacity());
    this->myMiner->setCoins(Origin.myMiner->getCoins());
    this->myMiner->setCoordinates(Origin.myMiner->getX(), Origin.myMiner->getY());
    this->myMiner->setDiamondCount(Origin.myMiner->getDiamondCount());
    this->myMiner->setDynamiteCount(Origin.myMiner->getDynamiteCount());
    this->myMiner->setEnergyLevel(Origin.myMiner->getEnergyLevel());
    this->myMiner->setEnergyRestoreLevel(Origin.myMiner->getEnergyRestoreLevel());
    this->myMiner->setExtraLiveCount(Origin.myMiner->getExtraLiveCount());
    this->myMiner->setGoldCount(Origin.myMiner->getGoldCount());
    this->myMiner->setIronCount(Origin.myMiner->getIronCount());
    this->myMiner->setLadderCount(Origin.myMiner->getLadderCount());
    this->myMiner->setLightLevel(Origin.myMiner->getLightLevel());
    this->myMiner->setPickaxeLevel(Origin.myMiner->getPickaxeLevel());
    this->myMiner->setTeleport(Origin.myMiner->canTeleport());

    this->myMine = new Block**[Origin.getLinhas()];

    for (int r = 0; r < Origin.getLinhas(); r++)
        {
            this->myMine[r] = new Block*[Origin.getColunas()];
            for (int c = 0; c < Origin.getColunas(); c++)
                {
                    this->myMine[r][c] = Origin.myMine[r][c];
                }
        }

    this->myConsole = Origin.myConsole;
}
Mine::~Mine()
{
    delete[] myMine;
    delete[] myMiner;
    delete[] myConsole;
}

const Mine& Mine::operator=(const Mine& Origin)
{
    if (this != &Origin)
        {
            this->_colunas = Origin._colunas;
            this->_linhas = Origin._linhas;
            this->_nome = Origin._nome;
            this->canFall = Origin.canFall;
            this->pY = Origin.pY;
            this->pX = Origin.pX;
            this->vX = Origin.vX;
            this->vY = Origin.vY;
            this->offSetX = Origin.offSetX;
            this->offSetY = Origin.offSetY;

            this->myMiner = new Miner(Origin.myMiner->getEnergyLevel());
            this->myMiner->setAluminiumCount(Origin.myMiner->getAluminumCount());
            this->myMiner->setBagpackLevel(Origin.myMiner->getBackpackLevel());
            this->myMiner->setBeamCount(Origin.myMiner->getBeamCount());
            this->myMiner->setCapacity(Origin.myMiner->getCapacity());
            this->myMiner->setCoins(Origin.myMiner->getCoins());
            this->myMiner->setCoordinates(Origin.myMiner->getX(), Origin.myMiner->getY());
            this->myMiner->setDiamondCount(Origin.myMiner->getDiamondCount());
            this->myMiner->setDynamiteCount(Origin.myMiner->getDynamiteCount());
            this->myMiner->setEnergyLevel(Origin.myMiner->getEnergyLevel());
            this->myMiner->setEnergyRestoreLevel(Origin.myMiner->getEnergyRestoreLevel());
            this->myMiner->setExtraLiveCount(Origin.myMiner->getExtraLiveCount());
            this->myMiner->setGoldCount(Origin.myMiner->getGoldCount());
            this->myMiner->setIronCount(Origin.myMiner->getIronCount());
            this->myMiner->setLadderCount(Origin.myMiner->getLadderCount());
            this->myMiner->setLightLevel(Origin.myMiner->getLightLevel());
            this->myMiner->setPickaxeLevel(Origin.myMiner->getPickaxeLevel());
            this->myMiner->setTeleport(Origin.myMiner->canTeleport());

            this->myMine = new Block**[Origin.getLinhas()];

            for (int r = 0; r < Origin.getLinhas(); r++)
                {
                    this->myMine[r] = new Block*[Origin.getColunas()];
                    for (int c = 0; c < Origin.getColunas(); c++)
                        {
                            this->myMine[r][c] = Origin.myMine[r][c];
                        }
                }

            this->myConsole = Origin.myConsole;
        }
    return *this;
}

void Mine::setVision(int S)
{
    _vision = S;
}
void Mine::setColunas(int S)
{
    _colunas = S;
}
void Mine::setLinhas(int S)
{
    _linhas = S;
}
void Mine::setName(std::string newName)
{
    _nome = newName;
}
void Mine::setFall(bool S)
{
    canFall = S;
}

int Mine::getLinhas() const
{
    return _linhas;
}
int Mine::getColunas() const
{
    return _colunas;
}
int Mine::getVision() const
{
    return _vision;
}
std::string Mine::getName() const
{
    return _nome;
}
bool Mine::getFall() const
{
    return canFall;
}

void Mine::RemoveBlock(int &bX, int &bY, int DIRECTION)
{
    int Picks;
    switch (myMiner->getPickaxeLevel())
        {
        case 1:
            Picks = 1;
        case 2:
            Picks = 2;
        case 3:
            Picks = 4;
        }
    if (this->myMine[bY][bX]->getBreakeable() == 1)
        {
            if (typeid(*myMine[bY][bX]).name() != typeid(Viga).name() && typeid(*myMine[bY][bX]).name() != typeid(Escada).name() && typeid(*myMine[bY][bX]).name() != typeid(Dynamite).name())
                {
                    while (this->myMine[bY][bX]->getTicks() > 0)
                        {
                            PlaySound(TEXT("Data/mine.wav"), NULL, SND_ASYNC | SND_FILENAME);
                            this->myMine[bY][bX]->setTicks(this->myMine[bY][bX]->getTicks() - Picks);
                            this->myMiner->setEnergyLevel(this->myMiner->getEnergyLevel() - 1);
                            this->myMiner->isAlive();
                        }
                    if (typeid(*myMine[bY + 1][bX]).name() == typeid(Pedra).name())
                        {
                            setFall(false);
                        }
                    MineOre(bX, bY);
                    this->myMine[bY][bX] = new Vazio(bX, bY);
                }
        }
    else
        {
            myMiner->setEnergyLevel(myMiner->getEnergyLevel() + 1);
            switch (DIRECTION)
                {
                case UP:
                    bY++;
                    break;
                case DOWN:
                    bY--;
                    break;
                case RIGHT:
                    bX--;
                    break;
                case LEFT:
                    bX++;
                    break;
                }
        }
}
void Mine::insertLadder(int x, int y)
{
    if (myMiner->getLadderCount() > 0)
        if (typeid(*myMine[y][x]).name() == typeid(Vazio).name())
            {
                myMine[y][x] = new Escada(x, y);
                myMiner->setLadderCount(myMiner->getLadderCount() - 1);
            }
}
void Mine::insertBeam(int x, int y)
{
    if (myMiner->getBeamCount() > 0)
        if (typeid(*myMine[y][x]).name() == typeid(Vazio).name() && typeid(*myMine[y - 1][x]).name() == typeid(Pedra).name())
            {
                myMine[y][x] = new Viga(x, y);
                myMiner->setBeamCount(myMiner->getBeamCount() - 1);
            }
}
void Mine::insertDynamite(int x, int y)
{
    if (myMiner->getDynamiteCount() > 0)
        {
            if (typeid(*myMine[y][x]).name() == typeid(Vazio).name())
                {
                    myMine[y][x] = new Dynamite(x, y);
                    myMiner->setDynamiteCount(myMiner->getDynamiteCount() - 1);
                }
        }
}
void Mine::blowDynamite()
{
    for (int r = 0; r < _linhas; r++)
        {
            for (int c = 0; c < _colunas; c++)
                {
                    if (typeid(*myMine[r][c]).name() == typeid(Dynamite).name())
                        {
                            PlaySound(TEXT("Data/explosion.wav"), NULL, SND_ASYNC | SND_FILENAME);
                            int startR = (r - 2 >= 0) ? r - 2 : (r - 1 >= 0) ? r - 1 : 0;
                            int endR = (r + 2 <= _linhas - 1) ? r + 2 : (r + 1 <= _linhas - 1) ? r + 1 : _linhas - 1;

                            int startC = (c - 2 >= 0) ? c - 2 : (c - 1 >= 0) ? c - 1 : 0;
                            int endC = (c + 2 <= _colunas - 1 ? c + 2 : (c + 1 <= _colunas - 1) ? c + 1 : _colunas - 1);

                            for (int R = startR; R <= endR; R++)
                                {
                                    for (int C = startC; C <= endC; C++)
                                        {
                                            myMine[R][C] = new Vazio(C ,R);
                                            if (myMiner->getX() == C && myMiner->getY() == R)
                                                {
                                                    myMiner->setEnergyLevel(0);
                                                    break;
                                                }
                                        }
                                }
                        }
                }
        }
}
void Mine::MineOre(int x, int y)
{
    if (typeid(*myMine[y][x]).name() == typeid(TerraCFrango).name())
        {
            myMiner->setEnergyLevel(myMiner->getEnergyLevel() + 21);
        }
    else if (typeid(*myMine[y][x]).name() == typeid(TerraCAluminio).name())
        {
            if (myMiner->getCapacity() + 1 <= myMiner->getMaxCapacity())
                {
                    myMiner->setAluminiumCount(myMiner->getAluminumCount() + 1);
                    std::cout << "Found 1 aluminium ore!" << myMiner->getAluminumCount() << " in total." << std::endl;
                    myMiner->setCapacity(myMiner->getCapacity() + 1);
                }
        }
    else if (typeid(*myMine[y][x]).name() == typeid(TerraCCarvao).name())
        {
            if (myMiner->getCapacity() + 2 <= myMiner->getMaxCapacity())
                {
                    myMiner->setCharcoalCount(myMiner->getCharcoalCount() + 1);
                    std::cout << "Found 1 charcoal ore!" << myMiner->getAluminumCount() << " in total." << std::endl;
                    myMiner->setCapacity(myMiner->getCapacity() + 2);
                }
        }
    else if (typeid(*myMine[y][x]).name() == typeid(TerraCDiamante).name())
        {
            if (myMiner->getCapacity() + 4 <= myMiner->getMaxCapacity())
                {
                    myMiner->setDiamondCount(myMiner->getDiamondCount() + 1);
                    std::cout << "Found 1 diamond ore!" << myMiner->getAluminumCount() << " in total." << std::endl;
                    myMiner->setCapacity(myMiner->getCapacity() + 4);
                }
        }
    else if (typeid(*myMine[y][x]).name() == typeid(TerraCFerro).name())
        {
            if (myMiner->getCapacity() + 3 <= myMiner->getMaxCapacity())
                {
                    myMiner->setIronCount(myMiner->getIronCount() + 1);
                    std::cout << "Found 1 iron ore!" << myMiner->getAluminumCount() << " in total." << std::endl;
                    myMiner->setCapacity(myMiner->getCapacity() + 3);
                }
        }
    else if (typeid(*myMine[y][x]).name() == typeid(TerraCOuro).name())
        {
            if (myMiner->getCapacity() + 4 <= myMiner->getMaxCapacity())
                {
                    myMiner->setGoldCount(myMiner->getGoldCount() + 1);
                    std::cout << "Found 1 gold ore!" << myMiner->getAluminumCount() << " in total." << std::endl;
                    myMiner->setCapacity(myMiner->getCapacity() + 4);
                }
        }
    else if(typeid(*myMine[y][x]).name() == typeid(TerraCVeneno).name())
        {
            std::cout << "That block was poisoned, you lost 10 energy!";
            myMiner->setEnergyLevel(myMiner->getEnergyLevel() - 10);
            myConsole->getch();
        }
}

void Mine::Rockslide()
{
    for (int r = 0; r < _linhas - 1; r++)
        {
            for (int c = 0; c < _colunas; c++)
                {
                    if (typeid(*myMine[r][c]).name() == typeid(Pedra).name() && typeid(*myMine[r + 1][c]).name() == typeid(Vazio).name())
                        {
                            if (myMiner->getX() == myMine[r][c]->getX() && myMiner->getY() == myMine[r][c]->getY() && typeid(*myMine[r][c]).name() == typeid(Pedra).name())
                                {
                                    myMiner->setEnergyLevel(0);
                                }
                            else
                                {
                                    PlaySound(TEXT("Data/rockslide.wav"), NULL, SND_ASYNC | SND_FILENAME);
                                    myMine[r][c] = new Vazio(c, r);
                                    myMine[r + 1][c] = new Pedra(c, r + 1);
                                }
                        }
                }
        }
}