#include "Ghost.h"

#pragma once
class SmartGhost: public Ghost
{

	int age;

public:
	
	~SmartGhost();

	void loadFromFile(ifstream& archivo);
	void PosiblesDirs();

	//GETS
	int getAge() { return age; }
};

