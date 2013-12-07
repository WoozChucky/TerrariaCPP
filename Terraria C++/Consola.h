
/* Funcoes da consola. Dez 2010 */

/* Pequenas correcoes. Nov. 2013 */

#ifndef __CONSOLA_H__
#define __CONSOLA_H__

#include "Core.h"

class Consola
{

    HANDLE hconsola;
    HANDLE hStdin;
    HWND hwnd;

public:

    // para usar nas cores
    const static int PRETO = 0;
    const static int AZUL = 1;
    const static int VERDE = 2;
    const static int CYAN = 3;
    const static int VERMELHO = 4;
    const static int ROXO = 5;
    const static int AMARELO = 6;
    const static int BRANCO = 7;
    const static int CINZENTO = 8;
    const static int AZUL_CLARO = 9;
    const static int VERDE_CLARO = 10;
    const static int CYAN_CLARO = 11;
    const static int VERMELHO_CLARO = 12;
    const static int COR_DE_ROSA = 13;
    const static int AMARELO_CLARO = 14;
    const static int BRANCO_CLARO = 15;

    // para usar em getch
    const static char ESQUERDA = 1;
    const static char DIREITA = 2;
    const static char CIMA = 3;
    const static char BAIXO = 4;

    Consola();
    void gotoxy(int x, int y);
    void clrscr();
    void setTextColor(WORD color);
    void setBackgroundColor(WORD color);
    void setScreenSize(int nLinhas, int nCols);
    void setScreenBufferSize(int Linhas, int Colunas); //implemented
    void setTextSize(int x, int y);
    void setTextSizeXP(int x, int y);
    char getch(void);
    void drawLine(int x1, int y1, int x2, int y2, int cor);
    void drawCircle(int X, int Y, int R, int Pen, int Fill);

    HWND NewWindow(LPCTSTR str_Title, int int_XPos, int int_YPos, int int_Width, int int_Height); //implemented
};

#endif