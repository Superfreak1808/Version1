#ifndef COLLISION_H
#define COLLISION_H

#include <allegro.h>
#include <fstream> 
#include <sstream>
#include <string> 
#include <algorithm>
#include "Global.h"
#include "Player.h"
#include "Map.h"
#include "Enemy.h"

using namespace std;

class Collision
{
private:
	int loadCounterX;
	int loadCounterY;
	int mapSizeX;
	int mapSizeY;
	int ColMapFile[3][100][100];
	string line;

public:
	Collision();
	~Collision();

	void Init();
	void Update(BITMAP *Buffer, Player &player, Enemy &enemy, Map &map);
	void Draw(BITMAP *Buffer);

	void LoadCollisionMap(const char*filename, int level);
	void LevelEnd(Player &player, Map &map);
	void PlatformCollision(BITMAP *Buffer, Player &player, Map &map);
	void EPCollision(Player &player, Enemy &enemy);

};

#endif