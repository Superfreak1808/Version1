#include "map.h"


Map::Map()
{

}


Map::~Map()
{

}

void Map::Init()
{
	loadCounterX = loadCounterY = 0;
	level = 0;
	Map::LoadMap("map1.txt", 0);
	Map::LoadMap("map2.txt", 1);
	Map::LoadMap("map3.txt", 2);
}

void Map::Update()
{
}

void Map::Draw(BITMAP *Buffer)
{
	for(int i = 0; i<mapSizeX; i++)
	{
		for(int j = 0; j < mapSizeY; j++)
		{
			if(MapFile [level][i][j] == 1)
			{
				rectfill(Buffer, i*BlockSize, j*BlockSize, i*BlockSize + BlockSize, j*BlockSize + BlockSize, makecol(8, 132, 209));
			}
			else if(MapFile [level][i][j] == 2)
			{
				rectfill(Buffer, i*BlockSize, j*BlockSize, i*BlockSize + BlockSize, j*BlockSize + BlockSize, makecol(52, 209, 8));
			}
			else if(MapFile [level][i][j] == 3)
			{
				rectfill(Buffer, i*BlockSize, j*BlockSize, i*BlockSize + BlockSize, j*BlockSize + BlockSize, makecol(255, 0, 0));
			}
			else if(MapFile [level][i][j] == 4)
			{
				rectfill(Buffer, i*BlockSize, j*BlockSize, i*BlockSize + BlockSize, j*BlockSize + BlockSize, makecol(255, 255, 0));
			}

		}
	}
}

void Map::LoadMap(const char *filename, int level)
{
	ifstream openfile (filename);
	if (openfile.is_open())
	{
		getline(openfile, line);
		line.erase( remove( line.begin(), line.end(), ' '), line.end() );
		mapSizeX = line.length();
		openfile.seekg(0, ios::beg);
		mapSizeY = 0;
		while(!openfile.eof())
		{
			openfile >> MapFile[level][loadCounterX][loadCounterY];
			loadCounterX ++;

			if(loadCounterX >= mapSizeX)
			{
				loadCounterX = 0;
				loadCounterY ++;
				mapSizeY ++;
			}
		}
		loadCounterX = loadCounterY = 0;
	}
	else
	{
		allegro_message("Map File Not Found");
	}
}

int Map::getLevel()
{
	return level;
}

void Map::setLevel(int value)
{
	level = value;
}