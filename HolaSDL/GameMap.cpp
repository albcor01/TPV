#include "GameMap.h"



GameMap::GameMap(Game* game)
{
	this->game = game;
}

GameMap::~GameMap()
{
}


void GameMap::loadTexture() {};

void GameMap::render(SDL_Renderer* render, Texture* mapTexture[4]) 
{
	SDL_Rect recDest;
	recDest.w = game->getWinWidth() / DimY;
	recDest.h = (game->getWinHeight() - 100) / DimX;

	for (int i = 0; i<DimX; i++)
		for (int j = 0; j < DimY; j++)
		{
			recDest.x = recDest.w*j;
			recDest.y = recDest.h*i;
			if (matrizMapa[i][j] == Wall)
				mapTexture[0]->renderFrame(game->getRenderer(), recDest, 0, 0);
			if (matrizMapa[i][j] == Food)
				mapTexture[1]->renderFrame(game->getRenderer(), recDest, 0, 0);
			if (matrizMapa[i][j] == Vitaminas)
				mapTexture[2]->renderFrame(game->getRenderer(), recDest, 0, 0);
		}
};

void GameMap::ReservaMemoriaMapa(int fils, int cols)
{
	DimX = fils;
	DimY = cols;

	matrizMapa = new MapCell*[DimX];

	for (int i = 0; i < fils; i++) {
		matrizMapa[i] = new MapCell[DimY];
	}
}

void GameMap::SetPos(int posicionX, int posicionY, int elemento)
{
	//SITUAMOS ELEMENTOS ESTATICOS
	if (elemento == 0) { matrizMapa[posicionX][posicionY] = empty; }
	else if (elemento == 1) { matrizMapa[posicionX][posicionY] = Wall; }
	else if (elemento == 2) { matrizMapa[posicionX][posicionY] = Food; this->game->subecomida(); }
	else if (elemento == 3) { matrizMapa[posicionX][posicionY] = Vitaminas; this->game->subecomida(); }
	//PONEMOS VACIA LA CASILLA DE LOS PERSONAJES
	else if (elemento >= 4) { matrizMapa[posicionX][posicionY] = empty; }

}

void GameMap::loadFromFile(ifstream& archivo) 
{
	archivo >> fils >> cols;
	ReservaMemoriaMapa(fils, cols);
	int elemento;
	for (int i = 0; i < fils; i++) {
		for  (int j = 0; j < cols; j++)
		{
			archivo >> elemento;
			SetPos(i, j, elemento);
		}
	}

};

void GameMap::render() 
{
};

void GameMap::saveToFile() {};

void GameMap::update() {};

void GameMap::loadFromFile() {};

void GameMap::DepuraMapa()
{
	cout << "filas: " << DimX << " Columnas: " << DimY << "\n\n";
	for (int i = 0; i < DimX; i++) {
		for (int j = 0; j < DimY; j++) {
			if (matrizMapa[i][j] == empty)
				cout << "  ";
			else if (matrizMapa[i][j] == Wall)
				cout << "W ";
			else if (matrizMapa[i][j] == Vitaminas)
				cout << "V ";
			else if (matrizMapa[i][j] == Food)
				cout << "F ";
		}
		cout << "\n";
	}
}

bool GameMap::hayMuro(int x, int y)
{
	//Toroide
	toroide(x, y);

	if (matrizMapa[x][y] == Wall) { return true; }
	else { return false; }
}

void GameMap::toroide(int& x, int& y)
{
	if (x < 0) { x = fils - 1; }
	else if (x > fils - 1) { x = 0; }
	else if (y > cols - 1) { y = 0; }
	else if (y < 0) { y = cols - 1; }
}

void GameMap::cambiacasiila(int posX, int posY)
{
	if (matrizMapa[posX][posY] == Vitaminas || matrizMapa[posX][posY] == Food)
	{
		if (matrizMapa[posX][posY] == Vitaminas)
			game->setEnergia(30);

		game->bajacomida();
		matrizMapa[posX][posY] = empty;
	}

}