#include "Pacman.h"
#include "Game.h"
#include "GameMap.h"


Pacman::Pacman(Game* juego, GameMap* mapa,Texture* pacManTextur)
{
	this->game = juego;
	this->mapa = mapa;
	pacManTexture = pacManTextur;
}


Pacman::~Pacman()
{
}

void Pacman::loadTexture() {};


void Pacman::MuevePacman()
{
	siguientePosX = posX + dirX;
	siguientePosY = posY + dirY;
	mapa->toroide(siguientePosX, siguientePosY);

	if (!mapa->hayMuro(siguientePosX, siguientePosY))
	{
		posX = siguientePosX;
		posY = siguientePosY;
	}
}


void Pacman::render()
{
	
	SDL_Rect recDest;
	recDest.w = game->getWinWidth() / mapa->getDimY();
	recDest.h = (game->getWinHeight() - 100) / mapa->getDimX();
	recDest.x = recDest.w * posY;
	recDest.y = recDest.h* posX;
	if (animacion) {
		if (dirX == 0 && dirY == 1)
			pacManTexture->renderFrame(game->getRenderer(), recDest, 0, 10);
		else if (dirX == 0 && dirY == -1)
			pacManTexture->renderFrame(game->getRenderer(), recDest, 2, 10);
		else if (dirX == 1 && dirY == 0)
			pacManTexture->renderFrame(game->getRenderer(), recDest, 1, 10);
		else if (dirX == -1 && dirY == 0)
			pacManTexture->renderFrame(game->getRenderer(), recDest, 3, 10);
		animacion = false;
	}
	else {
		if (dirX == 0 && dirY == 1)
			pacManTexture->renderFrame(game->getRenderer(), recDest, 0, 11);
		else if (dirX == 0 && dirY == -1)
			pacManTexture->renderFrame(game->getRenderer(), recDest, 2, 11);
		else if (dirX == 1 && dirY == 0)
			pacManTexture->renderFrame(game->getRenderer(), recDest, 1, 11);
		else if (dirX == -1 && dirY == 0)
			pacManTexture->renderFrame(game->getRenderer(), recDest, 3, 11);
		animacion = true;
	}


}

void Pacman::Ndir(SDL_Event event)
{

	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_RIGHT) {
			NdirX = 0;
			NdirY = 1;
			input = true;
		}
		else if (event.key.keysym.sym == SDLK_LEFT) {
			NdirX = 0;
			NdirY = -1;
			input = true;
		}
		else if (event.key.keysym.sym == SDLK_UP) {
			NdirX = -1;
			NdirY = 0;
			input = true;
		}
		else if (event.key.keysym.sym == SDLK_DOWN) {
			NdirX = 1;
			NdirY = 0;
			input = true;
		}

	}
}


void Pacman::Buffer()
{
	posibledirX = posX + NdirX;
	posibledirY = posY + NdirY;

	if (!mapa->hayMuro(posibledirX, posibledirY) && input)
	{
		dirX = NdirX;
		dirY = NdirY;
		NdirX = 0;
		NdirY = 0;
		input = false;
	}
}

void Pacman::loadFromFile(){};

void Pacman::loadFromFile(ifstream& archivo)
{
	int basura;//BASURA SE USA PORQUE COMO AUN NO HAY SMARTGHOST LEO UNA LINEA DE MAS EN PACMAN
	archivo >> basura;
	archivo >> this->posX >> this->posY >> this->posiniX >> this->posiniY >> this->dirX >> this->dirY;
};

void Pacman::DetectaFantasma()
{
	for (int i = 0; i < 4; i++)
	{
		if (posX == game->GetposXfan(i) && posY == game->GetposYfan(i))
		{
			game->restauraPosciones(this, i);
		}
	}
}

void Pacman::saveToFile() {};

void Pacman::update() 
{
	Buffer();

	DetectaFantasma();

	MuevePacman();

	DetectaFantasma();

	game->ComeComida(posX, posY);

	game->restaEnergia();
};


