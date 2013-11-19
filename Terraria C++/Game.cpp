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
	myConsole = new Consola();
	myBlockTypes = new BlockTypes();
	myMiner = new Miner(0, 0);
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
	while (1) {
		tecla = myConsole->getch();
		if (tecla == ESCAPE) break;
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
	case EXIT_GAME:
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

	linhas = nLinhas; // +6 for stats
	colunas = nColunas;

	myConsole->clrscr();

	myMine->Initialize(linhas * 4, colunas * 5);
	myMine->Draw(*myConsole);

	StopMusic();
	PlayTheme();

	Play();
}

void Game::LoadGame()
{
	myConsole->clrscr();
	myConsole->gotoxy(14, 2);

	std::cout << "Under Development";
	system("pause");
}

void Game::Play()
{
	char tecla;

	int x = ((colunas / 2) * 5) + 1, y = (linhas / 2) * 4; //Character Start Position
	int wX = (7 / 2) * 5, wY = (7 / 2) * 4; //Scroll Boundings
	int vX = x, vY = y; //Camera Start Position
	
	//myConsole->setScreenBufferSize(linhas * 4, colunas * 5);
	myConsole->setScreenSize(7 * 4, 7 * 5);	

	if (_currentStatus != ACTIVE)
		_currentStatus = END;

	while (myMiner->hasLifes())
	{
		myMiner->isAlive(*myConsole);
		//myMiner->showStats(*myConsole);
		myMiner->Show(*myConsole, x, y);

		myConsole->gotoxy(vX, vY);

		tecla = myConsole->getch();

		switch (tecla)
		{
		case C:
			CommandMode();
			myMiner->Show(*myConsole, x, y);
			break;
		case UP:
			//Mineiro.DeleteStats(Console,  x);
			if (y >= 9)
			{
				myMiner->Move(*myConsole, x, y);
				y -= 4;

				vX = x;
				vY = (y - 3 > wY) ? (y - wY) : 0;
			}
			break;
		case DOWN:
			
			//Mineiro.DeleteStats(Console, x);
			if (y < (linhas * 4) - 4)
			{
				myMiner->Move(*myConsole, x, y);
				y += 4;
				vX = x;
				vY = (y + 3 < (linhas * 4) - wY) ? y + wY + 3 : (linhas * 4) - 1;
			}
			break;
		case RIGHT:
			
			//Mineiro.DeleteStats(Console, x);
			if (x < (colunas * 5) - 5)
			{
				myMiner->Move(*myConsole, x, y);
				x += 5;
				vY = y;
				vX = (x + 4 < (colunas * 5) - wX) ? x + wX + 4 : (colunas * 5) - 1;
			}
			break;
		case LEFT:
			
			//Mineiro.DeleteStats(Console, x);
			
			if (x > 2)
			{
				myMiner->Move(*myConsole, x, y);
				x -= 5;
				vY = y;
				vX = (x - 4 > wX) ? x - wX : 0;
			}
			break;
		}
	}
	_currentStatus = END;
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


	while (command != "j") {
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