#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <list>

using namespace std;

//Dependencias
class GameMap;
class Texture;
class GameObject;
class Pacman;
class Ghost;
class gameCharacter;
class Game
{

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	const int winWidth = 1300;
	const int winHeight = 800;
	int fils, cols;
	int winX, winY;
	bool exit = false;
	int pasoNiveles = 0;
	int comidarestante = 0;
	vector <GameObject*> gameObjects;
	int vidas = 3;
	int Energia = 0;
	Texture* textureGame[7];
	Texture* fondo;
	list<gameCharacter*> characters;
	GameMap* Mapa = nullptr;
	Pacman* pac;
public:
	Game();
	~Game();

	void run();
	bool menu();
	void guardaPartida();
	void creaMapa(bool carga);

	//Actualizan
	void update();
	void render();
	void handleEvents();
	void restaVidas() { vidas -= 1; }
	void pintaVidas();

	//METODOS DE ENERGIA
	void setEnergia() { Energia = 30; };
	void restaEnergia() { if (Energia > 0)Energia -= 1; };

	//METODOS DE COLISIONES CON FANTASMAS Y COMIDA
	void ComeComida(int x, int y);
	//void restauraPosciones(Pacman* pacman, int i);
	void bajacomida() { comidarestante -= 1; };
	void subecomida() { comidarestante += 1; };
	void setEnergia(int x) { Energia = x; };
	void restauraPosciones(Pacman* pacman, int i);
	bool HayFantasma(int x, int y);

	//METODOS GET
	SDL_Renderer* getRenderer() { return renderer; };
	int GetposXfan(int x);
	int GetposYfan(int x);
	int getEnergia() { return Energia; };
	int getWinWidth() { return winWidth; };
	int getWinHeight() { return winHeight; };
	int getFilas() { return fils; };
	int getCols() { return cols; };


};

