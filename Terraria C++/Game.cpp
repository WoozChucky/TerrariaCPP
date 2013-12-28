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

/* General */
Game::Game()
{
    _currentStatus = ACTIVE;
    reader = new INIReader("Data/config.ini");
    if (reader->ParseError() < 0)
        {
            std::cout << "Can't load 'test.ini'\n";
            return;
        }
    myConsole = new Consola();
    //myCommunicatorInterface = new CommunicatorInterface(reader->Get("NETWORKING", "IP", 0).c_str(), reader->Get("NETWORKING", "Port", 0).c_str());
    LoadUtensilios(myUtensilios);
}

void Game::Start()
{
    //PlayIntro();

    char tecla;

    myConsole->setTextColor(myConsole->PRETO);
    myConsole->setBackgroundColor(myConsole->BRANCO_CLARO);
    myConsole->setScreenSize(20, 50);
    myConsole->clrscr();

    this->WriteMainMenu();

    int x = 8, y = 10;
    myConsole->gotoxy(x, y);
    std::cout << '>';
    while (1)
        {
            tecla = myConsole->getch();
            if (tecla == ESCAPE) exit(0);
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
        case NEW_GAME:
            NewGame();
            break;
        case LOAD_GAME:
            LoadGame();
            break;
        case SAVE_GAME: //Suposto EXIT_GAME
            exit(0);
            break;
        }
}

/* Game States */
void Game::NewGame()
{
    int nLinhas, nColunas;
    this->myConsole->clrscr();
    this->myConsole->gotoxy(14, 2);
    std::cout << "Criacao Novo Jogo";
    std::cout << std::endl << "Dimensao da Mina" << std::endl;
    std::cout << "Linhas: ";
    this->myConsole->setTextColor(this->myConsole->VERMELHO_CLARO);
    std::cin >> nLinhas;
    this->myConsole->setTextColor(this->myConsole->AZUL_CLARO);
    std::cout << "Colunas: ";
    this->myConsole->setTextColor(this->myConsole->VERMELHO_CLARO);
    std::cin >> nColunas;
    std::cout << std::endl;

    this->myConsole->clrscr();
    myMine = new Mine(nLinhas, nColunas);

    StopMusic();
    //PlayTheme();

    Play(0, 0, myMine->getLinhas() / 2 - 3, myMine->getColunas() / 2 - 3);
}
void Game::LoadGame()
{
    int numSaves = 0;
    char tecla;
    BOOL H = true;
    wchar_t* savesLocation = L"Saves/*.gem";

    WIN32_FIND_DATA FindFileData;
    HANDLE hFind;
    hFind = FindFirstFile(savesLocation, &FindFileData);

    myConsole->clrscr();

    if (hFind != INVALID_HANDLE_VALUE)
        {
            numSaves++;
            while ((H = FindNextFile(hFind, &FindFileData)) == TRUE)
                numSaves++;
        }

    myConsole->gotoxy(6, 2);
    if (numSaves == 0)
        {
            std::cout << "Erro: ";
            std::cout << "Num saves encontradas = " << numSaves;
            system("pause");
            return;
        }

    std::cout << " -----Saves-----";

    for (int i = 1; i <= numSaves; i++)
        {
            myConsole->gotoxy(4, 4 + (i*2));
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
    std::string data, garbageCollector("");
    std::string filename = GetLoadFilename(nameID);

    std::ifstream infile;
    int value = 0;
    infile.open("Saves/" + filename);


    infile >> data; //Data
    infile >> data; //[MINE]
    infile >> data >> data >> value; //Columns
    int colunas = value;
    infile >> data >> data >> value; //Rows
    int linhas = value;
    infile >> data >> data >> value; //Vision
    int vision = value;

    myMine = new Mine(linhas, colunas);
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


                }
        }

    Play(myMine->myMiner->getX(), myMine->myMiner->getY(), myMine->getLinhas() / 2 - 3, myMine->getColunas() / 2 - 3);


}
void Game::SaveGame()
{
    myConsole->clrscr();
    myConsole->gotoxy(2, 2);

    int i = 0;

    std::string filename = "Saves/miner-save-" + currentDate() + ".gem";

    std::ifstream ifile(filename);
    if (ifile)
        {
            char c;
            srand((unsigned int)time(NULL));
            c = (rand() % 122 + 48);
            i++;
            filename = "Saves/miner-save-" + currentDate() + c + ".gem";
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

    std::cout << "Gravado em " << filename;
    myConsole->getch();
}
void Game::Play(int _pX, int _pY, int _vX, int _vY)
{
    this->myConsole->setScreenBufferSize(7 * 5 + 10, 7 * 5);
    this->myConsole->setScreenSize(7 * 5 + 10, 7 * 5);
    this->myConsole->setTextColor(this->myConsole->PRETO);

    char tecla;
    pX = _pX, pY = _pY; //Player Start Position
    vX = _vX, vY = _vY; //Mine Start Writing Position

    /* Miner Start Position */
    myMine->myMiner->setCoordinates(pX, pY);

    /* Main cycle of Game */
    while (myMine->myMiner->hasLives())
        {
            this->myConsole->clrscr();
            myMine->myDrawer->DrawMine(myMine->myMine, *myMine->myMiner, vX, vY, myMine->getVision(), myMine->getColunas(), myMine->getLinhas());	//Draws Mine
            myMine->myDrawer->Draw(*myMine->myMiner, SHOW);												//Draws Miner
            myMine->myDrawer->DrawStats(*myMine->myMiner, SHOW);										//Draw Stats

            /*char buf[sizeof(int)*3+7];
            _snprintf(buf, sizeof buf, "X: %d", pX);
            myCommunicatorInterface->Send(buf);*/

            tecla = myConsole->getch();

            switch (tecla)
                {
                case ESCAPE:
                    Pause();
                    break;
                case C:
                    CommandMode();
                    break;
                case E:
                    myMine->insertLadder(pX, pY);
                    break;
                case V:
                    myMine->insertBeam(pX, pY);
                    break;
                case D:
                    myMine->insertDynamite(pX, pY);
                    break;
                case _X_:
                    myMine->blowDynamite();
                    break;
                case UP:
                    if ((pY - 1) >= 0)
                        if (typeid(*myMine->myMine[pY - 1][pX]).name() == typeid(Escada).name())
                            {
                                pY -= 1; //Move 1 position UP
                                (pY <= 0 ? pY = 0 : pY = pY); //Top Bounding
                                myMine->RemoveBlock(pX, pY, UP);
                                myMine->myDrawer->Draw(*myMine->myMiner, REMOVE);
                                myMine->myMiner->Move(pX, pY);
                                myMine->myMiner->Move(pX, pY);
                            }
                    break;
                case DOWN:
                    if ((pY + 1) < myMine->getLinhas())
                        {
                            if (typeid(*myMine->myMine[pY + 1][pX]).name() == typeid(Vazio).name())
                                {
                                    while (typeid(*myMine->myMine[pY + 1][pX]).name() == typeid(Vazio).name())
                                        {
                                            PlayFalling();
                                            pY += 1;
                                            (pY >= myMine->getLinhas() - 1 ? pY = myMine->getLinhas() - 1 : pY = pY); //Bottom Bounding
                                            myMine->myMiner->setEnergyLevel(myMine->myMiner->getEnergyLevel() - 5);
                                            myMine->myDrawer->Draw(*myMine->myMiner, REMOVE);
                                            myMine->myMiner->Move(pX, pY);
                                            if ((pY + 1) < myMine->getLinhas())
                                                break;
                                        }
                                }
                            else
                                {
                                    pY += 1; //Move 1 position DOWN
                                    (pY >= myMine->getLinhas() - 1 ? pY = myMine->getLinhas() - 1 : pY = pY); //Bottom Bounding
                                    myMine->RemoveBlock(pX, pY, DOWN);
                                    myMine->myDrawer->Draw(*myMine->myMiner, REMOVE);
                                    myMine->myMiner->Move(pX, pY);
                                }
                        }

                    break;
                case LEFT:
                    pX -= 1; //Move 1 position LEFT
                    (pX <= 0 ? pX = 0 : pX = pX); //Left Bounding
                    myMine->RemoveBlock(pX, pY, LEFT);
                    myMine->myDrawer->Draw(*myMine->myMiner, REMOVE);
                    myMine->myMiner->Move(pX, pY);

                    if ((pY + 1) < myMine->getLinhas())
                        while (typeid(*myMine->myMine[pY + 1][pX]).name() == typeid(Vazio).name())
                            {
                                std::cout << pY;
                                myConsole->getch();
                                PlayFalling();
                                pY += 1;
                                (pY >= myMine->getLinhas() - 1 ? pY = myMine->getLinhas() - 1 : pY = pY); //Bottom Bounding
                                myMine->myDrawer->Draw(*myMine->myMiner, REMOVE);
                                myMine->myMiner->Move(pX, pY);
                                if ((pY + 1) < myMine->getLinhas())
                                    break;
                            }

                    break;
                case RIGHT:
                    pX += 1; //Move 1 position RIGHT
                    (pX >= myMine->getColunas() - 1 ? pX = myMine->getColunas() - 1 : pX = pX); //Right Bounding
                    myMine->RemoveBlock(pX, pY, RIGHT);
                    myMine->myDrawer->Draw(*myMine->myMiner, REMOVE);
                    myMine->myMiner->Move(pX, pY);

                    if ((pY + 1) < myMine->getLinhas())
                        while (typeid(*myMine->myMine[pY + 1][pX]).name() == typeid(Vazio).name())
                            {
                                PlayFalling();
                                pY += 1;
                                (pY >= myMine->getLinhas() - 1 ? pY = myMine->getLinhas() - 1 : pY = pY); //Bottom Bounding
                                myMine->myDrawer->Draw(*myMine->myMiner, REMOVE);
                                myMine->myMiner->Move(pX, pY);
                                if ((pY + 1) < myMine->getLinhas())
                                    break;
                            }

                    break;
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
    WritePauseMenu();

    int x = 8, y = 10;
    myConsole->gotoxy(x, y);
    std::cout << '>';
    while (1)
        {
            tecla = myConsole->getch();
            if (tecla == ENTER && y == 10) break;
            if (tecla == ENTER && y == 12) break;
            if (tecla == ENTER && y == 14) break;
            if (tecla == ENTER && y == 16) break;
            if (tecla != UP && tecla != DOWN) continue;

            myConsole->gotoxy(x, y);
            std::cout << ' ';

            if (tecla == myConsole->CIMA) y -= 2;
            if (tecla == myConsole->BAIXO) y += 2;
            if (y < 10) y = 10;
            if (y > 16) y = 16;
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
        case SAVE_GAME:
            SaveGame();
            break;
        case EXIT_GAME:
            myMine->myMiner->ResetStats();
            Start();
            break;
        }
}
void Game::SoundOptions()
{
    myConsole->clrscr();
    myConsole->gotoxy(14, 2);
    std::cout << " ---Opcoes de Som---";
    myConsole->gotoxy(10, 8);
    std::cout << "** Escolhe uma opcao **";
    myConsole->gotoxy(10, 10);
    std::cout << "ON";
    myConsole->gotoxy(10, 12);
    std::cout << "OFF";
    myConsole->gotoxy(10, 14);
    std::cout << "Voltar";

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
        case EXIT_GAME:
            break;
        }
    Pause();
}
void Game::CommandMode()
{
    std::string read;
    bool valid = false;
    int action = 0;

    myConsole->clrscr();

    if (pY == 0)
        myMine->myMiner->ReachSurface();

    while (read != "j")
        {
            myConsole->gotoxy(2, 2);
            std::cout << "[MODO DE COMANDOS]";
            myConsole->gotoxy(0, 4);
            std::cout << "Comando : ____________________";
            myConsole->gotoxy(10, 4);
            std::getline(std::cin, read);

            std::istringstream iss(read);
            std::istringstream countstream(read);
            std::string command;
            std::string params[5];

            int count = 0;

            do
                {
                    std::string counter;
                    countstream >> counter;
                    count++;
                }
            while (countstream);
            count--;

            iss >> command;


            for (int i = 0; i< NUM_COMMANDS; i++)
                {
                    if (command.compare(validCommands[i][0]) == 0)
                        {
                            valid = true;
                            action = i;
                            break;
                        }
                }

            if (valid == false)
                {
                    myConsole->clrscr();
                    myConsole->gotoxy(2, 2);
                    std::cout << "[COMMAND MODE]";
                    myConsole->gotoxy(0, 4);
                    std::cout << "Command : ____________________";
                    myConsole->gotoxy(0, 6);
                    std::cout << "[GAME] -> '" << read << "' not found.";
                }
            else
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
                        case 3: //SetGold
                            if (count == atoi(validCommands[action][1].c_str()))
                                {
                                    for (int i = 0; i < atoi(validCommands[action][1].c_str()) - 1; i++)
                                        {
                                            iss >> params[i];
                                        }
                                    myMine->myMiner->setGoldCount(atoi(params[0].c_str()));
                                    std::cout << "Gold set successfully!" << std::endl;
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
                            if (count != atoi(validCommands[action][1].c_str()))
                                {
                                    std::cout << std::endl << std::endl << "Invalid argument number!" << std::endl;
                                    break;
                                }
                            break;
                        case 6: //LoadMine
                            if (count != atoi(validCommands[action][1].c_str()))
                                {
                                    std::cout << std::endl << std::endl << "Invalid argument number!" << std::endl;
                                    break;
                                }
                            break;
                        case 7: //CopyMine
                            if (count != atoi(validCommands[action][1].c_str()))
                                {
                                    std::cout << std::endl << std::endl << "Invalid argument number!" << std::endl;
                                    break;
                                }
                            break;
                        case 8:
                            myConsole->clrscr();
                            exit(0);
                            break;
                        case 9:
                            myConsole->clrscr();
                            return;
                            break;
                        case 10:
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

void Game::BuyTool(std::string toolName)
{
    for (int i = 0; i < NUM_UTENSILIOS; i++)
        {
            if (myUtensilios[i].getName().compare(toolName.c_str()) == 0)
                {
                    if (myMine->myMiner->getCoins() >= myUtensilios[i].getCost())
                        {
                            myMine->myMiner->setCoins(myMine->myMiner->getCoins() - myUtensilios[i].getCost());
                            std::cout << myUtensilios[i].getName() << " bought successfully with " << myUtensilios[i].getCost() << " coins." << std::endl;
                            myConsole->getch();
                        }
                    else
                        {
                            std::cout << "Not enough coins!" << std::endl;
                            myConsole->getch();
                            return;
                        }
                    return;
                }

        }
    std::cout << "Tool non-existant!" << std::endl;
    myConsole->getch();
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
    PlaySound(TEXT("Data/falling.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
}
void Game::PlayRockSlide()
{
    PlaySound(TEXT("Data/rockslide.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
}
void Game::StopMusic()
{
    PlaySound(NULL, 0, 0);
}

/* Gets */
int Game::Status() const
{
    return _currentStatus;
}

/* Draws */
void Game::WriteMainMenu()
{
    myConsole->gotoxy(14, 2);
    myConsole->setTextColor(myConsole->VERDE);
    std::cout << "Bem vindo ao Gem Miner";
    myConsole->gotoxy(10, 8);
    myConsole->setTextColor(myConsole->AMARELO);
    std::cout << "** Escolhe uma opcao **";
    myConsole->gotoxy(10, 10);
    myConsole->setTextColor(myConsole->VERMELHO);
    std::cout << "Novo Jogo";
    myConsole->gotoxy(10, 12);
    std::cout << "Carregar Jogo";
    myConsole->gotoxy(10, 14);
    std::cout << "Sair";
    myConsole->setTextColor(myConsole->AZUL_CLARO);
}
void Game::WritePauseMenu()
{
    myConsole->gotoxy(14, 2);
    std::cout << " -----Pausa-----";
    myConsole->gotoxy(10, 8);
    std::cout << "** Escolhe uma opcao **";
    myConsole->gotoxy(10, 10);
    std::cout << "Continuar";
    myConsole->gotoxy(10, 12);
    std::cout << "Som";
    myConsole->gotoxy(10, 14);
    std::cout << "Guardar Jogo";
    myConsole->gotoxy(10, 16);
    std::cout << "Sair do Jogo";
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
