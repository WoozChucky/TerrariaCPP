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
    { "j"  "2" } //j
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
    myGame = this;
    myConsole = new Consola();
    myMiner = new Miner(START_LIVES, START_ENERGY, START_GOLD);
    LoadUtensilios(myUtensilios);
}
void Game::InitializeMine(int Rows, int Cols, int Vision)
{
    _linhas = Rows;
    _colunas = Cols;
    _vision = Vision;

    srand( (unsigned int)time(NULL) );

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
                    int blockType = rand() % 2 + 2;



                    /*if (blockType == 1)
                        {
                            myMine[r][c]->setID(myBlocks[P]);
                            myMine[r][c]->setBreakeable(0);
                            myMine[r][c]->setTicks(0);
                            myMine[r][c]->setX(c);
                            myMine[r][c]->setY(r);
                        }
                    else if (blockType == 2)
                        { */
                    myMine[r][c]->setID(myBlocks[TM]);
                    myMine[r][c]->setBreakeable(1);
                    myMine[r][c]->setTicks(2);
                    myMine[r][c]->setX(c);
                    myMine[r][c]->setY(r);
                    //  }
                    //else if (blockType == 3) //Ouro de teste
                    //    {
                    //        if (c > _colunas / 2)
                    //            {
                    //                myMine[r][c]->setID(myBlocks[TcO]);
                    //                myMine[r][c]->setBreakeable(1);
                    //                myMine[r][c]->setTicks(2);
                    //                myMine[r][c]->setX(c);
                    //                myMine[r][c]->setY(r);
                    //            }
                    //        else
                    //            {
                    //                myMine[r][c]->setID(myBlocks[TM]);
                    //                myMine[r][c]->setBreakeable(1);
                    //                myMine[r][c]->setTicks(1);
                    //                myMine[r][c]->setX(c);
                    //                myMine[r][c]->setY(r);
                    //            }
                    //    }


                    if (r == _linhas / 2 && c == _colunas / 2) //Mineiro
                        {
                            /*myMine[r][c]->setID(myBlocks[M]);
                            myMine[r][c]->setX(c);
                            myMine[r][c]->setY(r);*/
                        }
                    // AI da Mine
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

    InitializeMine(_linhas, _colunas, 3);

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
    setScreenBufferSize(7 * 5 + 5, 7 * 5);
    setScreenSize(7 * 5 + 5, 7 * 5);
    setTextColor(PRETO);

    char tecla;
    int pX = _linhas / 2, pY = _colunas / 2; //Player Start Position
    int vX = _linhas / 2 - 3, vY = _colunas / 2 - 3; //Mine Start Writing Position


    myMiner->setCoordinates(pX, pY);
    //myConsole->NewWindow(L"Gem Miner - Stats", 400, 400, 400, 250);

    /* Main cycle of Game */
    while (myMiner->hasLifes())
        {
            clrscr();
            DrawMine(vX, vY); //Draws Mine
            myMiner->Show(); //Draws Miner
            myMiner->showStats(); //Draw Stats

            tecla = getch();

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

                    if (isColliding(pY, pX)) //Collision Detection
                        {
                            if (myMine[pY][pX]->getBreakeable() == 1)
                                {
                                    if (myMine[pY][pX]->getTicks() > 0)
                                        {
                                            while (myMine[pY][pX]->getTicks() > 0)
                                                {
                                                    if (myMiner->getEnergy() > 0)
                                                        {
                                                            myMine[pY][pX]->setTicks(myMine[pY][pX]->getTicks() - 1);
                                                            myMiner->setEnergy(myMiner->getEnergy() - 1);
                                                        }
                                                }
                                            RemoveBlock(myMine[pX][pY]);
                                        }
                                }
                            else
                                pY += 1;
                        }
                    myMiner->Move(pX, pY);
                    break;
                case DOWN:
                    pY += 1; //Move 1 posição para baixo

                    (pY >= _linhas - 1 ? pY = _linhas - 1 : pY = pY); //Bottom Bounding

                    if (isColliding(pY, pX)) //Collision Detection
                        {
                            if (myMine[pY][pX]->getBreakeable() == 1)
                                {
                                    if (myMine[pY][pX]->getTicks() > 0)
                                        {
                                            while (myMine[pY][pX]->getTicks() > 0)
                                                {
                                                    if (myMiner->getEnergy() > 0)
                                                        {
                                                            myMine[pY][pX]->setTicks(myMine[pY][pX]->getTicks() - 1);
                                                            myMiner->setEnergy(myMiner->getEnergy() - 1);
                                                        }
                                                }
                                            RemoveBlock(myMine[pX][pY]);
                                        }
                                }
                            else
                                pY -= 1;
                        }
                    myMiner->Move(pX, pY);
                    break;
                case LEFT:
                    pX -= 1; //Move 1 posição para a esquerda

                    (pX <= 0 ? pX = 0 : pX = pX); //Left Bounding

                    if (isColliding(pY, pX)) //Collision Detection
                        {
                            if (myMine[pY][pX]->getBreakeable() == 1)
                                {
                                    if (myMine[pY][pX]->getTicks() > 0)
                                        {
                                            while (myMine[pY][pX]->getTicks() > 0)
                                                {
                                                    if (myMiner->getEnergy() > 0)
                                                        {
                                                            myMine[pY][pX]->setTicks(myMine[pY][pX]->getTicks() - 1);
                                                            myMiner->setEnergy(myMiner->getEnergy() - 1);
                                                        }
                                                }
                                            RemoveBlock(myMine[pX][pY]);
                                        }
                                }
                            else
                                pX += 1;
                        }
                    myMiner->Move(pX, pY);
                    break;
                case RIGHT:

                    pX += 1; //Moves 1 position to the right

                    (pX >= _colunas - 1 ? pX = _colunas - 1 : pX = pX); //Right Bounding

                    if (isColliding(pY, pX)) //Collision Detection
                        {
                            if (myMine[pY][pX]->getBreakeable() == 1)
                                {
                                    if (myMine[pY][pX]->getTicks() > 0)
                                        {
                                            while (myMine[pY][pX]->getTicks() > 0)
                                                {
                                                    if (myMiner->getEnergy() > 0)
                                                        {
                                                            myMine[pY][pX]->setTicks(myMine[pY][pX]->getTicks() - 1);
                                                            myMiner->setEnergy(myMiner->getEnergy() - 1);
                                                        }
                                                }
                                            RemoveBlock(myMine[pX][pY]);
                                        }
                                }
                            else
                                pX -= 1;
                        }
                    myMiner->Move(pX, pY);
                    break;
                }
        }
    Write("Game Over");
    getch();
    _currentStatus = END;
    EndGame();
    return;
}
void Game::EndGame()
{
    delete myConsole;
    delete myGame;
    delete myMiner;
    delete[] myMine;
    free(myUtensilios);
    free(myBlocks);
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
    std::string read;
    bool valid = false;
    int action = 0;

    myConsole->clrscr();


    while (read != "j")
        {
            //Console.clrscr();
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

    for (startDrawX = piY; startDrawX <= pfY; startDrawX++)
        {
            for (startDrawY = piX; startDrawY <= pfX; startDrawY++)
                {
                    (startDrawX >= piY && startDrawX <= pfY && startDrawY >= piX && startDrawY <= pfX) ? DrawBlock(myMine[startDrawY][startDrawX]->getID(), startDrawY * 5, startDrawX * 5) : 0;
                }
        }
}
void Game::RemoveBlock(Block * &bloco)
{
    bloco = new Block();
    bloco->setID("NULL");
    bloco->setX(2147483647);
    bloco->setY(2147483647);
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

/* Collision Detection */
bool Game::isColliding(int pY, int pX)
{
    std::cout << pX << " : " << myMine[pY][pX]->getX() << " / " << pY << " : " << myMine[pY][pX]->getY();
    getch();
    if (pX == myMine[pY][pX]->getX() && pY == myMine[pY][pX]->getY())
        return true;
    return false;
}