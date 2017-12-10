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

protected:
	gameObject();
	~gameObject();

	virtual void loadTexture() = 0;
	virtual void render() = 0;
	virtual void loadFromFile() = 0;
	virtual void saveToFile() = 0;
	virtual void update() = 0;
};