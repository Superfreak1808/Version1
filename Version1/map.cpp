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
	Map::LoadMap("map1.txt");
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
			if(MapFile [i][j] == 1)
			{
				rectfill(Buffer, i*BlockSize, j*BlockSize, i*BlockSize + BlockSize, j*BlockSize + BlockSize, makecol(8, 132, 209));
			}
			else if(MapFile[i][j] == 2)
			{
				rectfill(Buffer, i*BlockSize, j*BlockSize, i*BlockSize + BlockSize, j*BlockSize + BlockSize, makecol(52, 209, 8));
			}
			else if(MapFile[i][j] == 3)
			{
				rectfill(Buffer, i*BlockSize, j*BlockSize, i*BlockSize + BlockSize, j*BlockSize + BlockSize, makecol(255, 0, 0));
			}

		}
	}
}

void Map::LoadMap(const char *filename)
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
			openfile >> MapFile[loadCounterX][loadCounterY];
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