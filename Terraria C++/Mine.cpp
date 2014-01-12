#include "Mine.h"


Mine::Mine(std::string Name, int Rows, int Cols)
{
    myDrawer = new Drawer();
    myConsole = new Consola();
    myMiner = new Miner(100);

    _nome = Name;
    _linhas = Rows;
    _colunas = Cols;
    _vision = myMiner->getLightLevel();

    srand((unsigned int)time(NULL)); //Randomize

    /* Create Mine Array Dinamically */
    myMine = new Block**[_linhas];
    for (int r = 0; r < _linhas; r++)
        {
            myMine[r] = new Block*[_colunas];
            for (int c = 0; c < _colunas; c++)
                myMine[r][c] = new Block();
        }

    //floor -
    //ceil +
    //round +-

    std::random_device rd;
    std::default_random_engine re(rd());
    std::uniform_real_distribution<> coiso(1.0, 100.0);

    /*for (int n = 0; n < 10; ++n)
        {
            std::cout << round(coiso(re)) << " ";
        }
    system("pause");*/

    int NinetyPercent = (int)round(90 * _colunas / 100);
    int EightyPercent = (int)round(80 * _colunas / 100);
    int SeventyPercent = (int)round(70 * _colunas / 100);
    int SixtyPercent = (int)round(60 * _colunas / 100);
    int FiftyPercent = (int)round(50 * _colunas / 100);
    int FourtyPercent = (int)ceil(40 * _colunas / 100);
    int ThirtyPercent = (int)ceil(30 * _colunas / 100);
    int TwentyPercent = (int)ceil(20 * _colunas / 100);
    int TenPercent = (int)ceil(10 * _colunas / 100);

    /* Populate Mine Array Automatically */
    for (int r = 0; r < _linhas; r++)
        {
            for (int c = 0; c < _colunas; c++)
                {
                    int blockType = rand() % 9 + 1; //Generates a random block type

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
                    else if (r > TwentyPercent)
                        {
                            int poss = rand() % 8 + 0;
                            if (poss == 8)
                                myMine[r][c] = new TerraCOuro(c, r);
                            else
                                myMine[r][c] = new TerrenoDuro(c, r);
                        }
                    else if (r > TenPercent)
                        {
                            int poss = rand() % 10 + 0;
                            if (poss == 5)
                                myMine[r][c] = new TerraCDiamante(c, r);
                            else
                                myMine[r][c] = new TerrenoMole(c, r);
                        }
                    else
                        {
                            myMine[r][c] = new TerrenoDuro(c, r);
                        }
                }
        }
}
Mine::~Mine()
{
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
            if (typeid(*myMine[bY][bX]).name() != typeid(Viga).name() && typeid(*myMine[bY][bX]).name() != typeid(Escada).name())
                {
                    while (this->myMine[bY][bX]->getTicks() > 0)
                        {
                            PlaySound(TEXT("data/mine.wav"), NULL, SND_ASYNC | SND_FILENAME);
                            this->myMine[bY][bX]->setTicks(this->myMine[bY][bX]->getTicks() - Picks);
                            this->myMiner->setEnergyLevel(this->myMiner->getEnergyLevel() - 1);
                            this->myMiner->isAlive();
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
                    myMiner->setCapacity(myMiner->getCapacity() + 2);
                }
        }
    else if (typeid(*myMine[y][x]).name() == typeid(TerraCDiamante).name())
        {
            if (myMiner->getCapacity() + 4 <= myMiner->getMaxCapacity())
                {
                    myMiner->setDiamondCount(myMiner->getDiamondCount() + 1);
                    myMiner->setCapacity(myMiner->getCapacity() + 4);
                }
        }
    else if (typeid(*myMine[y][x]).name() == typeid(TerraCFerro).name())
        {
            if (myMiner->getCapacity() + 3 <= myMiner->getMaxCapacity())
                {
                    myMiner->setIronCount(myMiner->getIronCount() + 1);
                    myMiner->setCapacity(myMiner->getCapacity() + 3);
                }
        }
    else if (typeid(*myMine[y][x]).name() == typeid(TerraCOuro).name())
        {
            if (myMiner->getCapacity() + 4 <= myMiner->getMaxCapacity())
                {
                    myMiner->setGoldCount(myMiner->getGoldCount() + 1);
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