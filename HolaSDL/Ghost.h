#include "gameCharacter.h"
#pragma once
class Ghost: public gameCharacter
{

	int tipo;
	int numfils, numcol;
	bool patas = true;

public:
	Ghost(Game* juego, GameMap* , int numFant);
	~Ghost();

	void loadFromFile();
	void render();

	void loadTexture();
	void render(SDL_Renderer*  renderer, Texture* texture);
	void loadFromFile(ifstream& archivo);
	void saveToFile();
	void update();
};

