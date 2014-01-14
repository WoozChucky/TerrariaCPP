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
    { "m", "1" }, //m
    { "save", "2" }, //save filename
    { "load", "2" } //load filename
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
    offSetX = -3;
    offSetY = -3;
    activeMines = 1;
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

    if (Difficulty < 0 || Difficulty > 3)
        {
            std::cout << "Invalid difficulty!" << std::endl;
            return;
        }

    switch (Difficulty)
        {
        case 1:
            LoadUtensilios(myUtensilios, 1); //Loads tools into myUtensilios's object array
            break;
        case 2:
            LoadUtensilios(myUtensilios, 2); //Loads tools into myUtensilios's object array
            break;
        case 3:
            LoadUtensilios(myUtensilios, 3); //Loads tools into myUtensilios's object array
            break;
        }

    this->myConsole->clrscr();
    //myMine =
    currentMine = 0;
    minesGrid = (Mine **)malloc(sizeof(Mine)*activeMines + 1);
    minesGrid[currentMine] = new Mine(Name, Rows, Columns); //Creates new mine with size (rows, columns)
    StopMusic();
    PlayTheme();

    Play(0, 0, 0, 0);
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
    infile >> data >> data >> data;//Name
    std::string name = data;
    infile >> data >> data >> value; //Columns
    int colunas = value;
    infile >> data >> data >> value; //Rows
    int linhas = value;
    infile >> data >> data >> value; //Vision
    int vision = value;

    if (activeMines == 1)
        {
            minesGrid = (Mine **)malloc(sizeof(Mine)*activeMines + 1);
        }
    else
        {
            minesGrid = (Mine **)realloc(minesGrid, sizeof(Mine)* activeMines + 1);
        }

    minesGrid[currentMine] = new Mine(name, linhas, colunas); //Creates new mine with size (rows, columns)
    minesGrid[currentMine]->setVision(vision);

    infile >> data; //[MINER]
    infile >> data >> data >> value; // Coins
    minesGrid[currentMine]->myMiner->setCoins(value);
    infile >> data >> data >> value; // Energy
    minesGrid[currentMine]->myMiner->setEnergyLevel(value);
    infile >> data >> data >> value; // X
    minesGrid[currentMine]->myMiner->setCoordinates(value, 0);
    infile >> data >> data >> value; // Y
    minesGrid[currentMine]->myMiner->setCoordinates(minesGrid[currentMine]->myMiner->getX(), value);
    infile >> data >> data >> value; // Capacity
    minesGrid[currentMine]->myMiner->setCapacity(value);
    infile >> data >> data >> value; // Pickaxe
    minesGrid[currentMine]->myMiner->setPickaxeLevel(value);
    infile >> data >> data >> value; // EnergyRestore
    minesGrid[currentMine]->myMiner->setEnergyRestoreLevel(value);
    infile >> data >> data >> value; // Bagpack
    minesGrid[currentMine]->myMiner->setBagpackLevel(value);
    infile >> data >> data >> value; // LightLevel
    minesGrid[currentMine]->myMiner->setLightLevel(value);
    infile >> data >> data >> value; // Parachute
    minesGrid[currentMine]->myMiner->setParachuteCount(value);
    infile >> data >> data >> value; // Ladder
    minesGrid[currentMine]->myMiner->setLadderCount(value);
    infile >> data >> data >> value; // Beam
    minesGrid[currentMine]->myMiner->setBeamCount(value);
    infile >> data >> data >> value; // ExtraLive
    minesGrid[currentMine]->myMiner->setExtraLiveCount(value);
    infile >> data >> data >> value; // Dynamite
    minesGrid[currentMine]->myMiner->setDynamiteCount(value);
    infile >> data >> data >> value; // Aluminium
    minesGrid[currentMine]->myMiner->setAluminiumCount(value);
    infile >> data >> data >> value; // Charcoal
    minesGrid[currentMine]->myMiner->setCharcoalCount(value);
    infile >> data >> data >> value; // Diamond
    minesGrid[currentMine]->myMiner->setDiamondCount(value);
    infile >> data >> data >> value; // Iron
    minesGrid[currentMine]->myMiner->setIronCount(value);
    infile >> data >> data >> value; // Gold
    minesGrid[currentMine]->myMiner->setGoldCount(value);

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
                            minesGrid[currentMine]->myMine[r][c] = new Dynamite(x, y);
                            minesGrid[currentMine]->myMine[r][c]->setTicks(ticks);
                        }
                    else if(className == "Escada")
                        {
                            minesGrid[currentMine]->myMine[r][c] = new Escada(x, y);
                            minesGrid[currentMine]->myMine[r][c]->setTicks(ticks);
                        }
                    else if (className == "Pedra")
                        {
                            minesGrid[currentMine]->myMine[r][c] = new Pedra(x, y);
                            minesGrid[currentMine]->myMine[r][c]->setTicks(ticks);
                        }
                    else if (className == "TerraCAluminio")
                        {
                            minesGrid[currentMine]->myMine[r][c] = new TerraCAluminio(x, y);
                            minesGrid[currentMine]->myMine[r][c]->setTicks(ticks);
                        }
                    else if (className == "TerraCCarvao")
                        {
                            minesGrid[currentMine]->myMine[r][c] = new TerraCCarvao(x, y);
                            minesGrid[currentMine]->myMine[r][c]->setTicks(ticks);
                        }
                    else if (className == "TerraCDiamante")
                        {
                            minesGrid[currentMine]->myMine[r][c] = new TerraCDiamante(x, y);
                            minesGrid[currentMine]->myMine[r][c]->setTicks(ticks);
                        }
                    else if (className == "TerraCFerro")
                        {
                            minesGrid[currentMine]->myMine[r][c] = new TerraCFerro(x, y);
                            minesGrid[currentMine]->myMine[r][c]->setTicks(ticks);
                        }
                    else if (className == "TerraCFrango")
                        {
                            minesGrid[currentMine]->myMine[r][c] = new TerraCFrango(x, y);
                            minesGrid[currentMine]->myMine[r][c]->setTicks(ticks);
                        }
                    else if (className == "TerraCOuro")
                        {
                            minesGrid[currentMine]->myMine[r][c] = new TerraCOuro(x, y);
                            minesGrid[currentMine]->myMine[r][c]->setTicks(ticks);
                        }
                    else if (className == "TerrenoDuro")
                        {
                            minesGrid[currentMine]->myMine[r][c] = new TerrenoDuro(x, y);
                            minesGrid[currentMine]->myMine[r][c]->setTicks(ticks);
                        }
                    else if (className == "TerrenoMole")
                        {
                            minesGrid[currentMine]->myMine[r][c] = new TerrenoMole(x, y);
                            minesGrid[currentMine]->myMine[r][c]->setTicks(ticks);
                        }
                    else if (className == "Vazio")
                        {
                            minesGrid[currentMine]->myMine[r][c] = new Vazio(x, y);
                            minesGrid[currentMine]->myMine[r][c]->setTicks(ticks);
                        }
                    else if (className == "Viga")
                        {
                            minesGrid[currentMine]->myMine[r][c] = new Viga(x, y);
                            minesGrid[currentMine]->myMine[r][c]->setTicks(ticks);
                        }
                    else if (className == "TerraCVeneno")
                        {
                            minesGrid[currentMine]->myMine[r][c] = new TerraCVeneno(x, y);
                            minesGrid[currentMine]->myMine[r][c]->setTicks(ticks);
                        }


                }
        }

    Play(minesGrid[currentMine]->myMiner->getX(), minesGrid[currentMine]->myMiner->getY(), minesGrid[currentMine]->getLinhas() / 2 - 3, minesGrid[currentMine]->getColunas() / 2 - 3);


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
    outfile << "Name = " << minesGrid[currentMine]->getName() << std::endl;
    outfile << "Columns = " << minesGrid[currentMine]->getColunas() << std::endl;
    outfile << "Rows = " << minesGrid[currentMine]->getLinhas() << std::endl;
    outfile << "Vision = " << minesGrid[currentMine]->getVision() << std::endl << std::endl;

    outfile << "[MINER]" << std::endl;
    outfile << "Coins = " << minesGrid[currentMine]->myMiner->getCoins() << std::endl;
    outfile << "Energy = " << minesGrid[currentMine]->myMiner->getEnergyLevel() << std::endl;
    outfile << "X = " << minesGrid[currentMine]->myMiner->getX() << std::endl;
    outfile << "Y = " << minesGrid[currentMine]->myMiner->getY() << std::endl;
    outfile << "Capacity = " << minesGrid[currentMine]->myMiner->getCapacity() << std::endl;
    outfile << "PickaxeLevel = " << minesGrid[currentMine]->myMiner->getPickaxeLevel() << std::endl;
    outfile << "EnergyRestoreLevel = " << minesGrid[currentMine]->myMiner->getEnergyRestoreLevel() << std::endl;
    outfile << "BagpackLevel = " << minesGrid[currentMine]->myMiner->getBackpackLevel() << std::endl;
    outfile << "LightLevel = " << minesGrid[currentMine]->myMiner->getLightLevel() << std::endl;
    outfile << "Parachute = " << minesGrid[currentMine]->myMiner->getParachuteCount() << std::endl;
    outfile << "Ladder = " << minesGrid[currentMine]->myMiner->getLadderCount() << std::endl;
    outfile << "Beam = " << minesGrid[currentMine]->myMiner->getBeamCount() << std::endl;
    outfile << "ExtraLive = " << minesGrid[currentMine]->myMiner->getExtraLiveCount() << std::endl;
    outfile << "Dynamite = " << minesGrid[currentMine]->myMiner->getDynamiteCount() << std::endl;
    outfile << "Aluminium = " << minesGrid[currentMine]->myMiner->getAluminumCount() << std::endl;
    outfile << "Charcoal = " << minesGrid[currentMine]->myMiner->getCharcoalCount() << std::endl;
    outfile << "Diamond = " << minesGrid[currentMine]->myMiner->getDiamondCount() << std::endl;
    outfile << "Iron = " << minesGrid[currentMine]->myMiner->getIronCount() << std::endl;
    outfile << "Gold = " << minesGrid[currentMine]->myMiner->getGoldCount() << std::endl << std::endl;

    outfile << "[BLOCKS]" << std::endl;
    for (int r = 0; r < minesGrid[currentMine]->getLinhas(); r++)
        {
            for (int c = 0; c < minesGrid[currentMine]->getColunas(); c++)
                {
                    outfile << "Type = " << typeid(*minesGrid[currentMine]->myMine[r][c]).name() << std::endl;
                    outfile << "Breakeable = " << minesGrid[currentMine]->myMine[r][c]->getBreakeable() << std::endl;
                    outfile << "Ticks = " << minesGrid[currentMine]->myMine[r][c]->getTicks() << std::endl;
                    outfile << "X = " << minesGrid[currentMine]->myMine[r][c]->getX() << std::endl;
                    outfile << "Y = " << minesGrid[currentMine]->myMine[r][c]->getY() << std::endl << std::endl;
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
    minesGrid[currentMine]->myMiner->setCoordinates(pX, pY);

    /* Main cycle of Game */
    while (minesGrid[currentMine]->myMiner->hasLives())
        {
            myConsole->clrscr();
            minesGrid[currentMine]->myDrawer->DrawMine(minesGrid[currentMine]->myMine, *minesGrid[currentMine]->myMiner, vX, vY, minesGrid[currentMine]->getVision(), minesGrid[currentMine]->getColunas(), minesGrid[currentMine]->getLinhas());	//Draws Mine

            if (typeid(*minesGrid[currentMine]->myMine[pY][pX]).name() == typeid(Escada).name())
                {
                    minesGrid[currentMine]->myDrawer->Draw(*minesGrid[currentMine]->myMiner, SHOW, 1);
                }
            else if (typeid(*minesGrid[currentMine]->myMine[pY][pX]).name() == typeid(Viga).name())
                {
                    minesGrid[currentMine]->myDrawer->Draw(*minesGrid[currentMine]->myMiner, SHOW, 2);
                }
            else
                minesGrid[currentMine]->myDrawer->Draw(*minesGrid[currentMine]->myMiner, SHOW);																							//Draws Miner
            minesGrid[currentMine]->myDrawer->DrawStats(*minesGrid[currentMine]->myMiner, SHOW);																					//Draw Stats



            myConsole->gotoxy(14, 36);
            std::cout << "Minas Totais: " << activeMines;
            myConsole->gotoxy(14, 37);
            std::cout << "Nome Mina: " << minesGrid[currentMine]->getName();
            myConsole->gotoxy(14, 38);
            std::cout << "Mina Activa: " << currentMine;



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
                    minesGrid[currentMine]->insertLadder(pX, pY);			//Trys to insert Ladder in current position
                    break;
                case V:
                    minesGrid[currentMine]->insertBeam(pX, pY);				//Trys to insert Beam in current position
                    break;
                case D:
                    minesGrid[currentMine]->insertDynamite(pX, pY);			//Trys to insert Dynamite in current position
                    break;
                case _X_:
                    minesGrid[currentMine]->blowDynamite();					//Blows all Dynamite found in the mine
                    ApplyGravity();
                    break;
                case _S_:
                    if (minesGrid[currentMine]->myMiner->canTeleport())		//Teleport to top of mine if tool is bought/avaiable
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
            if (minesGrid[currentMine]->myMiner->getCoins() >= 1500)	//Victory Condition
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
    minesGrid[currentMine]->myDrawer->DrawPauseMenu();

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
            minesGrid[currentMine]->myMiner->ResetStats();
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
    std::string read; //User input/command
    bool valid = false; //Boolean to check if command exists/is valid
    int action = 0;

    myConsole->clrscr();

    if (pY == 0) //If miner is on surface / top of the mine
        minesGrid[currentMine]->myMiner->ReachSurface(); //Sells all ores and resets energy

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
                                    if (minesGrid[currentMine]->myMiner->getY() == 0)
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
                                    minesGrid[currentMine]->myMiner->setCoins(atoi(params[0].c_str()));
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
                                    minesGrid[currentMine]->myMiner->setEnergyLevel(atoi(params[0].c_str()));
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
                                    //minesGrid = (Mine **)realloc(minesGrid, sizeof(Mine)* activeMines + 1);
                                    minesGrid[activeMines] = new Mine(*minesGrid[currentMine]);
                                    minesGrid[activeMines]->setName(params[0]);
                                    std::cout << "Mine created sucssefully! " << minesGrid[activeMines]->getName() << std::endl;
                                    activeMines++;
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
                                    for (int n = 0; n < activeMines; n++)
                                        {
                                            if (params[0].compare(minesGrid[n]->getName()) == 0)
                                                {
                                                    currentMine = n;
                                                    std::cout << "Mine loaded sucssefully!" << std::endl;
                                                    myConsole->getch();
                                                    return;
                                                }
                                        }
                                    std::cout << "Invalid mine name!" << std::endl;
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

                                    bool test1 = false, test2 = false;
                                    int orig, dest;

                                    for (int n = 0; n < activeMines; n++)
                                        {
                                            if (params[0].compare(minesGrid[n]->getName()) == 0)
                                                {
                                                    test1 = true;
                                                    orig = n;
                                                }
                                            if (params[1].compare(minesGrid[n]->getName()) == 0)
                                                {
                                                    test2 = true;
                                                    dest = n;
                                                }
                                        }

                                    if (test1 && test2)
                                        {
                                            minesGrid[dest] = minesGrid[orig];
                                        }
                                    else
                                        {
                                            std::cout << "Invalid mine names!" << std::endl;
                                            break;
                                        }

                                    std::cout << "Copy was successfull!" << std::endl;
                                    break;

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
                        case 10: //Tools Display
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
                        case 11: //SaveGame
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
                        case 12: //LoadGame
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

    if (minesGrid[currentMine]->myMiner->getCoins() >= myUtensilios[i].getCost())
        {
            minesGrid[currentMine]->myMiner->setCoins(minesGrid[currentMine]->myMiner->getCoins() - myUtensilios[i].getCost());

            switch (i)
                {
                case 0: //Picareta
                    std::cout << "Tool already bought!";
                    minesGrid[currentMine]->myMiner->setGoldCount(minesGrid[currentMine]->myMiner->getGoldCount() + myUtensilios[i].getCost());
                    myConsole->getch();
                    return;
                    break;
                case 1: //PicaretaAutomatica
                    switch (minesGrid[currentMine]->myMiner->getPickaxeLevel())
                        {
                        case 1:
                            minesGrid[currentMine]->myMiner->setPickaxeLevel(2);
                            break;
                        default:
                            std::cout << "Tool already bought!";
                            minesGrid[currentMine]->myMiner->setGoldCount(minesGrid[currentMine]->myMiner->getGoldCount() + myUtensilios[i].getCost());
                            myConsole->getch();
                            return;
                        }
                    break;
                case 2: //MarteloPneumatico
                    switch (minesGrid[currentMine]->myMiner->getPickaxeLevel())
                        {
                        case 2:
                            minesGrid[currentMine]->myMiner->setPickaxeLevel(3);
                            break;
                        default:
                            std::cout << "Tool already bought!";
                            minesGrid[currentMine]->myMiner->setGoldCount(minesGrid[currentMine]->myMiner->getGoldCount() + myUtensilios[i].getCost());
                            myConsole->getch();
                            return;
                        }
                    break;
                case 3: //Mochila
                    std::cout << "Tool already bought!";
                    minesGrid[currentMine]->myMiner->setGoldCount(minesGrid[currentMine]->myMiner->getGoldCount() + myUtensilios[i].getCost());
                    myConsole->getch();
                    return;
                    break;
                case 4: //MochilaPro
                    switch (minesGrid[currentMine]->myMiner->getBackpackLevel())
                        {
                        case 1:
                            minesGrid[currentMine]->myMiner->setBagpackLevel(2);
                            break;
                        default:
                            std::cout << "Tool already bought!";
                            minesGrid[currentMine]->myMiner->setGoldCount(minesGrid[currentMine]->myMiner->getGoldCount() + myUtensilios[i].getCost());
                            myConsole->getch();
                            return;
                        }
                    break;
                case 5: //MochilaHeavyDuty
                    switch (minesGrid[currentMine]->myMiner->getBackpackLevel())
                        {
                        case 2:
                            minesGrid[currentMine]->myMiner->setBagpackLevel(3);
                            break;
                        default:
                            std::cout << "Tool already bought!";
                            minesGrid[currentMine]->myMiner->setGoldCount(minesGrid[currentMine]->myMiner->getGoldCount() + myUtensilios[i].getCost());
                            myConsole->getch();
                            return;
                        }
                    break;
                case 6: //Isqueiro
                    std::cout << "Tool already bought!";
                    minesGrid[currentMine]->myMiner->setGoldCount(minesGrid[currentMine]->myMiner->getGoldCount() + myUtensilios[i].getCost());
                    myConsole->getch();
                    return;
                    break;
                case 7: //Lanterna
                    switch (minesGrid[currentMine]->myMiner->getLightLevel())
                        {
                        case 1:
                            minesGrid[currentMine]->myMiner->setLightLevel(2);
                            minesGrid[currentMine];
                        default:
                            std::cout << "Tool already bought!";
                            minesGrid[currentMine]->myMiner->setGoldCount(minesGrid[currentMine]->myMiner->getGoldCount() + myUtensilios[i].getCost());
                            myConsole->getch();
                            return;
                        }
                    break;
                case 8: //Holofote
                    switch (minesGrid[currentMine]->myMiner->getLightLevel())
                        {
                        case 2:
                            minesGrid[currentMine]->myMiner->setLightLevel(3);
                            break;
                        default:
                            std::cout << "Tool already bought!";
                            minesGrid[currentMine]->myMiner->setGoldCount(minesGrid[currentMine]->myMiner->getGoldCount() + myUtensilios[i].getCost());
                            myConsole->getch();
                            return;
                        }
                    break;
                case 9: //LataDeAtum
                    std::cout << "Tool already bought!";
                    minesGrid[currentMine]->myMiner->setGoldCount(minesGrid[currentMine]->myMiner->getGoldCount() + myUtensilios[i].getCost());
                    myConsole->getch();
                    return;
                    break;
                case 10: //BebidaEnergetica
                    switch (minesGrid[currentMine]->myMiner->getEnergyRestoreLevel())
                        {
                        case 1:
                            minesGrid[currentMine]->myMiner->setEnergyRestoreLevel(2);
                            break;
                        default:
                            std::cout << "Tool already bought!";
                            minesGrid[currentMine]->myMiner->setGoldCount(minesGrid[currentMine]->myMiner->getGoldCount() + myUtensilios[i].getCost());
                            myConsole->getch();
                            return;
                        }
                    break;
                case 11: //LancheiraCampismo
                    switch (minesGrid[currentMine]->myMiner->getEnergyRestoreLevel())
                        {
                        case 2:
                            minesGrid[currentMine]->myMiner->setEnergyRestoreLevel(3);
                            break;
                        default:
                            std::cout << "Tool already bought!";
                            minesGrid[currentMine]->myMiner->setGoldCount(minesGrid[currentMine]->myMiner->getGoldCount() + myUtensilios[i].getCost());
                            myConsole->getch();
                            return;
                        }
                    break;
                case 12: //FrigorificoPortatil
                    switch (minesGrid[currentMine]->myMiner->getEnergyRestoreLevel())
                        {
                        case 3:
                            minesGrid[currentMine]->myMiner->setEnergyRestoreLevel(4);
                            break;
                        default:
                            std::cout << "Tool already bought!";
                            minesGrid[currentMine]->myMiner->setGoldCount(minesGrid[currentMine]->myMiner->getGoldCount() + myUtensilios[i].getCost());
                            myConsole->getch();
                            return;
                        }
                    break;
                case 13: //AplicadorEscada
                    minesGrid[currentMine]->myMiner->setLadderCount(minesGrid[currentMine]->myMiner->getLadderCount() + 1);
                    break;
                case 14: //AplicadorVigas
                    minesGrid[currentMine]->myMiner->setBeamCount(minesGrid[currentMine]->myMiner->getBeamCount() + 1);
                    break;
                case 15: //Paraquedas
                    minesGrid[currentMine]->myMiner->setParachuteCount(minesGrid[currentMine]->myMiner->getParachuteCount() + 1);
                    break;
                case 16: //VidaExtra
                    minesGrid[currentMine]->myMiner->setExtraLiveCount(minesGrid[currentMine]->myMiner->getExtraLiveCount() + 1);
                    break;
                case 17: //Dynamite
                    minesGrid[currentMine]->myMiner->setDynamiteCount(minesGrid[currentMine]->myMiner->getDynamiteCount() + 1);
                    break;
                case 18: //Teleport
                    if (minesGrid[currentMine]->myMiner->canTeleport())
                        {
                            std::cout << "Tool already bought!";
                            minesGrid[currentMine]->myMiner->setGoldCount(minesGrid[currentMine]->myMiner->getGoldCount() + myUtensilios[i].getCost());
                            myConsole->getch();
                            return;
                        }
                    else
                        minesGrid[currentMine]->myMiner->setTeleport(true);
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
    if (blockType > 0 && blockType < 13 && X <= minesGrid[currentMine]->getLinhas() && Y <= minesGrid[currentMine]->getColunas())
        {
            switch (blockType)
                {
                case 1:
                    minesGrid[currentMine]->myMine[Y][X] = new Pedra(X, Y);
                    break;
                case 2:
                    minesGrid[currentMine]->myMine[Y][X] = new TerrenoMole(X, Y);
                    break;
                case 3:
                    minesGrid[currentMine]->myMine[Y][X] = new TerrenoDuro(X, Y);
                    break;
                case 4:
                    minesGrid[currentMine]->myMine[Y][X] = new TerraCAluminio(X, Y);
                    break;
                case 5:
                    minesGrid[currentMine]->myMine[Y][X] = new TerraCCarvao(X, Y);
                    break;
                case 6:
                    minesGrid[currentMine]->myMine[Y][X] = new TerraCFerro(X, Y);
                    break;
                case 7:
                    minesGrid[currentMine]->myMine[Y][X] = new TerraCOuro(X, Y);
                    break;
                case 8:
                    minesGrid[currentMine]->myMine[Y][X] = new TerraCDiamante(X, Y);
                    break;
                case 9:
                    minesGrid[currentMine]->myMine[Y][X] = new TerraCFrango(X, Y);
                    break;
                case 10:
                    minesGrid[currentMine]->myMine[Y][X] = new Escada(X, Y);
                    break;
                case 11:
                    minesGrid[currentMine]->myMine[Y][X] = new Viga(X, Y);
                    break;
                case 12:
                    minesGrid[currentMine]->myMine[Y][X] = new Vazio(X, Y);
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
    if (X >= 0 && X <= minesGrid[currentMine]->getLinhas() && Y >= 0 && Y <= minesGrid[currentMine]->getColunas())
        {
            minesGrid[currentMine]->myMine[X][Y] = new Vazio(X, Y);
            minesGrid[currentMine]->myMiner->Move(X, Y);
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
    if (typeid(*minesGrid[currentMine]->myMine[pY + 1][pX]).name() == typeid(Vazio).name()) //Falling
        {
            int t = minesGrid[currentMine]->myMine[pY + 1][pX]->getY();
            int count = 0; //num of blocks felt
            while (typeid(*minesGrid[currentMine]->myMine[pY + 1][pX]).name() == typeid(Vazio).name())
                {
                    if (t == minesGrid[currentMine]->getLinhas() - 1)
                        break;
                    pY += 1;
                    (pY >= minesGrid[currentMine]->getLinhas() - 1 ? pY = minesGrid[currentMine]->getLinhas() - 1 : pY = pY); //Bottom Bounding
                    minesGrid[currentMine]->myDrawer->Draw(*minesGrid[currentMine]->myMiner, REMOVE);
                    minesGrid[currentMine]->myMiner->setCoordinates(pX, pY);
                    t++;
                    count++;
                }
            if (count >= 2) //If fell 2 blocks or more
                {
                    if (minesGrid[currentMine]->myMiner->getParachuteCount() > 0) //if has parachute
                        {
                            minesGrid[currentMine]->myMiner->setParachuteCount(minesGrid[currentMine]->myMiner->getParachuteCount() - 1);
                        }
                    else
                        {
                            PlayFalling();
                            minesGrid[currentMine]->myMiner->setEnergyLevel(minesGrid[currentMine]->myMiner->getEnergyLevel() - (10 * (count - 1)));
                        }
                }
        }
}
void Game::MoveUp()
{
    minesGrid[currentMine]->Rockslide();

    if (pX - 3 > 0) //UP
        {
            offSetX--;
        }
    else
        {
            minesGrid[currentMine]->myMiner->setCoordinates(pX, pY);
        }

    if ((pY - 1) >= 0) //TopBouding
        if (typeid(*minesGrid[currentMine]->myMine[pY - 1][pX]).name() == typeid(Escada).name() || (pY - 1) == 0)
            {

                pY -= 1; //Move 1 position UP
                minesGrid[currentMine]->RemoveBlock(pX, pY, UP);
                minesGrid[currentMine]->myDrawer->Draw(*minesGrid[currentMine]->myMiner, REMOVE);
                minesGrid[currentMine]->myMiner->Move(pX, pY);
                minesGrid[currentMine]->myMiner->Move(pX, pY);
            }
    if (pY == 0) minesGrid[currentMine]->myMiner->ReachSurface();
}
void Game::MoveDown()
{
    minesGrid[currentMine]->Rockslide();
    if (typeid(*minesGrid[currentMine]->myMine[pY + 1][pX]).name() == typeid(Vazio).name()) //Falling
        {
            ApplyGravity();
        }
    else //Move Down
        {
            pY += 1; //Move 1 position DOWN
            (pY >= minesGrid[currentMine]->getLinhas() - 1 ? pY = minesGrid[currentMine]->getLinhas() - 1 : pY = pY); //Bottom Bounding
            minesGrid[currentMine]->RemoveBlock(pX, pY, DOWN);
            minesGrid[currentMine]->myDrawer->Draw(*minesGrid[currentMine]->myMiner, REMOVE);
            minesGrid[currentMine]->myMiner->Move(pX, pY);
        }

}
void Game::MoveLeft()
{
    minesGrid[currentMine]->Rockslide();
    pX -= 1; //Move 1 position LEFT
    if (pX < 0)
        {
            pX++;
            minesGrid[currentMine]->myMiner->Move(pX, pY);
            minesGrid[currentMine]->myMiner->setEnergyLevel(minesGrid[currentMine]->myMiner->getEnergyLevel() + 1);
            return;
        }
    else
        {
            minesGrid[currentMine]->RemoveBlock(pX, pY, LEFT);
            minesGrid[currentMine]->myDrawer->Draw(*minesGrid[currentMine]->myMiner, REMOVE);
            minesGrid[currentMine]->myMiner->Move(pX, pY);

        }

    ApplyGravity();

}
void Game::MoveRight()
{
    minesGrid[currentMine]->Rockslide();

    (vX + 1 <= minesGrid[currentMine]->getColunas() - 7 && offSetX == 0) ? vX++ : offSetX++;

    std::cout << "mineX: " << vX;
    std::cout << " offSetX: " << offSetX;

    myConsole->getch();

    pX += 1; //Move 1 position RIGHT
    if (pX > minesGrid[currentMine]->getColunas() - 1)
        {
            pX--;
            minesGrid[currentMine]->myMiner->Move(pX, pY);
            minesGrid[currentMine]->myMiner->setEnergyLevel(minesGrid[currentMine]->myMiner->getEnergyLevel() + 1);
            return;
        }
    else
        {
            minesGrid[currentMine]->RemoveBlock(pX, pY, LEFT);
            minesGrid[currentMine]->myDrawer->Draw(*minesGrid[currentMine]->myMiner, REMOVE);
            minesGrid[currentMine]->myMiner->Move(pX, pY);
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
