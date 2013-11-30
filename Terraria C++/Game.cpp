#include "Game.h"

std::string validCommands[NUM_COMMANDS] =
{
    "u", //u nome-utensilio
    "b", //b ID x y
    "t", //t x y
    "g", //g value
    "e", //e value
    "c", //c new_name
    "f", //f name
    "a", //a source destination
    "x", //x
    "j"  //j
};

Game::Game()
{
    _currentStatus = ACTIVE;
    myGame = this;
    myConsole = new Consola();
    myBlockTypes = new BlockTypes();
    myMiner = new Miner(3, 100, 0);
    myMine = new Mine();
}

void Game::WriteMainMenu()
{
    myConsole->gotoxy(14, 2);
    std::cout << "Bem vindo ao Gem Miner";
    myConsole->gotoxy(10, 8);
    std::cout << "** Escolhe uma opcao **";
    myConsole->gotoxy(10, 10);
    std::cout << "Novo Jogo";
    myConsole->gotoxy(10, 12);
    std::cout << "Carregar Jogo";
    myConsole->gotoxy(10, 14);
    std::cout << "Sair";
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

void Game::NewGame()
{
    int nLinhas, nColunas;

    myConsole->clrscr();

    myConsole->gotoxy(14, 2);
    std::cout << "Criacao Novo Jogo";
    std::cout << std::endl << "Dimensao da Mina:" << std::endl;
    std::cout << "Linhas: ";
    std::cin >> nLinhas;
    std::cout << "Colunas: ";
    std::cin >> nColunas;
    std::cout << std::endl;

    linhas = nLinhas;
    colunas = nColunas;

    myConsole->clrscr();

    myMine->Initialize(linhas, colunas, 2);

    StopMusic();
    PlayTheme();

    Play();
}

void Game::LoadGame()
{
    int numSaves = 0;
    char tecla;
    bool H = true;
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

    Play(myGame->myMiner->getX(), myGame->myMiner->getY());


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
}

void Game::Play(int playerX, int playerY)
{
    if (playerX != 0 && playerY != 0)
        {
            myMine->Initialize(linhas, colunas);
            std::cout << "Mina inicializada pelo savegame" << std::endl;
            std::cout << playerX, playerY;
            system("pause");
        }


    char tecla;

    int x = playerX, y = playerY; //Character Start Position
    int wX = (7 / 2) * 5, wY = (7 / 2) * 5; //Scroll Boundings
    int vX = x, vY = y; //Camera Start Position #Virtual Coordinates

    //myConsole->NewWindow(L"Gem Miner - Stats", 400, 400, 400, 250);
    myConsole->setScreenBufferSize(linhas * 5 + 1, colunas);
    myConsole->setScreenSize(7 * 5, 7 * 5);


    if (_currentStatus != ACTIVE)
        return;

    while (myMiner->hasLifes())
        {
            myMiner->isAlive(*myConsole);
            //myMiner->showStats(*myConsole);
            myMiner->Show(*myConsole, x, y);

            myConsole->gotoxy(vX, vY);

            tecla = myConsole->getch();

            switch (tecla)
                {
                case ESCAPE:
                    Pause();
                    break;
                case C:
                    CommandMode();
                    myMiner->Show(*myConsole, x, y);
                    break;
                case UP:
                    //Mineiro.DeleteStats(Console,  x);
                    if (y > 0)
                        {
                            myMiner->Move(*myConsole, x, y);
                            y -= 5;

                            vX = x;
                            vY = y - wY;
                        }
                    break;
                case DOWN:

                    //Mineiro.DeleteStats(Console, x);
                    if (y < (linhas * 5) - 5)
                        {
                            myMiner->Move(*myConsole, x, y);
                            y += 5;
                            vX = x;
                            vY = y + wY;
                        }
                    break;
                case RIGHT:

                    //Mineiro.DeleteStats(Console, x);
                    if (x < (colunas * 5) - 5)
                        {
                            myMiner->Move(*myConsole, x, y);
                            x += 5;
                            vY = y;
                            vX = x + wX;
                        }
                    break;
                case LEFT:

                    //Mineiro.DeleteStats(Console, x);

                    if (x > 0)
                        {
                            myMiner->Move(*myConsole, x, y);
                            x -= 5;
                            vY = y;
                            vX = x - wX;
                        }
                    break;
                }
        }
    _currentStatus = END;
}

void Game::Pause()
{
    char tecla;
    myConsole->setScreenSize(20, 50);
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
    myConsole->clrscr();
    myConsole->setScreenBufferSize(linhas * 5 + 1, colunas * 5);
    myConsole->setScreenSize(7 * 5, 7 * 5);
    myConsole->clrscr();

    //TODO: Fazer DrawParcial da mina
    myMine->Draw();
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

void Game::CommandMode()
{
    std::string command;
    bool valid = false;
    int action = 0;

    myConsole->clrscr();


    while (command != "j")
        {
            //Console.clrscr();
            myConsole->gotoxy(10, 42);
            std::cout << "[MODO DE COMANDOS]";
            myConsole->gotoxy(10, 44);
            std::cout << "Comando : _____________________________";
            myConsole->gotoxy(20, 44);
            std::getline(std::cin, command);

            for (int i = 0; i< NUM_COMMANDS; i++)
                {
                    if (command.compare(validCommands[i]) == 0)
                        {
                            valid = true;
                            action = i;
                            break;
                        }
                }

            if (valid == false)
                {
                    myConsole->clrscr();
                    myConsole->gotoxy(10, 42);
                    std::cout << "[MODO DE COMANDOS]";
                    myConsole->gotoxy(10, 44);
                    std::cout << "Comando : _____________________________";
                    myConsole->gotoxy(10, 46);
                    std::cout << "[GAME] -> '" << command << "' nao encontrado.";
                }
            else
                {
                    valid = false;
                    myConsole->clrscr();
                    myConsole->gotoxy(10, 42);
                    std::cout << "[MODO DE COMANDOS]";
                    myConsole->gotoxy(10, 44);
                    std::cout << "Comando : _____________________________";
                    myConsole->gotoxy(10, 46);
                    std::cout << "[GAME] -> '" << command << "' existe.";
                    switch (action)
                        {
                        case 0:
                            break;
                        case 1:
                            break;
                        case 2:
                            break;
                        case 3:
                            break;
                        case 4:
                            break;
                        case 5:
                            break;
                        case 6:
                            break;
                        case 7:
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

void Game::Write(std::string input)
{
    myConsole->clrscr();
    myConsole->gotoxy(14, 2);
    std::cout << input << std::endl;
}

int Game::Status() const
{
    return _currentStatus;
}

const std::string Game::currentDate()
{
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%d%m%Y", &tstruct);
    return buf;
}