#include <iostream>
#include <istream>
#include <fstream>
#include <string>


/* Tools */
#define NUM_UTENSILIOS 20
#define UTENSILIOS_FILE_NAME "Data/tools.ini"

class Utensilio
{
    std::string name;
    int cost;
public:
    void setName(std::string S);
    void setCost(int S);

    std::string getName() const;
    int getCost() const;
};

void LoadUtensilios(Utensilio Utensilios[], int Difficulty);