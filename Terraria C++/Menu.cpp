#include <iostream>
#include <istream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <string.h>
#include "Menu.h"

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

int Menu::LoadMainMenu(Consola Console)
{
	char tecla;

	Console.setScreenSize(50, 80);
	Console.clrscr();

	this->EscreverMainMenu(Console);

	int x = 8, y = 10;
	Console.gotoxy(x, y);
	std::cout << '>';
	while (1) {
		tecla = Console.getch();
		if (tecla == Console.ESCAPE) break;
		if (tecla == Console.ENTER && y == 10) break;
		if (tecla == Console.ENTER && y == 12) break;
		if (tecla == Console.ENTER && y == 14) break;
		if (tecla != Console.CIMA && tecla != Console.BAIXO) continue;

		Console.gotoxy(x, y);
		std::cout << ' ';

		if (tecla == Console.CIMA) y -= 2;
		if (tecla == Console.BAIXO) y += 2;
		if (y < 10) y = 10;
		if (y > 14) y = 14;
		Console.gotoxy(x, y);
		std::cout << '>';
	}
	return y;
}

void Menu::EscreverMainMenu(Consola Console)
{
	Console.gotoxy(14, 2);
	std::cout << "Bem vindo ao Terraria";
	Console.gotoxy(10, 8);
	std::cout << "** Escolhe uma opcao **";
	Console.gotoxy(10, 10);
	std::cout << "Novo Jogo";
	Console.gotoxy(10, 12);
	std::cout << "Carregar Jogo";
	Console.gotoxy(10, 14);
	std::cout << "Sair";
}

void Menu::NewGame(Consola Console)
{
	Console.clrscr();
	Console.gotoxy(14, 2);
	std::cout << "Criacao Novo Jogo";
	std::cout << std::endl;
	std::cout << "<Gemas> : " << std::endl;
}

void Menu::LoadGame(Consola Console)
{
	Console.clrscr();
	Console.gotoxy(14, 2);
	std::cout << "Carregar Jogo";
}

void Menu::CommandMode(Consola Console)
{
	std::string command;
	bool valid = false;
	int action = 0;

	Console.clrscr();
	

	while (command != "j") {
		//Console.clrscr();
		Console.gotoxy(10, 42);
		std::cout << "[MODO DE COMANDOS]";
		Console.gotoxy(10, 44);
		std::cout << "Comando : _____________________________";
		Console.gotoxy(20, 44);
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
			Console.clrscr();
			Console.gotoxy(10, 42);
			std::cout << "[MODO DE COMANDOS]";
			Console.gotoxy(10, 44);
			std::cout << "Comando : _____________________________";
			Console.gotoxy(10, 46);
			std::cout << "[GAME] -> '" << command << "' nao encontrado.";
		}
		else
		{
			valid = false;
			Console.clrscr();
			Console.gotoxy(10, 42);
			std::cout << "[MODO DE COMANDOS]";
			Console.gotoxy(10, 44);
			std::cout << "Comando : _____________________________";
			Console.gotoxy(10, 46);
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
				Console.clrscr();
				exit(0);
				break;
			case 9:
				Console.clrscr();
				return;
				break;
			}
			//command = strtok(command, " "); stringstream
		}
	}
	Console.clrscr();
	return;
}