#pragma once

/*
TODO:
	1º OffSet
*/

/* Socket Librarys */
#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <ws2tcpip.h>

/* General Librarys */
#include <vector>
#include <string>
#include <stdio.h>
#include <array>
#include <typeinfo> //class name 2 string
#include <random>

/* Windows Librarys */
#include <cstdio>
#include <windows.h>
#include "mmsystem.h"
#include <dshow.h>
#include <conio.h>
#include <dos.h>

/* Time Librarys */
#include <ctime>
#include <time.h>

/* Stream Librarys */
#include <fstream>
#include <iostream>
#include <sstream>
#include <istream>

/* Sock Libs*/
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")
/*Sound Libs*/
#pragma comment(lib, "strmiids.lib")
#pragma comment(lib, "winmm.lib")

/* Blocks */
enum BlockIDS
{
    P = 1, //Pedra
    TM = 2, //Terreno Mole
    TD = 3, //Terreno Duro
    TcA = 4, //Terra c Aluminio
    TcC = 5, //Terra c Carvao
    TcF = 6, //Terra c Ferro
    TcO = 7, //Terra c Ouro
    TcD = 8, //Terra c Diamante
    TcFAF = 9, //Terra c Frango Assado Fossilizado
    ESC = 10, //Escada
    VIG = 11, //Viga
    NULLED = 12 //Vazio
};

/* General */
#define NUM_COMMANDS 11
#define VISION 2

/* Menu Coordinates */
#define NEW_GAME 10
#define RESUME_GAME 10
#define UNMUTE 10
#define MUTE 12
#define SOUND_OPTIONS 12
#define LOAD_GAME 12
#define EXIT_GAME 16
#define SAVE_GAME 14

/* Networking */
#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"
#define DEFAULT_IP "10.65.130.190"

/*Miner Default Stats*/
#define SHOW 1
#define REMOVE 0
#define FULL 15

/* Console Chars Keys */
#define LEFT 1
#define RIGHT 2
#define UP 3
#define DOWN 4
#define ENTER 13
#define ESCAPE 27
#define _C_ 99
#define D 100
#define E 101
#define _S_ 115
#define V 118
#define _X_ 120

//for (int r = 0, startDrawY = piY; r < 7; r++, startDrawY++)
//{
//	for (int c = 0, startDrawX = piX; c < 7; c++, startDrawX++)
//	{
//		(startDrawY >= piY && startDrawY <= pfY && startDrawX >= piX && startDrawX <= pfX) ? DrawBlock(myMine[startDrawY][startDrawX]->getID(), c * 5, r * 5) : 0;
//	}
//}