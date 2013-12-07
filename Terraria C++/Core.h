#ifndef __CORE_H__
#define __CORE_H__

/*
TODO:
	1º Boundings - check
	2º UpdateBlock - check
	3º OffSet
	4º Colisao - semi-check
	5º Desenhar Blocos
*/

/* General */
#include <vector>
#include <string>

/* Windows */
#include <cstdio>
#include <windows.h>
#include "mmsystem.h"
#include <dshow.h>
#include<conio.h>
#include<dos.h>

/* Time */
#include <ctime>
#include <time.h>

/* Streams */
#include <fstream>
#include <iostream>
#include <sstream>
#include <istream>

/* Blocks */
enum BlockIDS
{
    M = 0, //Mineiro
    P = 1, //Pedra
    TM = 2, //Terreno Mole
    TD = 3, //Terreno Duro
    TcA = 4, //Terra c Aluminio
    TcC = 5, //Terra c Carvao
    TcF = 6, //Terra c Ferro
    TcO = 7, //Terra c Ouro
    TcD = 8, //Terra c Diamante
    TcFAF = 9, //Terra c Frango Assado Fossilizado
    E = 10, //Escada
    V = 11 //Viga
};

#define NEW_GAME 10
#define RESUME_GAME 10
#define UNMUTE 10
#define MUTE 12
#define SOUND_OPTIONS 12
#define LOAD_GAME 12
#define EXIT_GAME 16
#define SAVE_GAME 14

#define NUM_COMMANDS 10

#define C 99
#define ESCAPE 27
#define LEFT 1
#define RIGHT 2
#define UP 3
#define DOWN 4
#define ENTER 13

#pragma comment(lib, "strmiids.lib")
#pragma comment(lib, "winmm.lib")

#endif