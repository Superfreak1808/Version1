#ifndef COLLISION_H
#define COLLISION_H

#include <allegro.h>
#include <fstream>
#include <string>
#include <algorithm>
#include "global.h"
#include "Player.h"

using namespace std;

class Collision
{
private:
	int loadCounterX;
	int loadCounterY;
	int mapSizeX;
	int mapSizeY;
	int ColMapFile[100][100];
	string line;

public:
	Collision();
	~Collision();

	void Init();
	void Update(BITMAP *Buffer, Player &player);
	void Draw(BITMAP *Buffer);

	void LoadCollisionMap(const char*filename);

	void PlatformCollision(BITMAP *Buffer, Player &player);

};

#endif