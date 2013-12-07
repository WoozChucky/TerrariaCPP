#include "Block.h"

class Game : public Block
{

    Game *myGame;
    Miner *myMiner;
    Consola *myConsole;
    Block ***myMine;
    int _linhas, _colunas, _vision;
    int _currentStatus;

public:

    const static int ACTIVE = 1;
    const static int END = 0;

    Game();

    void InitializeMine(int Rows, int Cols, int Vision);
    void DrawMine(int startDrawX, int startDrawY);

    void RemoveBlock(Block * &bloco);

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
    void Play();
    void Pause();
    void Resume();

    Game Load(Game SavedGame);

    std::string GetLoadFilename(int Index);

    void CommandMode();


    const std::string Game::currentDate();
    int Status() const;
};