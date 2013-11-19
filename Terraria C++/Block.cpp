#include "Block.h"



Block::Block(std::string Name, int ID, bool Breakable, int X, int Y)
{
	name = Name;
	id = ID;
	breakable = Breakable;
	x = X;
	y = Y;
}

void Block::Draw(Consola Console)
{
	/* Left Side */
	Console.gotoxy(x + 3, y - 2);
	//std::cout << (char)191 << (char)196 << (char)196 << (char)196 << (char)196 << (char)218;

	Console.gotoxy(x - 2, y - 2);
	std::cout << (char)218 << (char)196 << (char)196 << (char)196  << (char)191;

	Console.gotoxy(x - 2, y - 1);
	std::cout << (char)179 << (char)219 << (char)219 << (char)219 << (char)179;

	Console.gotoxy(x - 2, y);
	std::cout << (char)179 << (char)219  << (char)219 << (char)219 << (char)179;

	Console.gotoxy(x - 2, y + 1);
	std::cout << (char)192 << (char)196 << (char)196 << (char)196 << (char)217;

	/*Console.gotoxy(x - 2, y + 1);
	std::cout << (char)179;
	Console.gotoxy(x - 2, y);
	std::cout << (char)179;
	Console.gotoxy(x - 2, y - 1);
	std::cout << (char)179;*/

	/* Right Side*/
	/*Console.gotoxy(x + 3, y + 2);
	std::cout << (char)179;
	Console.gotoxy(x + 3, y + 1);
	std::cout << (char)179;
	Console.gotoxy(x + 3, y);
	std::cout << (char)179;
	Console.gotoxy(x + 3, y - 1);
	std::cout << (char)179;*/

	/* Bottom Side */
	/*Console.gotoxy(x + 3, y + 2);
	std::cout << (char)196;
	std::cout << (char)196;
	std::cout << (char)196;
	std::cout << (char)196;
	std::cout << (char)192;*/

	/* Top Side */
	
}