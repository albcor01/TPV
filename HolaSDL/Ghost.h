#include "gameCharacter.h"
#pragma once
class Ghost: public gameCharacter
{
protected:
	struct Dirs
	{
		int x;
		int y;
	};
	vector<Dirs> posDirs;
	Texture* GhostTexture;
	int numfils, numcol;
	int NumeroFantasma;
	bool patas = true;

public:
	Ghost(Game* juego, GameMap* , int numFant,Texture* GhostTexture);
	~Ghost();

	void loadFromFile();
	void PosiblesDirs();
	void RellenaPos(int x, int y);
	void setposIni() {
		this->posX = this->posiniX;
		this->posY = this->posiniY;
	}
	void loadTexture();
	void render();
	void loadFromFile(ifstream& archivo);
	void saveToFile();
	void update();
};

