#pragma once
#include "gameCharacter.h"

class Game;
class Pacman: public gameCharacter
{

	bool animacion = true;

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
};

