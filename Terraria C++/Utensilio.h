#include <iostream>
#include <istream>
#include <fstream>
#include <string>

#define NUM_UTENSILIOS 19
#define UTENSILIOS_FILE_NAME "Data/tools.ini"

class Utensilio
{
    std::string name;
    int cost;
public:
    void setName(std::string S);
    void setCost(int S);

    std::string getName();
    int getCost();
};

void LoadUtensilios(Utensilio Utensilios[], int Difficulty);