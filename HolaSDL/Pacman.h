#pragma once
#include "gameCharacter.h"

class Game;
class Pacman: public gameCharacter
{

	bool animacion = true;
	int NdirX, NdirY;
	int siguientePosX,siguientePosY;
	int posibledirX, posibledirY;
	bool input;
public:
	Pacman(Game* juego, GameMap* mapa);
	~Pacman();

	void loadTexture();
	void render();
	void render(SDL_Renderer* render, Texture* texture);
	void loadFromFile(ifstream& archivo);
	void loadFromFile();
	void saveToFile();
	void update();
	void Ndir(SDL_Event event);
	void MuevePacman();
	void Buffer();
	void PosicionInicial(int x, int y) { this->posiniX = x; this->posiniY = y; };
	//void DetectaFantasma();
	void setPos(int x, int y) { posX = x; posY = y; };
	void setDir(int x, int y) { dirX = x; dirY = y; };
};

