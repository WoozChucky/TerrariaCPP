#include "Mine.h"
#include "Utensilio.h"
#include "CommunicatorInterface.h"

class Game
{
private:
    INIReader *reader;
    Consola *myConsole;
    CommunicatorInterface *myCommunicatorInterface;
    Mine *myMine;
    Utensilio myUtensilios[NUM_UTENSILIOS];

    int _currentStatus;

    int vX, vY, pX, pY;

public:

    const static int ACTIVE = 1;
    const static int END = 0;

    /* General */
    Game();  //Constructor
    ~Game(); //Destructor
    void Start();

    /* Sound */
    void PlayIntro();
    void PlayTheme();
    void PlayMine();
    void StopMusic();

    /* Draws */
    void WriteMainMenu();
    void WritePauseMenu();

    /* Game Stats*/
    void NewGame();
    void SaveGame();
    void LoadGame();
    void Play(int _pX, int _pY, int _vX, int _vY);

    /* Menu Interface */
    void Pause();
    void SoundOptions();

    /* Commands */
    void CommandMode();
    void BuyTool(std::string toolName);
    void CreateBlock(int blockType, int X, int Y);
    void Teleport(int X, int Y);

    /* System Option */
    const std::string Game::currentDate();
    std::string GetLoadFilename(int Index);
    void Write(std::string input);

    /* Gets */
    int Status() const;
};