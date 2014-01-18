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

std::string Utensilio::getName() const
{
    return name;
}

int Utensilio::getCost() const
{
    return cost;
}

void LoadUtensilios(Utensilio Utensilios[], int Difficulty)
{
    std::ifstream utensiliosFile(UTENSILIOS_FILE_NAME, std::ifstream::in);
    std::string nome;
    int cost, K = 0;
    if (utensiliosFile.is_open())
        {
            switch (Difficulty)
                {
                case 1:
                    while (utensiliosFile >> nome >> cost)
                        {
                            Utensilios[K].setName(nome);
                            Utensilios[K].setCost(cost);
                            K++;
                        }
                    break;
                case 2:
                    while (utensiliosFile >> nome >> cost)
                        {
                            Utensilios[K].setName(nome);
                            Utensilios[K].setCost(cost + (cost / 2));
                            K++;
                        }
                    break;
                case 3:
                    while (utensiliosFile >> nome >> cost)
                        {
                            Utensilios[K].setName(nome);
                            Utensilios[K].setCost(cost * 2);
                            K++;
                        }
                    break;
                }
        }
}