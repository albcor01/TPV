#pragma once
#include "GameMap.h"
#include <vector>
#include "Game.h"
#include "GameObject.h"

class GameMap;
class Texture;
class gameCharacter : public gameObject {

protected:
	GameMap* mapa = nullptr;
	Texture* texture = nullptr;

protected:
	int posiniX, posiniY;
	int posX, posY;
	int dirX, dirY;

protected:

	void setposIni() { posX = posiniX; posY = posiniY; }
	void setPos(int x, int y) { posX = x; posY = y; };
	void setDir(int x, int y) { dirX = x; dirY = y; };

	//Gets
	int GetPosX() { return posX; };
	int GetPosY() { return posY; };
	int GetDirX() { return dirX; };
	int GetdirY() { return dirY; };
	int GetposiniX() { return posiniX; };
	int GetposiniY() { return posiniY; };

	gameCharacter();
	~gameCharacter();
};