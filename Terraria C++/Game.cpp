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
    reader = new INIReader("data/config.ini");
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

    infile.read((char *)this, sizeof(Game));

    if (infile.fail())
        {
            std::cout << "read failed" << std::endl;
        }

    std::cout << this->myMine->myMiner->getX();
    system("pause");

    Play();


} //TODO: Serialization
void Game::SaveGame()
{
    myConsole->clrscr();
    myConsole->gotoxy(2, 2);

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

    std::cout << "SAVED: " << this->myMine->myMiner->getX();
    system("pause");

    std::ofstream outfile;
    outfile.open(filename.c_str(), std::ios::binary);

    outfile.write((char *)(this), sizeof(Game));

    if (outfile.fail())
        std::cout << "write failed" << std::endl;

    outfile.close();


    std::ifstream infile;
    infile.open(filename, std::ios::binary);

    infile.read((char *)this, sizeof(Game));

    if (infile.fail())
        {
            std::cout << "read failed" << std::endl;
        }

    std::cout << "READ: " << this->myMine->myMiner->getX();
    system("pause");

    std::cout << "Gravado em " << filename;
    myConsole->getch();
} //TODO: Serialization
void Game::Play()
{
    this->myConsole->setScreenBufferSize(7 * 5 + 5, 7 * 5);
    this->myConsole->setScreenSize(7 * 5 + 5, 7 * 5);
    this->myConsole->setTextColor(this->myConsole->PRETO);

    char tecla;
    pX = myMine->getLinhas() / 2, pY = myMine->getColunas() / 2; //Player Start Position
    vX = myMine->getLinhas() / 2 - 3, vY = myMine->getColunas() / 2 - 3; //Mine Start Writing Position

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
                    pY -= 1; //Move 1 position UP
                    (pY <= 0 ? pY = 0 : pY = pY); //Top Bounding
                    if (pY != 0)
                        {
                            myMine->RemoveBlock(pX, pY, UP);
                            myMine->myDrawer->Draw(*myMine->myMiner, REMOVE);
                            myMine->myMiner->Move(pX, pY);
                        }
                    else
                        {
                            myMine->myMiner->ReachSurface();
                            myMine->myDrawer->Draw(*myMine->myMiner, REMOVE);
                            myMine->myMiner->Move(pX, pY);
                        }
                    break;
                case DOWN: //TODO: Fall
                    pY += 1; //Move 1 position DOWN
                    (pY >= myMine->getLinhas() - 1 ? pY = myMine->getLinhas() - 1 : pY = pY); //Bottom Bounding
                    myMine->RemoveBlock(pX, pY, DOWN);
                    myMine->myDrawer->Draw(*myMine->myMiner, REMOVE);
                    myMine->myMiner->Move(pX, pY);
                    break;
                case LEFT:
                    pX -= 1; //Move 1 position LEFT
                    (pX <= 0 ? pX = 0 : pX = pX); //Left Bounding
                    myMine->RemoveBlock(pX, pY, LEFT);
                    myMine->myDrawer->Draw(*myMine->myMiner, REMOVE);
                    myMine->myMiner->Move(pX, pY);
                    break;
                case RIGHT:
                    pX += 1; //Move 1 position RIGHT
                    (pX >= myMine->getColunas() - 1 ? pX = myMine->getColunas() - 1 : pX = pX); //Right Bounding
                    myMine->RemoveBlock(pX, pY, RIGHT);
                    myMine->myDrawer->Draw(*myMine->myMiner, REMOVE);
                    myMine->myMiner->Move(pX, pY);
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
                                }
                            else
                                {
                                    std::cout << std::endl << std::endl << "Numero de argumentos invalido!" << std::endl;
                                    myConsole->getch();
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
                                    break;
                                }
                            else
                                {
                                    std::cout << std::endl << std::endl << "Numero de argumentos invalido!" << std::endl;
                                    myConsole->getch();
                                    break;
                                }
                        case 2:
                            if (count == atoi(validCommands[action][1].c_str()))
                                {
                                    for (int i = 0; i < atoi(validCommands[action][1].c_str()) - 1; i++)
                                        {
                                            iss >> params[i];
                                        }
                                    Teleport(atoi(params[0].c_str()), atoi(params[1].c_str()));
                                    break;
                                }
                            else
                                {
                                    std::cout << std::endl << std::endl << "Numero de argumentos invalido!" << std::endl;
                                    myConsole->getch();
                                    break;
                                }
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
                            switch (str2int(myUtensilios[i].getName().c_str()))
                                {
                                case 1:
                                    break;
                                }
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
}

void Game::CreateBlock(int blockType, int X, int Y)
{
    if (blockType > 0 && blockType < 13 && X <= myMine->getLinhas() && Y <= myMine->getColunas())
        {
            switch (blockType)
                {
                case 1:
                    myMine->myMine[X][Y] = new Pedra(X, Y);
                    break;
                case 2:
                    myMine->myMine[X][Y] = new TerrenoMole(X, Y);
                    break;
                case 3:
                    myMine->myMine[X][Y] = new TerrenoDuro(X, Y);
                    break;
                case 4:
                    myMine->myMine[X][Y] = new TerraCAluminio(X, Y);
                    break;
                case 5:
                    myMine->myMine[X][Y] = new TerraCCarvao(X, Y);
                    break;
                case 6:
                    myMine->myMine[X][Y] = new TerraCFerro(X, Y);
                    break;
                case 7:
                    myMine->myMine[X][Y] = new TerraCOuro(X, Y);
                    break;
                case 8:
                    myMine->myMine[X][Y] = new TerraCDiamante(X, Y);
                    break;
                case 9:
                    myMine->myMine[X][Y] = new TerraCFrango(X, Y);
                    break;
                case 10:
                    myMine->myMine[X][Y] = new Escada(X, Y);
                    break;
                case 11:
                    myMine->myMine[X][Y] = new Viga(X, Y);
                    break;
                case 12:
                    myMine->myMine[X][Y] = new Vazio(X, Y);
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

constexpr unsigned int str2int(const char* str, int h = 0)
{
    return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
}
