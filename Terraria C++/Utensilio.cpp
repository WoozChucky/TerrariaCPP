#include <iostream>
#include <string>

#include "Utensilio.h"

void Utensilio::setCost(int S){
	cost = S;
}

void Utensilio::setName(std::string S){
	name = S;
}

std::string Utensilio::getName(){
	return name;
}

int Utensilio::getCost(){
	return cost;
}