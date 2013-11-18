#include <iostream>
#include <istream>
#include <fstream>
#include <string>

#include "Block.h"
#include "Utensilio.h"

#define NUM_UTENSILIOS 19
#define UTENSILIOS_FILE_NAME "utensilios.txt"
#define NEW_GAME 10
#define LOAD_GAME 12
#define EXIT_GAME 14

void LoadUtensilios(Utensilio Utensilios[])
{
	std::ifstream utensiliosFile(UTENSILIOS_FILE_NAME, std::ifstream::in);
	std::string nome;
	int cost, K=0;

	if (utensiliosFile.is_open())
	{
		while (utensiliosFile >> nome >> cost) {
			Utensilios[K].setName(nome);
			Utensilios[K].setCost(cost);
			K++;
		}
	}
}

void main()
{
	Consola Console;
	Menu Menu;
	Miner Mineiro(27, 19);
	Utensilio Utensilios[NUM_UTENSILIOS];
	BlockTypes TiposBlocos(
		{ "Pedra", "Terreno duro", "Terreno mole", "Ouro", "Lava" }, 
		{ 0, 1, 2, 3, 4 }, 
		{ false, true, true, true, false }
	);

	Block pedra1(Console, TiposBlocos.getName(0), 0, TiposBlocos.isBrekeable(0), 3, 12);
	Block pedra2(Console, TiposBlocos.getName(0), 0, TiposBlocos.isBrekeable(0), 3, 16);
	Block pedra3(Console, TiposBlocos.getName(0), 0, TiposBlocos.isBrekeable(0), 8, 12);

	int userChoice;
	char tecla;
	

	Console.setTextColor(Console.PRETO);
	Console.setBackgroundColor(Console.BRANCO_CLARO);

	/* Loads utensilios data into array of objects*/
	LoadUtensilios(Utensilios);
	
	userChoice = Menu.LoadMainMenu(Console);

	switch (userChoice)
	{
	case NEW_GAME:
		Menu.NewGame(Console);
		
		break;
	case LOAD_GAME:
		Menu.LoadGame(Console);
		break;
	case EXIT_GAME:
		exit(0);
		break;
	}

	int x = (Console.getLinhas() / 2), y = (Console.getColunas() / 2), vX = (Console.getLinhas() / 2), vY = (Console.getColunas() / 2);
	Console.clrscr();
	pedra1.Draw(Console);
	pedra2.Draw(Console);
	pedra3.Draw(Console);

	/* Game Running */
	while (Mineiro.hasLifes()){		

		Mineiro.isAlive(Console);
		Mineiro.showStats(Console);
		Mineiro.Show(Console, x, y);

		Console.gotoxy(vX, vY);

		tecla = Console.getch();

		switch (tecla)
		{
		case Console.C:
			Menu.CommandMode(Console);
			Mineiro.Show(Console, x, y);
			break;
		case Console.CIMA:
			Mineiro.Move(Console, x, y);
			y -= 4;
			if (y <= 5)
				y = Mineiro.getY();

			vX = x;
			vY = y - ((Console.getLinhas() /2 ) * 4) - 4;
			break;
		case Console.BAIXO:
			Mineiro.Move(Console, x, y);
			y += 4;

			vX = x;
			vY = y + ((Console.getLinhas() / 2) * 4) + 4;
			break;
		case Console.DIREITA:
			Mineiro.Move(Console, x, y);
			x += 5;
			
			vY = y;
			vX = x + 11;
			break;
		case Console.ESQUERDA:
			Mineiro.Move(Console, x, y);
			x -= 5;
			if (x <= 1)
			{
				x = Mineiro.getX();
			}

			if (vX <= 1)
			{
				vX = 1;
			}

			vY = y;
			vX = x - 11;
			break;
		}
	}

	Console.clrscr();
	Console.gotoxy(10, 18);
	Console.setTextSize(30, 30);
	std::cout << "Game Over";

	Console.getch();
	exit(0);
	
	// RGB -> macro. valores entre 0 e 255 
	Console.drawLine(0, 0, 300, 200, RGB(255, 0, 0));
	Console.drawCircle(150, 130, 105, RGB(0, 0, 255), 1);
	Console.drawCircle(200, 130, 75, RGB(50, 255, 50), 0);

	Console.gotoxy(0, 34);
	Console.setTextColor(Console.AMARELO_CLARO);
	std::cout << "Desenho de pixels e possivel mas nao e suportado\n";
	std::cout << "Sao disponibilizadas algumas funcoes para esse efeito";
	std::cout << "\nmas o resultado nao fica \"memorizado\" na janela\n";
	std::cout << "(depois em SO2 resove-se isso)\n";
	std::cout << "\n\nEscolhendo com cuidado as coordenadas pode-se fazer os desenhos coincidir\n";
	std::cout << "com os limites dos caracteres\n";
	std::cout << "\nCaracteres com a mesma altura que a largura melhoram a apresentacao\n";
	std::cout << "\n\ncarrega numa tecla qualquer";
	Console.getch();

	Console.setBackgroundColor(Console.CINZENTO);
	Console.setTextColor(Console.BRANCO_CLARO);
	Console.clrscr();  // reparar no Console.   trata-se de funções da biblioteca de Consolda (para POO)
	Console.gotoxy(10, 4);
	std::cout << "Tabela com caracteres.";
	Console.gotoxy(10, 5);
	std::cout << "Reparar que muitos podem ser usados para desenhar molduras e afins";
	Console.gotoxy(10, 6);
	std::cout << "Outros podem ser como tonalidades";

	for (int i = 0; i< 16; i++) {
		for (int j = 0; j<16; j++) {
			Console.gotoxy(20 + j * 3, 9 + i * 2);
			std::cout << (char)(i * 16 + j);
		}
	}

	Console.setTextColor(Console.VERMELHO);
	Console.gotoxy(10, 40);
	std::cout << "\n\tNotar os seguintes\n\n";
	std::cout << "\t" << (char)176 << ' ' << (char)177 << ' ' << (char)178 << '\n';
	std::cout << "\n\t";
	std::cout << (char)179 << ' ' << (char)180 << ' ';
	for (int i = 192; i<198; i++) std::cout << (char)i << ' ';
	for (int i = 200; i<207; i++) std::cout << (char)i << ' ';
	std::cout << "\n\n\tcarrega numa tecla qualquer para ver exemplos";
	Console.getch();

	Console.setTextColor(Console.PRETO);
	Console.setBackgroundColor(Console.BRANCO_CLARO);
	Console.clrscr();

	Console.gotoxy(20, 20);
	std::cout << (char)218 << (char)196 << (char)196 << (char)196 << (char)191 << '\n';
	Console.gotoxy(20, 21);
	std::cout << (char)179 << (char)176 << (char)176 << (char)176 << (char)179 << '\n';
	Console.gotoxy(20, 22);
	std::cout << (char)179 << (char)176 << (char)176 << (char)176 << (char)179 << '\n';
	Console.gotoxy(20, 23);
	std::cout << (char)179 << (char)176 << (char)176 << (char)176 << (char)179 << '\n';
	Console.gotoxy(20, 24);
	std::cout << (char)192 << (char)196 << (char)196 << (char)196 << (char)217 << '\n';


	Console.gotoxy(25, 20);
	std::cout << (char)218 << (char)196 << (char)196 << (char)196 << (char)191 << '\n';
	Console.gotoxy(25, 21);
	std::cout << (char)179 << (char)177 << (char)177 << (char)177 << (char)179 << '\n';
	Console.gotoxy(25, 22);
	std::cout << (char)179 << (char)177 << (char)177 << (char)177 << (char)179 << '\n';
	Console.gotoxy(25, 23);
	std::cout << (char)179 << (char)177 << (char)177 << (char)177 << (char)179 << '\n';
	Console.gotoxy(25, 24);
	std::cout << (char)192 << (char)196 << (char)196 << (char)196 << (char)217 << '\n';


	Console.gotoxy(30, 20);
	std::cout << (char)218 << (char)196 << (char)196 << (char)196 << (char)191 << '\n';
	Console.gotoxy(30, 21);
	std::cout << (char)179 << (char)178 << (char)178 << (char)178 << (char)179 << '\n';
	Console.gotoxy(30, 22);
	std::cout << (char)179 << (char)178 << (char)178 << (char)178 << (char)179 << '\n';
	Console.gotoxy(30, 23);
	std::cout << (char)179 << (char)178 << (char)178 << (char)178 << (char)179 << '\n';
	Console.gotoxy(30, 24);
	std::cout << (char)192 << (char)196 << (char)196 << (char)196 << (char)217 << '\n';

	Console.gotoxy(35, 20);
	std::cout << (char)218 << (char)196 << (char)196 << (char)196 << (char)191 << '\n';
	Console.gotoxy(35, 21);
	std::cout << (char)179 << (char)219 << (char)219 << (char)219 << (char)179 << '\n';
	Console.gotoxy(35, 22);
	std::cout << (char)179 << (char)219 << (char)219 << (char)219 << (char)179 << '\n';
	Console.gotoxy(35, 23);
	std::cout << (char)179 << (char)219 << (char)219 << (char)219 << (char)179 << '\n';
	Console.gotoxy(35, 24);
	std::cout << (char)192 << (char)196 << (char)196 << (char)196 << (char)217 << '\n';

	Console.setTextColor(Console.VERDE);
	std::cout << "\n\n\t\tAgora e uma questao de criatividade";
	Console.setTextColor(Console.PRETO);
	std::cout << "\n\n\t\tCarrega numa tecla qualquer";
	Console.getch();
	return;
}