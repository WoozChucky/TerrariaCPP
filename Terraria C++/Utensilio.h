#include <iostream>
#include <string>

class Utensilio {
	std::string name;
	int cost;
public:
	void setName(std::string S);
	void setCost(int S);

	std::string getName();
	int getCost();
};