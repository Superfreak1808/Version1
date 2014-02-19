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
	void LoadMap(const char*filename);

private:

	int loadCounterX, loadCounterY;
	int mapSizeX, mapSizeY;
	int MapFile[100][100];
	string line;

};
#endif