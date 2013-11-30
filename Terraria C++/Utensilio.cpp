#include <iostream>
#include <string>

#include "Utensilio.h"

void Utensilio::setCost(int S)
{
    cost = S;
}

void Utensilio::setName(std::string S)
{
    name = S;
}

std::string Utensilio::getName()
{
    return name;
}

int Utensilio::getCost()
{
    return cost;
}

void LoadUtensilios(Utensilio Utensilios[])
{
    std::ifstream utensiliosFile(UTENSILIOS_FILE_NAME, std::ifstream::in);
    std::string nome;
    int cost, K = 0;
    if (utensiliosFile.is_open())
        {
            while (utensiliosFile >> nome >> cost)
                {
                    Utensilios[K].setName(nome);
                    Utensilios[K].setCost(cost);
                    K++;
                }
        }
}