#include "Ghost.h"



Ghost::Ghost(Game* juego, GameMap* mapa, int numFant)
{
	this->game = juego;
	this->mapa = mapa;
	numcol = numFant * 2;
}


Ghost::~Ghost()
{
}


void Ghost::render() {}
void Ghost::loadFromFile() {};

void Ghost::loadTexture() {};

void Ghost::render(SDL_Renderer*  renderer, Texture* texture)
{
	SDL_Rect recDest;
	recDest.w = game->getWinWidth() / mapa->getDimY();
	recDest.h = (game->getWinHeight() - 100) / mapa->getDimX();
	recDest.x = recDest.w * posY;
	recDest.y = recDest.h* posX;
	if (game->getEnergia() <= 0) {
		if (patas) {
			texture->renderFrame(game->getRenderer(), recDest, 0, numcol);
			patas = false;
		}
		else
		{
			texture->renderFrame(game->getRenderer(), recDest, 0, numcol + 1);
			patas = true;
		}
	}
	else
	{
		if (patas) {
			texture->renderFrame(game->getRenderer(), recDest, 0, 12);
			patas = false;
		}
		else
		{
			texture->renderFrame(game->getRenderer(), recDest, 0, 13);
			patas = true;
		}

	}
}

void Ghost::loadFromFile(ifstream& archivo) 
{
	archivo >> tipo >> posX >> posY >> posiniX >> posiniY >> dirX >> dirY;
};

void Ghost::saveToFile() {};

void Ghost::update() {};