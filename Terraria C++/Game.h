#include "Mine.h"
#include "Utensilio.h"

class Game : public Drawer
{
private:
    Consola *myConsole;
    Drawer *myDrawer;
    Mine **minesGrid;
    Utensilio myUtensilios[NUM_UTENSILIOS];
    //Mine *myMine;
    int _currentStatus;

    int activeMines, currentMine;

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
    void PlayFalling();
    void StopMusic();

    /* Movement Handling*/
    void ApplyGravity();
    void MoveUp();
    void MoveDown();
    void MoveLeft();
    void MoveRight();

    /* Game Stats*/
    void NewGame(std::string Name, int Rows, int Columns, int Difficulty);
    void SaveGame(std::string filename);
    void LoadGame(std::string filename);
    void LoadGameMenu();
    void Play();

    /* Menu Interface */
    void Pause();
    void SoundOptions();

    /* Commands */
    void CommandMode();
    void BuyTool(std::string toolName);
    void CreateBlock(std::string blockType, int X, int Y);
    void Teleport(int X, int Y);

    /* System Option */
    const std::string Game::currentDate();
    std::string GetLoadFilename(int Index);
    void Write(std::string input);

    /* Gets */
    int Status() const;
};