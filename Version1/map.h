#ifndef MAP_H
#define MAP_H

#include<allegro.h>
#include<fstream>
#include<string>
#include<algorithm>
#include"Global.h"
using namespace std;

class Map
{
    private:
        int loadCounterX;
        int loadCounterY;
        int mapSizeX[3];
        int mapSizeY[3];
        int MapFile[3][100][100];
		int level;
		string line;
    public:
        Map();
        ~Map();

        void Init();
        void Update();
        void Draw(BITMAP *Buffer, BITMAP *Brick, BITMAP *Floor, BITMAP *Floor2, BITMAP *Floor3, BITMAP *Cloud);
		void LoadMap(const char*filename, int level);
		int getLevel();
		void setLevel(int value);
		int getMapSizeX(int index);
};

#endif