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

std::string myBlocks[12] =
{
    "M", //Mineiro
    "P", //Pedra
    "TM", //Terreno Mole
    "TD", //Terreno Duro
    "TcA", //Terra c Aluminio
    "TcC", //Terra c Carvao
    "TcF", //Terra c Ferro
    "TcO", //Terra c Ouro
    "TcD", //Terra c Diamante
    "TcFAF", //Terra c Frango Assado Fossilizado
    "E", //Escada
    "V" //Viga
};

/* General */
Game::Game()
{
    _currentStatus = ACTIVE;
    reader = new INIReader("data/config.ini");
    if (reader->ParseError() < 0)
        {
            std::cout << "Can't load 'test.ini'\n";
            return;
        }
    myDrawer = new Drawer();
    myConsole = new Consola();
    myMiner = new Miner((int)reader->GetInteger("MINER_DEFAULT_STATS", "StartLives", 3), (int)reader->GetInteger("MINER_DEFAULT_STATS", "StartEnergy", 100), (int)reader->GetInteger("MINER_DEFAULT_STATS", "StartCoins", 0));
    myCommunicatorInterface = new CommunicatorInterface(reader->Get("NETWORKING", "IP", 0).c_str(), reader->Get("NETWORKING", "Port", 0).c_str());
    LoadUtensilios(myUtensilios);
}
void Game::InitializeMine(int Rows, int Cols, int Vision)
{
    _linhas = Rows;
    _colunas = Cols;
    _vision = Vision;

    srand( (unsigned int)time(NULL) ); //Randomize

    /* Create Mine Array Dinamically */
    myMine = new Block**[_linhas];
    for (int r = 0; r < _linhas; r++)
        {
            myMine[r] = new Block*[_colunas];
            for (int c = 0; c < _colunas; c++)
                myMine[r][c] = new Block();
        }

    /* Populate Mine Array Automatically */
    for (int r = 0; r < _linhas; r++)
        {
            for (int c = 0; c < _colunas; c++)
                {
                    int blockType = rand() % 10 + 1; //Generates a random block type

                    if (r == _linhas / 2 && c == _colunas / 2) //Middle of Mine
                        {
                            myMine[r][c] = new Block(c, r); //Empty Block
                        }
                    else
                        {
                            switch (blockType)
                                {
                                case P:
                                    myMine[r][c] = new Pedra(c, r);
                                    break;
                                case TM:
                                    myMine[r][c] = new TerrenoMole(c, r);
                                    break;
                                case TD:
                                    myMine[r][c] = new TerrenoDuro(c, r);
                                    break;
                                case TcA:
                                    myMine[r][c] = new TerraCAluminio(c, r);
                                    break;
                                case TcC:
                                    myMine[r][c] = new TerraCCarvao(c, r);
                                    break;
                                case TcF:
                                    myMine[r][c] = new TerraCFerro(c, r);
                                    break;
                                case TcO:
                                    myMine[r][c] = new TerraCOuro(c, r);
                                    break;
                                case TcD:
                                    myMine[r][c] = new TerraCDiamante(c, r);
                                    break;
                                case TcFAF:
                                    myMine[r][c] = new TerraCFrango(c, r);
                                    break;
                                case E:
                                    myMine[r][c] = new Escada(c, r);
                                    break;
                                case V:
                                    myMine[r][c] = new Viga(c, r);
                                    break;
                                }
                        }
                }
        }
}
void Game::Start()
{
    PlayIntro();

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
    clrscr();
    gotoxy(14, 2);
    std::cout << "Criacao Novo Jogo";
    std::cout << std::endl << "Dimensao da Mina" << std::endl;
    std::cout << "Linhas: ";
    myConsole->setTextColor(VERMELHO_CLARO);
    std::cin >> nLinhas;
    myConsole->setTextColor(AZUL_CLARO);
    std::cout << "Colunas: ";
    myConsole->setTextColor(VERMELHO_CLARO);
    std::cin >> nColunas;
    std::cout << std::endl;

    _linhas = nLinhas;
    _colunas = nColunas;

    clrscr();

    InitializeMine(_linhas, _colunas, (int)reader->GetInteger("GENERAL", "Vision", 2));

    StopMusic();
    PlayTheme();

    Play();
}
void Game::LoadGame()
{
    int numSaves = 0;
    char tecla;
    BOOL H = true;
    wchar_t* savesLocation = L"saves/*.gem";

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

    std::string filename = GetLoadFilename(nameID);

    std::ifstream infile;
    infile.open(filename, std::ios::binary);

    infile.read((char *)&myGame, sizeof(Game));

    if (infile.fail())
        {
            std::cout << "read failed" << std::endl;
        }

    std::cout << myGame->myMiner->getX();
    system("pause");

    Play();


} //TODO: Serialization
void Game::SaveGame()
{
    myConsole->clrscr();
    myConsole->gotoxy(2, 2);

    myGame = this;

    int i = 0;

    std::string filename = "saves/miner-save-" + currentDate() + ".gem";

    std::ifstream ifile(filename);
    if (ifile)
        {
            char c;
            srand((unsigned int)time(NULL));
            c = (rand() % 254);
            i++;
            filename = "saves/miner-save-" + currentDate() + c + ".gem";
        }

    std::cout << "SAVED: " << myGame->myMiner->getX();
    system("pause");

    std::ofstream outfile;
    outfile.open(filename.c_str(), std::ios::binary);

    outfile.write((char *)(&myGame), sizeof(Game));

    if (outfile.fail())
        std::cout << "write failed" << std::endl;

    outfile.close();


    std::ifstream infile;
    infile.open(filename, std::ios::binary);

    infile.read((char *)&myGame, sizeof(Game));

    if (infile.fail())
        {
            std::cout << "read failed" << std::endl;
        }

    std::cout << "READ: " << myGame->myMiner->getX();
    system("pause");

    std::cout << "Gravado em " << filename;
    myConsole->getch();
} //TODO: Serialization
void Game::Play()
{
    myConsole->setScreenBufferSize(7 * 5 + 5, 7 * 5);
    myConsole->setScreenSize(7 * 5 + 5, 7 * 5);
    myConsole->setTextColor(myConsole->PRETO);

    char tecla;
    int pX = _linhas / 2, pY = _colunas / 2; //Player Start Position
    int vX = _linhas / 2 - 3, vY = _colunas / 2 - 3; //Mine Start Writing Position

    /* Miner Start Position */
    myMiner->setCoordinates(pX, pY);

    /* Main cycle of Game */
    while (myMiner->hasLifes())
        {
            myConsole->clrscr();
            myDrawer->Draw(myMine, myMiner, vX, vY, _vision, _colunas, _linhas);	//Draws Mine
            myDrawer->Draw(*myMiner, SHOW);											//Draws Miner
            myDrawer->DrawStats(*myMiner, SHOW);									//Draw Stats

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
                case UP:
                    pY -= 1; //Move 1 position UP
                    (pY <= 0 ? pY = 0 : pY = pY); //Top Bounding
                    RemoveBlock(pX, pY, UP);
                    myDrawer->Draw(*myMiner, REMOVE);
                    myMiner->Move(pX, pY);
                    break;
                case DOWN: //TODO: Fall
                    pY += 1; //Move 1 position DOWN
                    (pY >= _linhas - 1 ? pY = _linhas - 1 : pY = pY); //Bottom Bounding
                    RemoveBlock(pX, pY, DOWN);
                    myDrawer->Draw(*myMiner, REMOVE);
                    myMiner->Move(pX, pY);
                    break;
                case LEFT:
                    pX -= 1; //Move 1 position LEFT
                    (pX <= 0 ? pX = 0 : pX = pX); //Left Bounding
                    RemoveBlock(pX, pY, LEFT);
                    myDrawer->Draw(*myMiner, REMOVE);
                    myMiner->Move(pX, pY);
                    break;
                case RIGHT:
                    pX += 1; //Move 1 position RIGHT
                    (pX >= _colunas - 1 ? pX = _colunas - 1 : pX = pX); //Right Bounding
                    RemoveBlock(pX, pY, RIGHT);
                    myDrawer->Draw(*myMiner, REMOVE);
                    myMiner->Move(pX, pY);
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
    setTextColor(PRETO);
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
            Resume();
            break;
        case SOUND_OPTIONS:
            SoundOptions();
            break;
        case SAVE_GAME:
            SaveGame();
            break;
        case EXIT_GAME:
            myMiner->ResetStats();
            Start();
            break;
        }
    Resume();
}
void Game::Resume()
{
    DrawMine(_linhas / 2 - 3, _colunas / 2 - 3);
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
            Resume();
            break;
        }
    Pause();
}
void Game::CommandMode()
{
    //TODO: Code Rework with Recursive
    std::string read;
    bool valid = false;
    int action = 0;

    myConsole->clrscr();


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
                    std::cout << "[MODO DE COMANDOS]";
                    myConsole->gotoxy(0, 4);
                    std::cout << "Comando : ____________________";
                    myConsole->gotoxy(0, 6);
                    std::cout << "[GAME] -> '" << read << "' nao encontrado.";
                }
            else
                {
                    valid = false;
                    myConsole->clrscr();
                    myConsole->gotoxy(2, 2);
                    std::cout << "[MODO DE COMANDOS]";
                    myConsole->gotoxy(0, 4);
                    std::cout << "Comando : ____________________";
                    myConsole->gotoxy(0, 6);
                    std::cout << "[GAME] -> '" << read << "' existe." << std::endl;
                    switch (action)
                        {
                        case 0:
                            if (count != atoi(validCommands[action][1].c_str()))
                                {
                                    std::cout << std::endl << std::endl << "Numero de argumentos invalido!" << std::endl;
                                    myConsole->getch();
                                    break;
                                }
                            iss >> command;
                            std::cout << "Param 1: " << command << std::endl;
                            break;
                        case 1:
                            if (count != atoi(validCommands[action][1].c_str()))
                                {
                                    std::cout << std::endl << std::endl << "Numero de argumentos invalido!" << std::endl;
                                    myConsole->getch();
                                    break;
                                }
                            iss >> command;
                            std::cout << "Param 1: " << command << std::endl;
                            break;
                        case 2:
                            if (count != atoi(validCommands[action][1].c_str()))
                                {
                                    std::cout << std::endl << std::endl << "Numero de argumentos invalido!" << std::endl;
                                    myConsole->getch();
                                    break;
                                }
                            iss >> command;
                            std::cout << "Param 1: " << command << std::endl;
                            break;
                        case 3:
                            if (count != atoi(validCommands[action][1].c_str()))
                                {
                                    std::cout << std::endl << std::endl << "Numero de argumentos invalido!" << std::endl;
                                    myConsole->getch();
                                    break;
                                }
                            iss >> command;
                            std::cout << "Param 1: " << command << std::endl;
                            break;
                        case 4:
                            if (count != atoi(validCommands[action][1].c_str()))
                                {
                                    std::cout << std::endl << std::endl << "Numero de argumentos invalido!" << std::endl;
                                    myConsole->getch();
                                    break;
                                }
                            iss >> command;
                            std::cout << "Param 1: " << command << std::endl;
                            break;
                        case 5:
                            if (count != atoi(validCommands[action][1].c_str()))
                                {
                                    std::cout << std::endl << std::endl << "Numero de argumentos invalido!" << std::endl;
                                    myConsole->getch();
                                    break;
                                }
                            iss >> command;
                            std::cout << "Param 1: " << command << std::endl;
                            break;
                        case 6:
                            if (count != atoi(validCommands[action][1].c_str()))
                                {
                                    std::cout << std::endl << std::endl << "Numero de argumentos invalido!" << std::endl;
                                    myConsole->getch();
                                    break;
                                }
                            iss >> command;
                            std::cout << "Param 1: " << command << std::endl;
                            break;
                        case 7:
                            if (count != atoi(validCommands[action][1].c_str()))
                                {
                                    std::cout << std::endl << std::endl << "Numero de argumentos invalido!" << std::endl;
                                    myConsole->getch();
                                    break;
                                }
                            iss >> command;
                            std::cout << "Param 1: " << command << std::endl;
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
                                    std::cout << std::endl << std::endl << "Numero de argumentos invalido!" << std::endl;
                                    myConsole->getch();
                                    break;
                                }
                            for (int i = 0; i < NUM_UTENSILIOS; i++)
                                {
                                    std::cout << myUtensilios[i].getName() << " - " << myUtensilios[i].getCost() << std::endl;

                                }
                            break;
                        }
                    //command = strtok(command, " "); stringstream
                }
        }
    myConsole->clrscr();
    return;
}

/* Sound */
void Game::PlayIntro()
{
    PlaySound(TEXT("data/intro.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
}
void Game::PlayTheme()
{
    PlaySound(TEXT("data/theme.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
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
    myConsole->setTextColor(VERDE);
    std::cout << "Bem vindo ao Gem Miner";
    myConsole->gotoxy(10, 8);
    myConsole->setTextColor(AMARELO);
    std::cout << "** Escolhe uma opcao **";
    myConsole->gotoxy(10, 10);
    myConsole->setTextColor(VERMELHO);
    std::cout << "Novo Jogo";
    myConsole->gotoxy(10, 12);
    std::cout << "Carregar Jogo";
    myConsole->gotoxy(10, 14);
    std::cout << "Sair";
    myConsole->setTextColor(AZUL_CLARO);
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
void Game::DrawMine(int startDrawX, int startDrawY)
{
    int piX = (myMiner->getX() - _vision > 0) ? myMiner->getX() - _vision : 0; //Initial X
    int piY = (myMiner->getY() - _vision > 0) ? myMiner->getY() - _vision : 0; //Initial Y

    int pfX = (myMiner->getX() + _vision < _colunas) ? myMiner->getX() + _vision : myMiner->getX() + (_colunas - myMiner->getX()) - 1; //Final X
    int pfY = (myMiner->getY() + _vision < _linhas) ? myMiner->getY() + _vision : myMiner->getY() + (_linhas - myMiner->getY()) - 1; //Final Y

    for (startDrawY = piY; startDrawY <= pfY; startDrawY++)
        {
            for (startDrawX = piX; startDrawX <= pfX; startDrawX++)
                {
                    (startDrawY >= piY && startDrawY <= pfY && startDrawX >= piX && startDrawX <= pfX) ? DrawBlock(myMine[startDrawY][startDrawX]->getID(), myMine[startDrawY][startDrawX]->getX() * 5, myMine[startDrawY][startDrawX]->getY() * 5) : 0;
                }
        }
}
void Game::RemoveBlock(int &bX, int &bY, int DIRECTION)
{
    if (myMine[bY][bX]->getID() != "E" && myMine[bY][bX]->getID() != "V")
        {
            if (myMine[bY][bX]->getBreakeable() == 1)
                {
                    PlaySound(TEXT("data/mine.wav"), NULL, SND_ASYNC | SND_FILENAME);
                    while (myMine[bY][bX]->getTicks() > 0)
                        {
                            myMine[bY][bX]->setTicks(myMine[bY][bX]->getTicks() - 1);
                            myMiner->setEnergy(myMiner->getEnergy() - 1);
                        }
                    myMine[bY][bX]->setID("NULL");
                    myMine[bY][bX]->setBreakeable(1);
                }
            else
                {
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

}

/* System Funcionts */
const std::string Game::currentDate()
{
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%d%m%Y", &tstruct);
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
    wchar_t* savesLocation = L"saves/*.gem";

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
