#include "Game.h"
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include "GameMap.h"
#include "Pacman.h"
#include "Ghost.h"
#include "gameCharacter.h"

using namespace std;

Game::Game()
{
	winX = winY = SDL_WINDOWPOS_CENTERED;
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("First test with SDL", winX, winY,
		winWidth, winHeight, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (window == nullptr || renderer == nullptr)
		cout << "Error inicializando SDL";
	else
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	for (int i = 0; i < 7; i++)
	{
		textureGame[i] = new Texture;
	}

	textureGame[0]->load(renderer, "..\\images\\wall2.png");
	textureGame[1]->load(renderer, "..\\images\\food2.png");
	textureGame[2]->load(renderer, "..\\images\\burguer1.png");
	textureGame[3]->load(renderer, "..\\images\\characters1.png", 4, 14);
	textureGame[4]->load(renderer, "..\\images\\vidas.png", 3, 1);
	textureGame[5]->load(renderer, "..\\images\\menu.jpg");
	textureGame[6]->load(renderer, "..\\images\\flecha.png");

	Mapa = new GameMap(this);
}

void Game::render()
{
	Mapa->render(renderer, textureGame);
	list<gameCharacter*>::iterator it = characters.begin();
	while (it != characters.end())
	{
		if (Pacman* pac = dynamic_cast<Pacman*>(*it)){
			pac->render(renderer, textureGame[3]);
		}
		else if (Ghost* ghost = dynamic_cast<Ghost*>(*it)){
			ghost->render(renderer, textureGame[3]);
		}
		++it;
	}
	SDL_RenderPresent(renderer);
}

Game::~Game()
{
}

void Game::run()
{
	creaMapa(true);
	Mapa->DepuraMapa();
	render();
}

void Game::creaMapa(bool carga)
{
	int numFantasmas;
	int elemento;

	ifstream archivoMapa;
	archivoMapa.open("..\\Levels\\level01.pac");

	Mapa->loadFromFile(archivoMapa);

	archivoMapa >> numFantasmas;


	for (int i = 0; i < numFantasmas; i++)
	{
		Ghost* fant = new Ghost(this, Mapa, i);
		fant->loadFromFile(archivoMapa);
		characters.push_back(fant);
	}
	Pacman* pac = new Pacman(this, Mapa);
	pac->loadFromFile(archivoMapa);
	characters.push_back(pac);

	archivoMapa.close();
	
}
