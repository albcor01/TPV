#pragma once
#include "SDL.h"
#include <string>
#include "Texture.h"
#include "Game.h"

using namespace std;
class gameObject
{
protected:

	Game* game = nullptr;

public:
	gameObject();
	~gameObject();

	virtual void loadTexture() = 0;
	virtual void render() = 0;
	virtual void loadFromFile(ifstream& archivo) = 0;
	virtual void saveToFile() = 0;
	virtual void update() = 0;
};