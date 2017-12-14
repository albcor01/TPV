#include "gameObject.h"

#pragma once
class GameMap: public gameObject
{
	//Dimensiones del mapa
	int DimX;
	int DimY;
	int fils, cols;

	enum MapCell { empty, Wall, Food, Vitaminas }; //Tipos de muro que puede tener el mapa
	MapCell **matrizMapa;
	Texture* mapTexture[3];

public:
	GameMap(Game* game,Texture* textures[7]);
	~GameMap();

	void loadFromFile();

	void loadTexture();
	void render();
	void loadFromFile(ifstream& archivo);
	void saveToFile();
	void update();


	void ReservaMemoriaMapa(int fils, int cols);
	void SetPos(int posicionX, int posicionY, int elemetnto);

	//Metodos Get
	bool hayMuro(int x, int y);
	int getDimX() { return DimX; };
	int getDimY() { return DimY; };
	int getElemMatriz(int i, int j);


	void DepuraMapa();
	void cambiacasiila(int posX, int posY);
	void toroide(int& x, int& y);
};

