#include "Mine.h"

#define NEW_GAME 10
#define LOAD_GAME 12
#define EXIT_GAME 14

#define NUM_COMMANDS 10

#define C 99
#define ESCAPE 27
#define LEFT 1
#define RIGHT 2
#define UP 3
#define DOWN 4
#define ENTER 13

class Game {

	Miner *myMiner;
	BlockTypes *myBlockTypes;
	Block* myBlocks[10000];
	Consola *myConsole;
	Mine *myMine;
	//Block
	int linhas, colunas;
	int _currentStatus;
	
	void WriteMainMenu();

public:

	const static int ACTIVE = 1;
	const static int END = 0;

	Game();

	void Start();
	void NewGame();
	void LoadGame();
	void Play();
	void CommandMode();
	void Write(std::string input);
	void PlayIntro();
	void PlayTheme();
	void StopMusic();
	
	int Status() const;
};