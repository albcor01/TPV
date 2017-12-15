#include "SmartGhost.h"



SmartGhost::~SmartGhost()
{
}


void SmartGhost::PosiblesDirs()
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

void SmartGhost::loadFromFile(ifstream& archivo)
{
	archivo >> tipo >> posX >> posY >> posiniX >> posiniY >> dirX >> dirY >> age;
};