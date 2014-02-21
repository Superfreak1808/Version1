#ifndef MAP_H
#define MAP_H

#include <allegro.h>
#include <fstream>
#include "global.h"
#include <string>
#include <algorithm>
using namespace std;

class Map
{
public:
	
	Map();
	~Map();

	void Init();
	void Update();
	void Draw(BITMAP *Buffer);
	void LoadMap(const char*filename, int level);
	int getLevel();
	void setLevel(int value);

private:

	int loadCounterX, loadCounterY;
	int mapSizeX, mapSizeY;
	int MapFile[3][100][100];
	int level;
	string line;

};
#endif