#include "Pacman.h"
#include "Game.h"
#include "GameMap.h"


Pacman::Pacman(Game* juego, GameMap* mapa)
{
	this->game = juego;
	this->mapa = mapa;
}


Pacman::~Pacman()
{
}

void Pacman::loadTexture() {};

void Pacman::render() {};

void Pacman::render(SDL_Renderer* render, Texture* texture)
{
	SDL_Rect recDest;
	recDest.w = game->getWinWidth() / mapa->getDimY();
	recDest.h = (game->getWinHeight() - 100) / mapa->getDimX();
	recDest.x = recDest.w * posY;
	recDest.y = recDest.h* posX;
	if (animacion) {
		if (dirX == 0 && dirY == 1)
			texture->renderFrame(game->getRenderer(), recDest, 0, 10);
		else if (dirX == 0 && dirY == -1)
			texture->renderFrame(game->getRenderer(), recDest, 2, 10);
		else if (dirX == 1 && dirY == 0)
			texture->renderFrame(game->getRenderer(), recDest, 1, 10);
		else if (dirX == -1 && dirY == 0)
			texture->renderFrame(game->getRenderer(), recDest, 3, 10);
		animacion = false;
	}
	else {
		if (dirX == 0 && dirY == 1)
			texture->renderFrame(game->getRenderer(), recDest, 0, 11);
		else if (dirX == 0 && dirY == -1)
			texture->renderFrame(game->getRenderer(), recDest, 2, 11);
		else if (dirX == 1 && dirY == 0)
			texture->renderFrame(game->getRenderer(), recDest, 1, 11);
		else if (dirX == -1 && dirY == 0)
			texture->renderFrame(game->getRenderer(), recDest, 3, 11);
		animacion = true;
	}


}

void Pacman::loadFromFile(){};

void Pacman::loadFromFile(ifstream& archivo)
{
	int basura;//BASURA SE USA PORQUE COMO AUN NO HAY SMARTGHOST LEO UNA LINEA DE MAS EN PACMAN
	archivo >> basura;
	archivo >> posX >> posY >> posiniX >> posiniY >> dirX >> dirY;
};

void Pacman::saveToFile() {};

void Pacman::update() {};

