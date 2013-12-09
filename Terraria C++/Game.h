#include "Block.h"
#include "Utensilio.h"

class Game : public Block
{
    Utensilio myUtensilios[NUM_UTENSILIOS];
    Game *myGame;
    Miner *myMiner;
    Consola *myConsole;
    Block ***myMine;
    int _linhas, _colunas, _vision;
    int _currentStatus;

public:

    const static int ACTIVE = 1;
    const static int END = 0;

    /* General */
    Game(); //Constructor
    void InitializeMine(int Rows, int Cols, int Vision);
    void Start();

    /* Sound */
    void PlayIntro();
    void PlayTheme();
    void StopMusic();

    /* Draws */
    void DrawMine(int startDrawX, int startDrawY);
    void RemoveBlock(int &bX, int &b, int DIRECTION);
    void WriteMainMenu();
    void WritePauseMenu();

    /* Game Stats*/
    void NewGame();
    void SaveGame();
    void LoadGame();
    void Play();
    void EndGame();

    /* Menu Interface */
    void Pause();
    void Resume();
    void SoundOptions();
    void CommandMode();

    /*System Option */
    const std::string Game::currentDate();
    std::string GetLoadFilename(int Index);
    void Write(std::string input);

    /* Collision Detection */
    bool isColliding(int pY, int pX);

    /* Gets */
    int Status() const;
};