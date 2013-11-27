#include "Mine.h"

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

class Game {

	Game *myGame;
	Miner *myMiner;
	BlockTypes *myBlockTypes;
	//Block* myBlocks[10000];
	Consola *myConsole;
	Mine *myMine;
	int linhas, colunas;
	int _currentStatus;
	
	

public:

	const static int ACTIVE = 1;
	const static int END = 0;

	Game();

	//Sound
	void SoundOptions();
	void PlayIntro();
	void PlayTheme();
	void StopMusic();

	//Write
	void Write(std::string input);
	void WriteMainMenu();
	void WritePauseMenu();

	void Start();
	void NewGame();
	void SaveGame();
	void LoadGame();
	void Play(int playerX = 0, int playerY = 0);
	void Pause();
	void Resume();

	Game Load(Game SavedGame);

	std::string GetLoadFilename(int Index);
	
	void CommandMode();
	
	
	const std::string Game::currentDate();
	int Status() const;
};