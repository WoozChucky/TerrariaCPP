
/* Funcoes da consola. Dez 2010 */

/* Pequenas correcoes. Nov. 2013 */

#include "Consola.h"                      
#include <windows.h>
#include <stdio.h>

Consola::Consola() {
	hconsola = GetStdHandle(STD_OUTPUT_HANDLE);
	hStdin = GetStdHandle(STD_INPUT_HANDLE);
	hwnd = GetConsoleWindow(); // NT upwards. Nem queiram saber como seria para 95 e 98
}

void Consola::gotoxy(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(hconsola, coord);
}

void Consola::clrscr() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	const COORD startCoords = { 0, 0 };
	DWORD dummy;

	GetConsoleScreenBufferInfo(hconsola, &csbi);
	FillConsoleOutputCharacter(hconsola,
		' ',
		csbi.dwSize.X * csbi.dwSize.Y,
		startCoords,
		&dummy);
	FillConsoleOutputAttribute(hconsola,
		csbi.wAttributes,
		csbi.dwSize.X * csbi.dwSize.Y,
		startCoords,
		&dummy);
	gotoxy(0, 0);
}

void Consola::setTextColor(WORD color) {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hconsola, &csbi);
	WORD cor = csbi.wAttributes;
	cor &= 0xFFF0;
	cor |= color;
	// duvidas acerca destas duas linhas -> TI ou TAC
	SetConsoleTextAttribute(hconsola, cor);
	return;
}

void Consola::setBackgroundColor(WORD color) {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hconsola, &csbi);
	WORD cor = csbi.wAttributes;
	cor &= 0xFF0F;
	cor |= (color << 4);
	// duvidas acerca destas duas linhas -> TI ou TAC
	SetConsoleTextAttribute(hconsola, cor);
}

void Consola::setScreenSize(int nLinhas, int nCols) {
	COORD tam;
	SMALL_RECT DisplayArea;

	tam.X = nCols;
	tam.Y = nLinhas;
	SetConsoleScreenBufferSize(hconsola, tam);   // isto muda o tamanho da matriz de caracteres

	DisplayArea.Top = 0;
	DisplayArea.Left = 0;
	DisplayArea.Bottom = nLinhas - 1;
	DisplayArea.Right = nCols - 1;
	SetConsoleWindowInfo(hconsola, TRUE, &DisplayArea);  // isto muda o tamanho da area da janela em caracteres
}

// usar esta de preferência a não ser que se esteja no XP ou anterior
void Consola::setTextSize(int x, int y) {
	CONSOLE_FONT_INFOEX cfont;

	cfont.cbSize = sizeof(CONSOLE_FONT_INFOEX);

	GetCurrentConsoleFontEx(hconsola, false, &cfont);
	cfont.dwFontSize.X = x;
	cfont.dwFontSize.Y = y;
	SetCurrentConsoleFontEx(hconsola, false, &cfont);
}


char Consola::getch(void) {
	INPUT_RECORD irInputRecord;
	DWORD dwEventsRead;
	CHAR cChar;

	while (ReadConsoleInputA(hStdin, &irInputRecord, 1, &dwEventsRead)) /* Read key press */
	if (irInputRecord.EventType == KEY_EVENT
		&& irInputRecord.Event.KeyEvent.wVirtualKeyCode != VK_SHIFT
		&& irInputRecord.Event.KeyEvent.wVirtualKeyCode != VK_MENU
		&& irInputRecord.Event.KeyEvent.wVirtualKeyCode != VK_CONTROL)
	{

		cChar = irInputRecord.Event.KeyEvent.uChar.AsciiChar;
		ReadConsoleInputA(hStdin, &irInputRecord, 1, &dwEventsRead); /* Read key release */

		if (irInputRecord.Event.KeyEvent.wVirtualKeyCode == VK_LEFT) return ESQUERDA;
		if (irInputRecord.Event.KeyEvent.wVirtualKeyCode == VK_RIGHT) return DIREITA;
		if (irInputRecord.Event.KeyEvent.wVirtualKeyCode == VK_UP) return CIMA;
		if (irInputRecord.Event.KeyEvent.wVirtualKeyCode == VK_DOWN) return BAIXO;

		return cChar;
	}
	return EOF;
}


// setTextSize - Usar isto apenas se a outra não funcionar (XP ou menos)
// O método de funcionamento é bastante força-bruta
//   Procura uma fonte que cumpra os requisitos do novo tamanho
//   e muda para essa fonte (ou seja, muda tambéma fonte)
// Funções que a MS nem se deu ao trabalho de documentar
// Help: http://blogs.microsoft.co.il/blogs/pavely/archive/2009/07/23/changing-console-fonts.aspx
typedef BOOL(WINAPI * SetConsoleFont_)(HANDLE ConsoleOutput, DWORD FontIndex); // kernel32!SetConsoleFont
typedef BOOL(WINAPI * GetConsoleFontInfo_)(HANDLE ConsoleOutput, BOOL Unknown1, DWORD Unknown2, PCONSOLE_FONT_INFO ConsoleFontInfo); // kernel32!GetConsoleFontInfo
typedef DWORD(WINAPI * GetNumberOfConsoleFonts_)(); // kernel32!GetNumberOfConsoleFonts


void Consola::setTextSizeXP(int x, int y){
	// Configura acesso às funções "secretas" do Windows
	SetConsoleFont_ SetConsoleFont = reinterpret_cast<SetConsoleFont_>(GetProcAddress(GetModuleHandle(L"kernel32.dll"), "SetConsoleFont"));
	GetConsoleFontInfo_ GetConsoleFontInfo = reinterpret_cast<GetConsoleFontInfo_>(GetProcAddress(GetModuleHandle(L"kernel32.dll"), "GetConsoleFontInfo"));
	GetNumberOfConsoleFonts_ GetNumberOfConsoleFonts = reinterpret_cast<GetNumberOfConsoleFonts_>(GetProcAddress(GetModuleHandle(L"kernel32.dll"), "GetNumberOfConsoleFonts"));

	// Num de fontes
	DWORD NumFonts = GetNumberOfConsoleFonts();

	// alloca matriz de cont infos
	CONSOLE_FONT_INFO* ConsoleInfo = new CONSOLE_FONT_INFO[sizeof(CONSOLE_FONT_INFO)* NumFonts];

	// obtem info das fontes todas
	GetConsoleFontInfo(hconsola, FALSE, NumFonts, ConsoleInfo);

	// percorre-as todas. O melhor é não chamar isto muitas vezes
	for (size_t i = 0; i < NumFonts; ++i) {
		// Indaga o tamanho (suportado) da fonte. Pode não haver nenhuma para esse tamanho
		ConsoleInfo[i].dwFontSize = GetConsoleFontSize(GetStdHandle(STD_OUTPUT_HANDLE), ConsoleInfo[i].nFont);

		// Encontrou uma. muda para essa e já está (mesmo que haja outras)
		if (ConsoleInfo[i].dwFontSize.X == x && ConsoleInfo[i].dwFontSize.Y == y) {
			// x,y = tamanho desejado (se houver)
			// muda para essa fonte e sai
			SetConsoleFont(GetStdHandle(STD_OUTPUT_HANDLE), ConsoleInfo[i].nFont);
			break;
		}
	}

	// devolve a matriz de INFO
	delete[] ConsoleInfo;
}


// estas funcoes servem para pouco a nao ser que nao se tape/destape a janela
// o refresh da janela da consola não reactualiza isto
// por esse motivo nao achei que valesse apena optimizar certos aspectos delas
void Consola::drawLine(int x1, int y1, int x2, int y2, int cor){
	HDC DrawHDC;
	HPEN hOPen;  // penstyle, width, color
	HPEN hNPen = CreatePen(PS_SOLID, 2, cor);
	DrawHDC = GetDC(hwnd);
	hOPen = (HPEN)SelectObject(DrawHDC, hNPen);  // inicio da linha
	MoveToEx(DrawHDC, x1, y1, NULL);  // fim da linha
	LineTo(DrawHDC, x2, y2);
	DeleteObject(SelectObject(DrawHDC, hOPen));
	ReleaseDC(hwnd, DrawHDC);
}

// converte circle(centerX,centerY,radius,pen) para a WinApi
void Consola::drawCircle(int X, int Y, int R, int Pen, int Fill){
	HDC DrawHDC;
	DrawHDC = GetDC(hwnd);  // penstyle, width, color
	HPEN   hNPen = CreatePen(PS_SOLID, 2, Pen);
	HPEN   hOPen = (HPEN)SelectObject(DrawHDC, hNPen);
	HBRUSH hOldBrush;
	HBRUSH hNewBrush;  // true  preenche o circulo com a cor
	if (Fill) {
		hNewBrush = CreateSolidBrush(Pen);
		hOldBrush = (HBRUSH)SelectObject(DrawHDC, hNewBrush);
	}
	else {
		hNewBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		hOldBrush = (HBRUSH)SelectObject(DrawHDC, hNewBrush);
	}
	Ellipse(DrawHDC, X - R, Y + R, X + R, Y - R);
	DeleteObject(SelectObject(DrawHDC, hOPen));
	DeleteObject(SelectObject(DrawHDC, hOldBrush));
	ReleaseDC(hwnd, DrawHDC);  // torna-se lento
}

//Consola Console;