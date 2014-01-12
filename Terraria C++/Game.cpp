#include "Game.h"

std::string validCommands[NUM_COMMANDS][2] =
{
    { "u", "2" },//u nome-utensilio
    { "b", "4" },//b ID x y
    { "t", "3" },//t x y
    { "g", "2" },//g value
    { "e", "2" },//e value
    { "c", "2" },//c new_name
    { "f", "2" },//f name
    { "a", "3" },//a source destination
    { "x", "2" },//x
    { "j", "2" },//j
    { "m", "1" } //m
};

std::string startCommands[2][2] =
{
    { "load", "2" },//load filename
    { "jogo", "5" } //jogo minename rows columns dif
};

/* General */
Game::Game()
{
    _currentStatus = ACTIVE;
    myConsole = new Consola();
    LoadUtensilios(myUtensilios); //Loads tools into myUtensilios's object array
    offSetX = -3;
    offSetY = -3;
}
void Game::Start()
{
    PlayIntro();

    myConsole->setTextColor(myConsole->PRETO);
    myConsole->setBackgroundColor(myConsole->BRANCO_CLARO);
    myConsole->setScreenSize(20, 50);
    myConsole->clrscr();

    std::string read; //User input/command
    bool valid = false; //Boolean to check if command exists/is valid
    int action = 0;

    while (read != "exit")
        {
            myConsole->gotoxy(2, 2);
            std::cout << "[Gem Miner Menu]";
            myConsole->gotoxy(0, 4);
            std::cout << "Command : ____________________";
            myConsole->gotoxy(10, 4);
            std::getline(std::cin, read);

            std::istringstream iss(read);
            std::istringstream countstream(read);
            std::string command;
            std::string params[5];

            int count = 0;

            do //Counts number of arguments and stores it in 'count'
                {
                    std::string counter;
                    countstream >> counter;
                    count++;
                }
            while (countstream);
            count--;

            iss >> command;


            for (int i = 0; i< 2; i++) //Runs the startCommands array
                {
                    if (command.compare(startCommands[i][0]) == 0) //if command comparison returns 0 (exists), then valid var is set to true
                        {
                            valid = true;
                            action = i;
                            break;
                        }
                }

            if (valid == false) //command doesnt exist
                {
                    myConsole->clrscr();
                    myConsole->gotoxy(2, 2);
                    std::cout << "[Gem Miner Menu]";
                    myConsole->gotoxy(0, 4);
                    std::cout << "Command : ____________________";
                    myConsole->gotoxy(0, 6);
                    std::cout << "[GAME] -> '" << read << "' - invalid command.";
                }
            else //Command exists, procede to specific command action
                {
                    valid = false;
                    myConsole->clrscr();
                    myConsole->gotoxy(2, 2);
                    std::cout << "[Gem Miner Menu]";
                    myConsole->gotoxy(0, 4);
                    std::cout << "Command : ____________________";
                    myConsole->gotoxy(0, 6);
                    std::cout << "[GAME] -> ";
                    switch (action)
                        {
                        case 0: //Load
                            if (count == atoi(startCommands[action][1].c_str()))
                                {
                                    for (int i = 0; i < atoi(startCommands[action][1].c_str()) - 1; i++)
                                        {
                                            iss >> params[i];
                                        }
                                    LoadGame(params[0]);
                                    break;
                                }
                            else
                                {
                                    std::cout << std::endl << std::endl << "Invalid argument number!" << std::endl;
                                    break;
                                }
                        case 1: //New
                            if (count == atoi(startCommands[action][1].c_str()))
                                {
                                    for (int i = 0; i < atoi(startCommands[action][1].c_str()) - 1; i++)
                                        {
                                            iss >> params[i];
                                        }
                                    NewGame(params[0], atoi(params[1].c_str()), atoi(params[2].c_str()), atoi(params[3].c_str()));
                                    break;
                                }
                            else
                                {
                                    std::cout << std::endl << std::endl << "Invalid argument number!" << std::endl;
                                    break;
                                }
                        }
                }
        }
    myConsole->clrscr();
    exit(0);
    return;
}

/* Game States */
void Game::NewGame(std::string Name, int Rows, int Columns, int Difficulty)
{
    if (Rows < 7 || Columns < 7) //Test minimum mine size
        {
            std::cout << "Invalid mine size!" << std::endl;
            return;
        }


    //TODO: Handle Difficulty

    this->myConsole->clrscr();
    myMine = new Mine(Name, Rows, Columns); //Creates new mine with size (rows, columns)

    StopMusic();
    PlayTheme();

    Play(0, 0, myMine->getLinhas() / 2 - 3, myMine->getColunas() / 2 - 3);
}
void Game::LoadGameMenu()
{
    int numSaves = 0;
    char tecla;
    BOOL H = true;
    wchar_t* savesLocation = L"Saves/*.gem";

    WIN32_FIND_DATA FindFileData;
    HANDLE hFind;
    hFind = FindFirstFile(savesLocation, &FindFileData); //Searches a directory for a file or subdirectory with a name that matches a specific name

    myConsole->clrscr();

    if (hFind != INVALID_HANDLE_VALUE)
        {
            numSaves++;
            while ((H = FindNextFile(hFind, &FindFileData)) == TRUE)
                numSaves++; //increments number of save games found
        }

    myConsole->gotoxy(6, 2);
    if (numSaves == 0)
        {
            std::cout << "Error: ";
            std::cout << "Savegames found = " << numSaves;
            system("pause");
            return;
        }

    std::cout << " -----Saves-----";

    for (int i = 1; i <= numSaves; i++)
        {
            myConsole->gotoxy(4, 4 + (i * 2));
            std::cout << "Save " << i;
        }

    int x = 3, y = 6;
    myConsole->gotoxy(x, y);
    std::cout << '>';
    while (1)
        {
            tecla = myConsole->getch();
            if (tecla == ENTER) break;
            if (tecla != UP && tecla != DOWN) continue;

            myConsole->gotoxy(x, y);
            std::cout << ' ';

            if (tecla == myConsole->CIMA) y -= 2;
            if (tecla == myConsole->BAIXO) y += 2;
            if (y < 6) y = 6;
            if (y > 4 + (numSaves * 2)) y = 4 + (numSaves * 2);
            myConsole->gotoxy(x, y);
            std::cout << '>';
        }

    myConsole->clrscr();
    int nameID = (y - 4) / 2;
    std::string filename = GetLoadFilename(nameID); //Gets filename by passing index(int) of file

    std::ifstream infile;
    int value = 0;
    std::string data;

    infile.open("Saves/" + filename);

    if (!infile)
        {
            std::cout << "File doesnt exist!";
            myConsole->getch();
            return;
        }

    infile >> data; //Data
    infile >> data; //[MINE]
    infile >> data >> data >> value; //Columns
    int colunas = value;
    infile >> data >> data >> value; //Rows
    int linhas = value;
    infile >> data >> data >> value; //Vision
    int vision = value;

    //myMine = new Mine(linhas, colunas);
    myMine->setVision(vision);

    infile >> data; //[MINER]
    infile >> data >> data >> value; // Coins
    myMine->myMiner->setCoins(value);
    infile >> data >> data >> value; // Energy
    myMine->myMiner->setEnergyLevel(value);
    infile >> data >> data >> value; // X
    myMine->myMiner->setCoordinates(value, 0);
    infile >> data >> data >> value; // Y
    myMine->myMiner->setCoordinates(myMine->myMiner->getX(), value);
    infile >> data >> data >> value; // Capacity
    myMine->myMiner->setCapacity(value);
    infile >> data >> data >> value; // Pickaxe
    myMine->myMiner->setPickaxeLevel(value);
    infile >> data >> data >> value; // EnergyRestore
    myMine->myMiner->setEnergyRestoreLevel(value);
    infile >> data >> data >> value; // Bagpack
    myMine->myMiner->setBagpackLevel(value);
    infile >> data >> data >> value; // LightLevel
    myMine->myMiner->setLightLevel(value);
    infile >> data >> data >> value; // Parachute
    myMine->myMiner->setParachuteCount(value);
    infile >> data >> data >> value; // Ladder
    myMine->myMiner->setLadderCount(value);
    infile >> data >> data >> value; // Beam
    myMine->myMiner->setBeamCount(value);
    infile >> data >> data >> value; // ExtraLive
    myMine->myMiner->setExtraLiveCount(value);
    infile >> data >> data >> value; // Dynamite
    myMine->myMiner->setDynamiteCount(value);
    infile >> data >> data >> value; // Aluminium
    myMine->myMiner->setAluminiumCount(value);
    infile >> data >> data >> value; // Charcoal
    myMine->myMiner->setCharcoalCount(value);
    infile >> data >> data >> value; // Diamond
    myMine->myMiner->setDiamondCount(value);
    infile >> data >> data >> value; // Iron
    myMine->myMiner->setIronCount(value);
    infile >> data >> data >> value; // Gold
    myMine->myMiner->setGoldCount(value);

    infile >> data; //[BLOCKS]

    std::string className;
    int breakeable;
    int ticks;

    for (int r = 0; r < linhas; r++)
        {
            for (int c = 0; c < colunas; c++)
                {
                    infile >> data >> data >> data >> data;
                    className = data;
                    infile >> data >> data >> value;
                    breakeable = value;
                    infile >> data >> data >> value;
                    ticks = value;
                    infile >> data >> data >> value;
                    x = value;
                    infile >> data >> data >> value;
                    y = value;

                    if (className == "Dynamite")
                        {
                            myMine->myMine[r][c] = new Dynamite(x, y);
                            myMine->myMine[r][c]->setTicks(ticks);
                        }
                    else if (className == "Escada")
                        {
                            myMine->myMine[r][c] = new Escada(x, y);
                            myMine->myMine[r][c]->setTicks(ticks);
                        }
                    else if (className == "Pedra")
                        {
                            myMine->myMine[r][c] = new Pedra(x, y);
                            myMine->myMine[r][c]->setTicks(ticks);
                        }
                    else if (className == "TerraCAluminio")
                        {
                            myMine->myMine[r][c] = new TerraCAluminio(x, y);
                            myMine->myMine[r][c]->setTicks(ticks);
                        }
                    else if (className == "TerraCCarvao")
                        {
                            myMine->myMine[r][c] = new TerraCCarvao(x, y);
                            myMine->myMine[r][c]->setTicks(ticks);
                        }
                    else if (className == "TerraCDiamante")
                        {
                            myMine->myMine[r][c] = new TerraCDiamante(x, y);
                            myMine->myMine[r][c]->setTicks(ticks);
                        }
                    else if (className == "TerraCFerro")
                        {
                            myMine->myMine[r][c] = new TerraCFerro(x, y);
                            myMine->myMine[r][c]->setTicks(ticks);
                        }
                    else if (className == "TerraCFrango")
                        {
                            myMine->myMine[r][c] = new TerraCFrango(x, y);
                            myMine->myMine[r][c]->setTicks(ticks);
                        }
                    else if (className == "TerraCOuro")
                        {
                            myMine->myMine[r][c] = new TerraCOuro(x, y);
                            myMine->myMine[r][c]->setTicks(ticks);
                        }
                    else if (className == "TerrenoDuro")
                        {
                            myMine->myMine[r][c] = new TerrenoDuro(x, y);
                            myMine->myMine[r][c]->setTicks(ticks);
                        }
                    else if (className == "TerrenoMole")
                        {
                            myMine->myMine[r][c] = new TerrenoMole(x, y);
                            myMine->myMine[r][c]->setTicks(ticks);
                        }
                    else if (className == "Vazio")
                        {
                            myMine->myMine[r][c] = new Vazio(x, y);
                            myMine->myMine[r][c]->setTicks(ticks);
                        }
                    else if (className == "Viga")
                        {
                            myMine->myMine[r][c] = new Viga(x, y);
                            myMine->myMine[r][c]->setTicks(ticks);
                        }
                    else if (className == "TerraCVeneno")
                        {
                            myMine->myMine[r][c] = new TerraCVeneno(x, y);
                            myMine->myMine[r][c]->setTicks(ticks);
                        }


                }
        }

    Play(myMine->myMiner->getX(), myMine->myMiner->getY(), myMine->getLinhas() / 2 - 3, myMine->getColunas() / 2 - 3);
}
void Game::LoadGame(std::string filename)
{
    std::ifstream infile;
    int value = 0;
    std::string data;

    infile.open("Saves/" + filename + ".gem");

    if (!infile)
        {
            std::cout << "File doesnt exist!";
            myConsole->getch();
            return;
        }

    infile >> data; //Data
    infile >> data; //[MINE]
    infile >> data >> data >> value; //Columns
    int colunas = value;
    infile >> data >> data >> value; //Rows
    int linhas = value;
    infile >> data >> data >> value; //Vision
    int vision = value;

    myMine = new Mine("Stable", linhas, colunas);
    myMine->setVision(vision);

    infile >> data; //[MINER]
    infile >> data >> data >> value; // Coins
    myMine->myMiner->setCoins(value);
    infile >> data >> data >> value; // Energy
    myMine->myMiner->setEnergyLevel(value);
    infile >> data >> data >> value; // X
    myMine->myMiner->setCoordinates(value, 0);
    infile >> data >> data >> value; // Y
    myMine->myMiner->setCoordinates(myMine->myMiner->getX(), value);
    infile >> data >> data >> value; // Capacity
    myMine->myMiner->setCapacity(value);
    infile >> data >> data >> value; // Pickaxe
    myMine->myMiner->setPickaxeLevel(value);
    infile >> data >> data >> value; // EnergyRestore
    myMine->myMiner->setEnergyRestoreLevel(value);
    infile >> data >> data >> value; // Bagpack
    myMine->myMiner->setBagpackLevel(value);
    infile >> data >> data >> value; // LightLevel
    myMine->myMiner->setLightLevel(value);
    infile >> data >> data >> value; // Parachute
    myMine->myMiner->setParachuteCount(value);
    infile >> data >> data >> value; // Ladder
    myMine->myMiner->setLadderCount(value);
    infile >> data >> data >> value; // Beam
    myMine->myMiner->setBeamCount(value);
    infile >> data >> data >> value; // ExtraLive
    myMine->myMiner->setExtraLiveCount(value);
    infile >> data >> data >> value; // Dynamite
    myMine->myMiner->setDynamiteCount(value);
    infile >> data >> data >> value; // Aluminium
    myMine->myMiner->setAluminiumCount(value);
    infile >> data >> data >> value; // Charcoal
    myMine->myMiner->setCharcoalCount(value);
    infile >> data >> data >> value; // Diamond
    myMine->myMiner->setDiamondCount(value);
    infile >> data >> data >> value; // Iron
    myMine->myMiner->setIronCount(value);
    infile >> data >> data >> value; // Gold
    myMine->myMiner->setGoldCount(value);

    infile >> data; //[BLOCKS]

    std::string className;
    int breakeable;
    int ticks;
    int x, y;

    for (int r = 0; r < linhas; r++)
        {
            for (int c = 0; c < colunas; c++)
                {
                    infile >> data >> data >> data >> data;
                    className = data;
                    infile >> data >> data >> value;
                    breakeable = value;
                    infile >> data >> data >> value;
                    ticks = value;
                    infile >> data >> data >> value;
                    x = value;
                    infile >> data >> data >> value;
                    y = value;

                    if (className == "Dynamite")
                        {
                            myMine->myMine[r][c] = new Dynamite(x, y);
                            myMine->myMine[r][c]->setTicks(ticks);
                        }
                    else if(className == "Escada")
                        {
                            myMine->myMine[r][c] = new Escada(x, y);
                            myMine->myMine[r][c]->setTicks(ticks);
                        }
                    else if (className == "Pedra")
                        {
                            myMine->myMine[r][c] = new Pedra(x, y);
                            myMine->myMine[r][c]->setTicks(ticks);
                        }
                    else if (className == "TerraCAluminio")
                        {
                            myMine->myMine[r][c] = new TerraCAluminio(x, y);
                            myMine->myMine[r][c]->setTicks(ticks);
                        }
                    else if (className == "TerraCCarvao")
                        {
                            myMine->myMine[r][c] = new TerraCCarvao(x, y);
                            myMine->myMine[r][c]->setTicks(ticks);
                        }
                    else if (className == "TerraCDiamante")
                        {
                            myMine->myMine[r][c] = new TerraCDiamante(x, y);
                            myMine->myMine[r][c]->setTicks(ticks);
                        }
                    else if (className == "TerraCFerro")
                        {
                            myMine->myMine[r][c] = new TerraCFerro(x, y);
                            myMine->myMine[r][c]->setTicks(ticks);
                        }
                    else if (className == "TerraCFrango")
                        {
                            myMine->myMine[r][c] = new TerraCFrango(x, y);
                            myMine->myMine[r][c]->setTicks(ticks);
                        }
                    else if (className == "TerraCOuro")
                        {
                            myMine->myMine[r][c] = new TerraCOuro(x, y);
                            myMine->myMine[r][c]->setTicks(ticks);
                        }
                    else if (className == "TerrenoDuro")
                        {
                            myMine->myMine[r][c] = new TerrenoDuro(x, y);
                            myMine->myMine[r][c]->setTicks(ticks);
                        }
                    else if (className == "TerrenoMole")
                        {
                            myMine->myMine[r][c] = new TerrenoMole(x, y);
                            myMine->myMine[r][c]->setTicks(ticks);
                        }
                    else if (className == "Vazio")
                        {
                            myMine->myMine[r][c] = new Vazio(x, y);
                            myMine->myMine[r][c]->setTicks(ticks);
                        }
                    else if (className == "Viga")
                        {
                            myMine->myMine[r][c] = new Viga(x, y);
                            myMine->myMine[r][c]->setTicks(ticks);
                        }
                    else if (className == "TerraCVeneno")
                        {
                            myMine->myMine[r][c] = new TerraCVeneno(x, y);
                            myMine->myMine[r][c]->setTicks(ticks);
                        }


                }
        }

    Play(myMine->myMiner->getX(), myMine->myMiner->getY(), myMine->getLinhas() / 2 - 3, myMine->getColunas() / 2 - 3);


}
void Game::SaveGame(std::string filename)
{

    filename = "Saves/" + filename + ".gem";

    std::ifstream ifile(filename);
    if (ifile)
        {
            std::cout << "File name already exists!";
            myConsole->getch();
            return;
        }

    std::ofstream outfile;
    outfile.open(filename.c_str(), std::ios::app);

    outfile << currentDate() << std::endl << std::endl;

    outfile << "[MINE]" << std::endl;
    outfile << "Columns = " << myMine->getColunas() << std::endl;
    outfile << "Rows = " << myMine->getLinhas() << std::endl;
    outfile << "Vision = " << myMine->getVision() << std::endl << std::endl;

    outfile << "[MINER]" << std::endl;
    outfile << "Coins = " << myMine->myMiner->getCoins() << std::endl;
    outfile << "Energy = " << myMine->myMiner->getEnergyLevel() << std::endl;
    outfile << "X = " << myMine->myMiner->getX() << std::endl;
    outfile << "Y = " << myMine->myMiner->getY() << std::endl;
    outfile << "Capacity = " << myMine->myMiner->getCapacity() << std::endl;
    outfile << "PickaxeLevel = " << myMine->myMiner->getPickaxeLevel() << std::endl;
    outfile << "EnergyRestoreLevel = " << myMine->myMiner->getEnergyRestoreLevel() << std::endl;
    outfile << "BagpackLevel = " << myMine->myMiner->getBackpackLevel() << std::endl;
    outfile << "LightLevel = " << myMine->myMiner->getLightLevel() << std::endl;
    outfile << "Parachute = " << myMine->myMiner->getParachuteCount() << std::endl;
    outfile << "Ladder = " << myMine->myMiner->getLadderCount() << std::endl;
    outfile << "Beam = " << myMine->myMiner->getBeamCount() << std::endl;
    outfile << "ExtraLive = " << myMine->myMiner->getExtraLiveCount() << std::endl;
    outfile << "Dynamite = " << myMine->myMiner->getDynamiteCount() << std::endl;
    outfile << "Aluminium = " << myMine->myMiner->getAluminumCount() << std::endl;
    outfile << "Charcoal = " << myMine->myMiner->getCharcoalCount() << std::endl;
    outfile << "Diamond = " << myMine->myMiner->getDiamondCount() << std::endl;
    outfile << "Iron = " << myMine->myMiner->getIronCount() << std::endl;
    outfile << "Gold = " << myMine->myMiner->getGoldCount() << std::endl << std::endl;

    outfile << "[BLOCKS]" << std::endl;
    for (int r = 0; r < myMine->getLinhas(); r++)
        {
            for (int c = 0; c < myMine->getColunas(); c++)
                {
                    outfile << "Type = " << typeid(*myMine->myMine[r][c]).name() << std::endl;
                    outfile << "Breakeable = " << myMine->myMine[r][c]->getBreakeable() << std::endl;
                    outfile << "Ticks = " << myMine->myMine[r][c]->getTicks() << std::endl;
                    outfile << "X = " << myMine->myMine[r][c]->getX() << std::endl;
                    outfile << "Y = " << myMine->myMine[r][c]->getY() << std::endl << std::endl;
                }
        }


    if (outfile.fail())
        {
            std::cout << "write failed" << std::endl;
            outfile.close();
            myConsole->getch();
            return;
        }


    outfile.close();

    std::cout << "Saved at " << filename;
    myConsole->getch();
    return;
}
void Game::Play(int _pX, int _pY, int _vX, int _vY)
{
    this->myConsole->setScreenBufferSize(7 * 5 + 10, 7 * 5); //Window buffer size
    this->myConsole->setScreenSize(7 * 5 + 10, 7 * 5); //Windows size
    this->myConsole->setTextColor(this->myConsole->PRETO);

    char tecla;
    pX = _pX, pY = _pY; //Player Start Position
    vX = _vX, vY = _vY; //Mine Start Writing Position


    /* Miner Start Position */
    myMine->myMiner->setCoordinates(pX, pY);




    //if (pX + 3 < myMine->getColunas()) //DOWN
    //    {
    //        offSetX++;
    //    }

    /* Main cycle of Game */
    while (myMine->myMiner->hasLives())
        {
            myConsole->clrscr();
            myMine->myDrawer->DrawMine(myMine->myMine, *myMine->myMiner, vX, vY, myMine->getVision(), myMine->getColunas(), myMine->getLinhas());	//Draws Mine

            if (typeid(*myMine->myMine[pY][pX]).name() == typeid(Escada).name())
                {
                    myMine->myDrawer->Draw(*myMine->myMiner, SHOW, 1);
                }
            else if(typeid(*myMine->myMine[pY][pX]).name() == typeid(Viga).name())
                {
                    myMine->myDrawer->Draw(*myMine->myMiner, SHOW, 2);
                }
            else
                myMine->myDrawer->Draw(*myMine->myMiner, SHOW);																							//Draws Miner
            myMine->myDrawer->DrawStats(*myMine->myMiner, SHOW);																					//Draw Stats

            tecla = myConsole->getch();

            switch (tecla)
                {
                case ESCAPE:
                    Pause();								//Pauses the game
                    break;
                case _C_:
                    CommandMode();							//Enters Command Mode
                    break;
                case E:
                    myMine->insertLadder(pX, pY);			//Trys to insert Ladder in current position
                    break;
                case V:
                    myMine->insertBeam(pX, pY);				//Trys to insert Beam in current position
                    break;
                case D:
                    myMine->insertDynamite(pX, pY);			//Trys to insert Dynamite in current position
                    break;
                case _X_:
                    myMine->blowDynamite();					//Blows all Dynamite found in the mine
                    ApplyGravity();
                    break;
                case _S_:
                    if (myMine->myMiner->canTeleport())		//Teleport to top of mine if tool is bought/avaiable
                        Teleport(0, 0);
                    break;
                case UP:
                    MoveUp();								//Moves Up
                    break;
                case DOWN:
                    MoveDown();								//Moves Down
                    break;
                case LEFT:
                    MoveLeft();								//Moves Left
                    break;
                case RIGHT:
                    MoveRight();							//Moves Right
                    break;
                }
            if (myMine->myMiner->getCoins() >= 1500)	//Victory Condition
                {
                    Write("Victory! You have a total of 1500 gold and you won ! :)");
                    return;
                }
        }
    Write("Game Over");
    _currentStatus = END;
    return;
}

/* Menu Interface */
void Game::Pause()
{
    myConsole->setTextColor(myConsole->PRETO);
    char tecla;
    myConsole->clrscr();
    myMine->myDrawer->DrawPauseMenu();

    int x = 8, y = 10;
    myConsole->gotoxy(x, y);
    std::cout << '>';
    while (1)
        {
            tecla = myConsole->getch();
            if (tecla == ENTER && y == 10) break;
            if (tecla == ENTER && y == 12) break;
            if (tecla == ENTER && y == 14) break;
            if (tecla != UP && tecla != DOWN) continue;

            myConsole->gotoxy(x, y);
            std::cout << ' ';

            if (tecla == myConsole->CIMA) y -= 2;
            if (tecla == myConsole->BAIXO) y += 2;
            if (y < 10) y = 10;
            if (y > 14) y = 14;
            myConsole->gotoxy(x, y);
            std::cout << '>';
        }
    switch (y)
        {
        case RESUME_GAME:
            break;
        case SOUND_OPTIONS:
            SoundOptions();
            break;
        case SAVE_GAME: //Suposed EXIT_GAME Coordinate # Y-14
            myMine->myMiner->ResetStats();
            Start();
            break;
        }
}
void Game::SoundOptions()
{
    myConsole->clrscr();
    myConsole->gotoxy(14, 2);
    std::cout << " ---Sound Options---";
    myConsole->gotoxy(10, 8);
    std::cout << "** Choose an option **";
    myConsole->gotoxy(10, 10);
    std::cout << "ON";
    myConsole->gotoxy(10, 12);
    std::cout << "OFF";
    myConsole->gotoxy(10, 14);
    std::cout << "Back";

    char tecla;

    int x = 8, y = 10;
    myConsole->gotoxy(x, y);
    std::cout << '>';
    while (1)
        {
            tecla = myConsole->getch();
            if (tecla == ENTER && y == 10) break;
            if (tecla == ENTER && y == 12) break;
            if (tecla == ENTER && y == 14) break;
            if (tecla != UP && tecla != DOWN) continue;

            myConsole->gotoxy(x, y);
            std::cout << ' ';

            if (tecla == myConsole->CIMA) y -= 2;
            if (tecla == myConsole->BAIXO) y += 2;
            if (y < 10) y = 10;
            if (y > 14) y = 14;
            myConsole->gotoxy(x, y);
            std::cout << '>';
        }
    switch (y)
        {
        case UNMUTE:
            PlayTheme();
            break;
        case MUTE:
            StopMusic();
            break;
        case SAVE_GAME: //Suposed EXIT_GAME Coordinate # Y-14
            break;
        }
    Pause();
}
void Game::CommandMode()
{
    std::string read = "m"; //User input/command
    bool valid = false; //Boolean to check if command exists/is valid
    int action = 0;

    myConsole->clrscr();

    if (pY == 0) //If miner is on surface / top of the mine
        myMine->myMiner->ReachSurface(); //Sells all ores and resets energy

    while (read != "j")
        {
            myConsole->gotoxy(2, 2);
            std::cout << "[COMMAND MODE]";
            myConsole->gotoxy(0, 4);
            std::cout << "Command : ____________________";
            myConsole->gotoxy(10, 4);
            std::getline(std::cin, read);

            std::istringstream iss(read);
            std::istringstream countstream(read);
            std::string command;
            std::string params[5];

            int count = 0;

            do //Counts number of arguments and stores it in 'count'
                {
                    std::string counter;
                    countstream >> counter;
                    count++;
                }
            while (countstream);
            count--;

            iss >> command;


            for (int i = 0; i< NUM_COMMANDS; i++) //Runs the validCommands array
                {
                    if (command.compare(validCommands[i][0]) == 0) //if command comparison returns 0 (exists), then valid var is set to true
                        {
                            valid = true;
                            action = i;
                            break;
                        }
                }

            if (valid == false) //command doesnt exist
                {
                    myConsole->clrscr();
                    myConsole->gotoxy(2, 2);
                    std::cout << "[COMMAND MODE]";
                    myConsole->gotoxy(0, 4);
                    std::cout << "Command : ____________________";
                    myConsole->gotoxy(0, 6);
                    std::cout << "[GAME] -> '" << read << "' not found.";
                }
            else //Command exists, procede to specific command action
                {
                    valid = false;
                    myConsole->clrscr();
                    myConsole->gotoxy(2, 2);
                    std::cout << "[COMMAND MODE]";
                    myConsole->gotoxy(0, 4);
                    std::cout << "Command : ____________________";
                    myConsole->gotoxy(0, 6);
                    std::cout << "[GAME] -> ";
                    switch (action)
                        {
                        case 0: //BuyTool
                            if (count == atoi(validCommands[action][1].c_str()))
                                {
                                    for (int i = 0; i < atoi(validCommands[action][1].c_str()) - 1; i++)
                                        {
                                            iss >> params[i];
                                        }
                                    if (myMine->myMiner->getY() == 0)
                                        {
                                            this->BuyTool(params[0]);
                                            break;
                                        }
                                    else
                                        {
                                            std::cout << "You have to be on surface to use shop!" << std::endl;
                                        }
                                    break;
                                }
                            else
                                {
                                    std::cout << std::endl << std::endl << "Invalid argument number!" << std::endl;
                                    break;
                                }
                        case 1: //CreateBlock
                            if (count == atoi(validCommands[action][1].c_str()))
                                {
                                    for (int i = 0; i < atoi(validCommands[action][1].c_str()) - 1; i++)
                                        {
                                            iss >> params[i];
                                        }
                                    CreateBlock(atoi(params[0].c_str()), atoi(params[1].c_str()), atoi(params[2].c_str()));
                                    std::cout << "Block created successfully!" << std::endl;
                                    break;
                                }
                            else
                                {
                                    std::cout << std::endl << std::endl << "Invalid argument number!" << std::endl;
                                    break;
                                }
                        case 2: //Teleport
                            if (count == atoi(validCommands[action][1].c_str()))
                                {
                                    for (int i = 0; i < atoi(validCommands[action][1].c_str()) - 1; i++)
                                        {
                                            iss >> params[i];
                                        }
                                    Teleport(atoi(params[0].c_str()), atoi(params[1].c_str()));
                                    return;
                                    break;
                                }
                            else
                                {
                                    std::cout << std::endl << std::endl << "Invalid argument number!" << std::endl;
                                    break;
                                }
                        case 3: //SetCoins
                            if (count == atoi(validCommands[action][1].c_str()))
                                {
                                    for (int i = 0; i < atoi(validCommands[action][1].c_str()) - 1; i++)
                                        {
                                            iss >> params[i];
                                        }
                                    myMine->myMiner->setCoins(atoi(params[0].c_str()));
                                    std::cout << "Coins set successfully!" << std::endl;
                                    break;
                                }
                            else
                                {
                                    std::cout << std::endl << std::endl << "Invalid argument number!" << std::endl;
                                    break;
                                }
                            break;
                        case 4: //SetEnergy
                            if (count == atoi(validCommands[action][1].c_str()))
                                {
                                    for (int i = 0; i < atoi(validCommands[action][1].c_str()) - 1; i++)
                                        {
                                            iss >> params[i];
                                        }
                                    myMine->myMiner->setEnergyLevel(atoi(params[0].c_str()));
                                    std::cout << "Energy set successfully!" << std::endl;
                                    break;
                                }
                            else
                                {
                                    std::cout << std::endl << std::endl << "Invalid argument number!" << std::endl;
                                    break;
                                }
                            break;
                        case 5: //CreateMine
                            if (count == atoi(validCommands[action][1].c_str()))
                                {
                                    for (int i = 0; i < atoi(validCommands[action][1].c_str()) - 1; i++)
                                        {
                                            iss >> params[i];
                                        }
                                    SaveGame(params[0]);
                                    break;
                                }
                            else
                                {
                                    std::cout << std::endl << std::endl << "Invalid argument number!" << std::endl;
                                    break;
                                }
                            break;
                        case 6: //LoadMine
                            if (count == atoi(validCommands[action][1].c_str()))
                                {
                                    for (int i = 0; i < atoi(validCommands[action][1].c_str()) - 1; i++)
                                        {
                                            iss >> params[i];
                                        }
                                    LoadGame(params[0]);
                                    break;
                                }
                            else
                                {
                                    std::cout << std::endl << std::endl << "Invalid argument number!" << std::endl;
                                    break;
                                }
                            break;
                        case 7: //CopyMine
                            if (count == atoi(validCommands[action][1].c_str()))
                                {
                                    for (int i = 0; i < atoi(validCommands[action][1].c_str()) - 1; i++)
                                        {
                                            iss >> params[i];
                                        }

                                    std::ifstream  src("Saves/" + params[0] + ".gem");
                                    std::ofstream  dst("Saves/" + params[1] + ".gem");

                                    if (!src)
                                        {
                                            std::cout << "Source file doesnt exist!";
                                            myConsole->getch();
                                            break;
                                        }
                                    else if (dst)
                                        {
                                            std::cout << "Destination file exist!";
                                            myConsole->getch();
                                            break;
                                        }
                                    else
                                        {
                                            dst << src.rdbuf();

                                            dst.close();
                                            src.close();

                                            std::cout << "Copy was successfull!" << std::endl;
                                            break;
                                        }
                                }
                            else
                                {
                                    std::cout << std::endl << std::endl << "Invalid argument number!" << std::endl;
                                    break;
                                }
                            break;
                        case 8: //Return to Game
                            myConsole->clrscr();
                            exit(0);
                            break;
                        case 9: //Exit Game
                            myConsole->clrscr();
                            return;
                            break;
                        case 10: //Teleport
                            if (count != atoi(validCommands[action][1].c_str()))
                                {
                                    std::cout << std::endl << std::endl << "Invalid argument number!" << std::endl;
                                    break;
                                }
                            for (int i = 0; i < NUM_UTENSILIOS; i++)
                                {
                                    std::cout << myUtensilios[i].getName() << " - " << myUtensilios[i].getCost() << std::endl;
                                }
                            break;
                        }
                }
        }
    myConsole->clrscr();
    return;
}
void Game::BuyTool(std::string toolName) //TODO: Comments
{
    bool found = false;
    int i = 0;
    for (i = 0; i < NUM_UTENSILIOS; i++)
        {
            if (myUtensilios[i].getName().compare(toolName.c_str()) == 0)
                {
                    break;
                }
            if (i < NUM_UTENSILIOS)
                {
                    std::cout << "Tool non-existant!" << std::endl;
                    myConsole->getch();
                    return;
                }
        }

    if (myMine->myMiner->getCoins() >= myUtensilios[i].getCost())
        {
            myMine->myMiner->setCoins(myMine->myMiner->getCoins() - myUtensilios[i].getCost());

            switch (i)
                {
                case 0: //Picareta
                    std::cout << "Tool already bought!";
                    myMine->myMiner->setGoldCount(myMine->myMiner->getGoldCount() + myUtensilios[i].getCost());
                    myConsole->getch();
                    return;
                    break;
                case 1: //PicaretaAutomatica
                    switch (myMine->myMiner->getPickaxeLevel())
                        {
                        case 1:
                            myMine->myMiner->setPickaxeLevel(2);
                            break;
                        default:
                            std::cout << "Tool already bought!";
                            myMine->myMiner->setGoldCount(myMine->myMiner->getGoldCount() + myUtensilios[i].getCost());
                            myConsole->getch();
                            return;
                        }
                    break;
                case 2: //MarteloPneumatico
                    switch (myMine->myMiner->getPickaxeLevel())
                        {
                        case 2:
                            myMine->myMiner->setPickaxeLevel(3);
                            break;
                        default:
                            std::cout << "Tool already bought!";
                            myMine->myMiner->setGoldCount(myMine->myMiner->getGoldCount() + myUtensilios[i].getCost());
                            myConsole->getch();
                            return;
                        }
                    break;
                case 3: //Mochila
                    std::cout << "Tool already bought!";
                    myMine->myMiner->setGoldCount(myMine->myMiner->getGoldCount() + myUtensilios[i].getCost());
                    myConsole->getch();
                    return;
                    break;
                case 4: //MochilaPro
                    switch (myMine->myMiner->getBackpackLevel())
                        {
                        case 1:
                            myMine->myMiner->setBagpackLevel(2);
                            break;
                        default:
                            std::cout << "Tool already bought!";
                            myMine->myMiner->setGoldCount(myMine->myMiner->getGoldCount() + myUtensilios[i].getCost());
                            myConsole->getch();
                            return;
                        }
                    break;
                case 5: //MochilaHeavyDuty
                    switch (myMine->myMiner->getBackpackLevel())
                        {
                        case 2:
                            myMine->myMiner->setBagpackLevel(3);
                            break;
                        default:
                            std::cout << "Tool already bought!";
                            myMine->myMiner->setGoldCount(myMine->myMiner->getGoldCount() + myUtensilios[i].getCost());
                            myConsole->getch();
                            return;
                        }
                    break;
                case 6: //Isqueiro
                    std::cout << "Tool already bought!";
                    myMine->myMiner->setGoldCount(myMine->myMiner->getGoldCount() + myUtensilios[i].getCost());
                    myConsole->getch();
                    return;
                    break;
                case 7: //Lanterna
                    switch (myMine->myMiner->getLightLevel())
                        {
                        case 1:
                            myMine->myMiner->setLightLevel(2);
                            break;
                        default:
                            std::cout << "Tool already bought!";
                            myMine->myMiner->setGoldCount(myMine->myMiner->getGoldCount() + myUtensilios[i].getCost());
                            myConsole->getch();
                            return;
                        }
                    break;
                case 8: //Holofote
                    switch (myMine->myMiner->getLightLevel())
                        {
                        case 2:
                            myMine->myMiner->setLightLevel(3);
                            break;
                        default:
                            std::cout << "Tool already bought!";
                            myMine->myMiner->setGoldCount(myMine->myMiner->getGoldCount() + myUtensilios[i].getCost());
                            myConsole->getch();
                            return;
                        }
                    break;
                case 9: //LataDeAtum
                    std::cout << "Tool already bought!";
                    myMine->myMiner->setGoldCount(myMine->myMiner->getGoldCount() + myUtensilios[i].getCost());
                    myConsole->getch();
                    return;
                    break;
                case 10: //BebidaEnergetica
                    switch (myMine->myMiner->getEnergyRestoreLevel())
                        {
                        case 1:
                            myMine->myMiner->setEnergyRestoreLevel(2);
                            break;
                        default:
                            std::cout << "Tool already bought!";
                            myMine->myMiner->setGoldCount(myMine->myMiner->getGoldCount() + myUtensilios[i].getCost());
                            myConsole->getch();
                            return;
                        }
                    break;
                case 11: //LancheiraCampismo
                    switch (myMine->myMiner->getEnergyRestoreLevel())
                        {
                        case 2:
                            myMine->myMiner->setEnergyRestoreLevel(3);
                            break;
                        default:
                            std::cout << "Tool already bought!";
                            myMine->myMiner->setGoldCount(myMine->myMiner->getGoldCount() + myUtensilios[i].getCost());
                            myConsole->getch();
                            return;
                        }
                    break;
                case 12: //FrigorificoPortatil
                    switch (myMine->myMiner->getEnergyRestoreLevel())
                        {
                        case 3:
                            myMine->myMiner->setEnergyRestoreLevel(4);
                            break;
                        default:
                            std::cout << "Tool already bought!";
                            myMine->myMiner->setGoldCount(myMine->myMiner->getGoldCount() + myUtensilios[i].getCost());
                            myConsole->getch();
                            return;
                        }
                    break;
                case 13: //AplicadorEscada
                    myMine->myMiner->setLadderCount(myMine->myMiner->getLadderCount() + 1);
                    break;
                case 14: //AplicadorVigas
                    myMine->myMiner->setBeamCount(myMine->myMiner->getBeamCount() + 1);
                    break;
                case 15: //Paraquedas
                    myMine->myMiner->setParachuteCount(myMine->myMiner->getParachuteCount() + 1);
                    break;
                case 16: //VidaExtra
                    myMine->myMiner->setExtraLiveCount(myMine->myMiner->getExtraLiveCount() + 1);
                    break;
                case 17: //Dynamite
                    myMine->myMiner->setDynamiteCount(myMine->myMiner->getDynamiteCount() + 1);
                    break;
                case 18: //Teleport
                    if (myMine->myMiner->canTeleport())
                        {
                            std::cout << "Tool already bought!";
                            myMine->myMiner->setGoldCount(myMine->myMiner->getGoldCount() + myUtensilios[i].getCost());
                            myConsole->getch();
                            return;
                        }
                    else
                        myMine->myMiner->setTeleport(true);
                    break;
                default:
                    break;
                }

            std::cout << myUtensilios[i].getName() << " bought successfully with " << myUtensilios[i].getCost() << " coins." << std::endl;
            myConsole->getch();
            return;
        }
    else
        {
            std::cout << "Not enough coins!" << std::endl;
            myConsole->getch();
            return;
        }
    return;

}
void Game::CreateBlock(int blockType, int X, int Y)
{
    if (blockType > 0 && blockType < 13 && X <= myMine->getLinhas() && Y <= myMine->getColunas())
        {
            switch (blockType)
                {
                case 1:
                    myMine->myMine[Y][X] = new Pedra(X, Y);
                    break;
                case 2:
                    myMine->myMine[Y][X] = new TerrenoMole(X, Y);
                    break;
                case 3:
                    myMine->myMine[Y][X] = new TerrenoDuro(X, Y);
                    break;
                case 4:
                    myMine->myMine[Y][X] = new TerraCAluminio(X, Y);
                    break;
                case 5:
                    myMine->myMine[Y][X] = new TerraCCarvao(X, Y);
                    break;
                case 6:
                    myMine->myMine[Y][X] = new TerraCFerro(X, Y);
                    break;
                case 7:
                    myMine->myMine[Y][X] = new TerraCOuro(X, Y);
                    break;
                case 8:
                    myMine->myMine[Y][X] = new TerraCDiamante(X, Y);
                    break;
                case 9:
                    myMine->myMine[Y][X] = new TerraCFrango(X, Y);
                    break;
                case 10:
                    myMine->myMine[Y][X] = new Escada(X, Y);
                    break;
                case 11:
                    myMine->myMine[Y][X] = new Viga(X, Y);
                    break;
                case 12:
                    myMine->myMine[Y][X] = new Vazio(X, Y);
                    break;
                }
        }
    else
        {
            std::cout << "Coordenadas invalidas!" << std::endl;
            myConsole->getch();
        }
}
void Game::Teleport(int X, int Y)
{
    if (X >= 0 && X <= myMine->getLinhas() && Y >= 0 && Y <= myMine->getColunas())
        {
            myMine->myMine[X][Y] = new Vazio(X, Y);
            myMine->myMiner->Move(X, Y);
            pX = X;
            pY = Y;
        }
    else
        {
            std::cout << "Coordenadas invalidas!" << std::endl;
            myConsole->getch();
        }
}

/* Sound */
void Game::PlayIntro()
{
    PlaySound(TEXT("Data/intro.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
}
void Game::PlayTheme()
{
    PlaySound(TEXT("Data/theme.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
}
void Game::PlayMine()
{
    PlaySound(TEXT("Data/mine.wav"), NULL, SND_ASYNC | SND_FILENAME);
}
void Game::PlayFalling()
{
    PlaySound(TEXT("Data/falling.wav"), NULL, SND_ASYNC | SND_FILENAME);
}
void Game::StopMusic()
{
    PlaySound(NULL, 0, 0);
}

/* Movement Handling*/
void Game::ApplyGravity()
{
    if (typeid(*myMine->myMine[pY + 1][pX]).name() == typeid(Vazio).name()) //Falling
        {
            int t = myMine->myMine[pY + 1][pX]->getY();
            int count = 0; //num of blocks felt
            while (typeid(*myMine->myMine[pY + 1][pX]).name() == typeid(Vazio).name())
                {
                    if (t == myMine->getLinhas() - 1)
                        break;
                    pY += 1;
                    (pY >= myMine->getLinhas() - 1 ? pY = myMine->getLinhas() - 1 : pY = pY); //Bottom Bounding
                    myMine->myDrawer->Draw(*myMine->myMiner, REMOVE);
                    myMine->myMiner->setCoordinates(pX, pY);
                    t++;
                    count++;
                }
            if (count >= 2) //If fell 2 blocks or more
                {
                    if (myMine->myMiner->getParachuteCount() > 0) //if has parachute
                        {
                            myMine->myMiner->setParachuteCount(myMine->myMiner->getParachuteCount() - 1);
                        }
                    else
                        {
                            PlayFalling();
                            myMine->myMiner->setEnergyLevel(myMine->myMiner->getEnergyLevel() - (10 * (count - 1)));
                        }
                }
        }
}
void Game::MoveUp()
{
    myMine->Rockslide();

    if ((pY - 1) >= 0) //TopBouding
        if (typeid(*myMine->myMine[pY - 1][pX]).name() == typeid(Escada).name() || (pY - 1) == 0)
            {
                pY -= 1; //Move 1 position UP
                if (pX - 3 > 0) //UP
                    {
                        offSetX--;
                    }
                else
                    {
                        myMine->RemoveBlock(pX, pY, UP);
                        myMine->myDrawer->Draw(*myMine->myMiner, REMOVE);
                        myMine->myMiner->Move(pX, pY);
                        myMine->myMiner->Move(pX, pY);
                    }
            }
    if (pY == 0) myMine->myMiner->ReachSurface();
}
void Game::MoveDown()
{
    myMine->Rockslide();
    if (typeid(*myMine->myMine[pY + 1][pX]).name() == typeid(Vazio).name()) //Falling
        {
            ApplyGravity();
        }
    else //Move Down
        {
            pY += 1; //Move 1 position DOWN
            (pY >= myMine->getLinhas() - 1 ? pY = myMine->getLinhas() - 1 : pY = pY); //Bottom Bounding
            myMine->RemoveBlock(pX, pY, DOWN);
            myMine->myDrawer->Draw(*myMine->myMiner, REMOVE);
            myMine->myMiner->Move(pX, pY);
        }

}
void Game::MoveLeft()
{
    myMine->Rockslide();
    pX -= 1; //Move 1 position LEFT
    if (pX < 0)
        {
            pX++;
            myMine->myMiner->Move(pX, pY);
            myMine->myMiner->setEnergyLevel(myMine->myMiner->getEnergyLevel() + 1);
            return;
        }
    else
        {
            myMine->RemoveBlock(pX, pY, LEFT);
            myMine->myDrawer->Draw(*myMine->myMiner, REMOVE);
            myMine->myMiner->Move(pX, pY);

        }

    ApplyGravity();

}
void Game::MoveRight()
{
    myMine->Rockslide();
    pX += 1; //Move 1 position RIGHT
    if (pX > myMine->getColunas() - 1)
        {
            pX--;
            myMine->myMiner->Move(pX, pY);
            myMine->myMiner->setEnergyLevel(myMine->myMiner->getEnergyLevel() + 1);
            return;
        }
    else
        {
            myMine->RemoveBlock(pX, pY, LEFT);
            myMine->myDrawer->Draw(*myMine->myMiner, REMOVE);
            myMine->myMiner->Move(pX, pY);
        }

    ApplyGravity();

}

/* Gets */
int Game::Status() const
{
    return _currentStatus;
}

/* System Funcionts */
const std::string Game::currentDate()
{
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%d-%m-%Y", &tstruct);
    return buf;
}
void Game::Write(std::string input)
{
    myConsole->clrscr();
    myConsole->gotoxy(10, 2);
    std::cout << input << std::endl;
    myConsole->getch();
}
std::string Game::GetLoadFilename(int Index)
{
    char ch[260];
    char DefChar = ' ';
    bool H = true;
    wchar_t* savesLocation = L"Saves/*.gem";

    WIN32_FIND_DATA FindFileData;
    HANDLE hFind;
    hFind = FindFirstFile(savesLocation, &FindFileData);

    if (hFind != INVALID_HANDLE_VALUE)
        {
            for (int f = 1; f < Index; f++)
                {
                    FindNextFile(hFind, &FindFileData);
                }
        }

    WideCharToMultiByte(CP_ACP, 0, FindFileData.cFileName, -1, ch, 260, &DefChar, NULL);

    return ch;
}
