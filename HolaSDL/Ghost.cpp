#include "Ghost.h"



Ghost::Ghost(Game* juego, GameMap* mapa, int numFant,Texture* GhostTextur)
{
	this->game = juego;
	this->mapa = mapa;
	numcol = numFant * 2;
	this->GhostTexture = GhostTextur;
}


Ghost::~Ghost()
{
}

void Ghost::loadFromFile() {};

void Ghost::loadTexture() {};

void Ghost::render()
{
	SDL_Rect recDest;
	recDest.w = game->getWinWidth() / mapa->getDimY();
	recDest.h = (game->getWinHeight() - 100) / mapa->getDimX();
	recDest.x = recDest.w * posY;
	recDest.y = recDest.h* posX;
	if (game->getEnergia() <= 0) {
		if (patas) {
			GhostTexture->renderFrame(game->getRenderer(), recDest, 0, numcol);
			patas = false;
		}
		else
		{
			GhostTexture->renderFrame(game->getRenderer(), recDest, 0, numcol + 1);
			patas = true;	
		}
	}
	else
	{
		if (patas) {
			GhostTexture->renderFrame(game->getRenderer(), recDest, 0, 12);
			patas = false;
		}
		else
		{
			GhostTexture->renderFrame(game->getRenderer(), recDest, 0, 13);
			patas = true;
		}

	}
}

void Ghost::loadFromFile(ifstream& archivo) 
{
	archivo >> tipo >> posX >> posY >> posiniX >> posiniY >> dirX >> dirY;
};



void Ghost::saveToFile() {};

void Ghost::RellenaPos(int x, int y)
{
	Dirs aux;
	aux.x = x;
	aux.y = y;
	posDirs.push_back(aux);
}

void Ghost::PosiblesDirs()
{
	posDirs.clear();

	RellenaPos(1, 0);
	RellenaPos(-1, 0);
	RellenaPos(0, 1);
	RellenaPos(0, -1);
	int i = 0;

	while (i < posDirs.size()) {
		if ((mapa->hayMuro(posX + posDirs[i].x, posY + posDirs[i].y)) || (posDirs[i].x == -dirX && posDirs[i].y == -dirY) ||
			this->game->HayFantasma(posX + posDirs[i].x, posY + posDirs[i].y))
		{
			posDirs.erase(posDirs.begin() + i);
		}
		else i++;
	}
	if (posDirs.size() < 1)
	{
		RellenaPos(-dirX, -dirY);
	}


}


void Ghost::update()
{
	PosiblesDirs();
	int random = rand() % posDirs.size();
	dirX = posDirs[random].x;
	dirY = posDirs[random].y;
	//detectaPacman();
	posX += dirX;
	posY += dirY;
	mapa->toroide(posX, posY);
	//juego->Conpruebamuerte(this);

}
