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

	Mapa = new GameMap(this, textureGame);
}

void Game::render()
{
	list<gameCharacter*>::iterator it;
	SDL_RenderClear(renderer);
	Mapa->render();
	it = characters.begin();
	while (it != characters.end())
	{
		(*it)->render();
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
	while (vidas>0)
	{
		handleEvents();
		update();
		render();
		SDL_Delay(200);
	}
	SDL_Quit();
}

void Game::handleEvents()
{

	SDL_Event event;

	//Control de eventos
	while (SDL_PollEvent(&event) && !exit) {

		if (event.type == SDL_QUIT)
			exit = true;
		else if (event.type == SDL_KEYDOWN)
		{
			pac->Ndir(event);
			exit = false;
		}
	}
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
		Ghost* fant = new Ghost(this, Mapa, i,textureGame[3]);
		fant->loadFromFile(archivoMapa);
		characters.push_back(fant);
	}
	pac = new Pacman(this, Mapa,textureGame[3]);
	pac->loadFromFile(archivoMapa);
	characters.push_front(pac);

	archivoMapa.close();
	
}
void Game::ComeComida(int x, int y)
{
	Mapa->cambiacasiila(x, y);
}

void Game::update()
{
	list<gameCharacter*>::iterator it;
	 it = characters.begin();
	while (it != characters.end())
	{
		 if (Ghost* ghost = dynamic_cast<Ghost*>(*it)) {
			ghost->update();
		}

		else if (pac = dynamic_cast<Pacman*>(*it)) {
			pac->update();
		}
		
		
		++it;
	}
}

bool Game::HayFantasma(int x, int y)
{
	list<gameCharacter*>::iterator it;
	bool hayfantasma = false;
	it = characters.begin();
	while (it != characters.end())
	{
		 if (Ghost* ghost = dynamic_cast<Ghost*>(*it)) {
			 if (x == ghost->GetPosX() && y == ghost->GetPosY())
				 hayfantasma = true;
		}
		++it;
	}

	return hayfantasma;
}

int Game::GetposXfan(int x)
{
	list<gameCharacter*>::iterator it;
	it = next(characters.begin(), 1);
	for (int i = 0; i < x; i++)
	{
		it++;
	}
	return (*it)->GetPosX();
	
}

int Game::GetposYfan(int x)
{
	list<gameCharacter*>::iterator it;
	it = next(characters.begin(), 1);
	for (int i = 0; i < x; i++)
	{
		it++;
	}

	return (*it)->GetPosY();
}
void Game::restauraPosciones(Pacman* pacman, int i)
{
	list<gameCharacter*>::iterator it;
	it = next(characters.begin(), 1);
	if (Energia <= 0)
	{
		for (int t = 0; t < 4; t++)
		{
			(*it)->setposIni();
			it++;
		}
		pac->setPos(pacman->GetposiniX(), pacman->GetposiniY());
		restaVidas();
		pac->setDir(0, 1);
	}

	else
	{
		for (int t = 0; t < i; t++)
			it++;
		(*it)->setposIni();
	}
}
