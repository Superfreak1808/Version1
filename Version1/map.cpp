#include"Map.h"

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
    for (int i = 0; i < mapSizeX[level]; i++)
    {
        for (int j = 0; j < mapSizeY[level]; j++)
        {
            if (MapFile[level][i][j] == 1)
            {
                rectfill(Buffer, i*BlockSize, j*BlockSize, i*BlockSize + BlockSize, j*BlockSize + BlockSize, makecol(0, 255, 255));
            }
            else if (MapFile[level][i][j] == 2)
            {
                rectfill(Buffer, i*BlockSize, j*BlockSize, i*BlockSize + BlockSize, j*BlockSize + BlockSize, makecol(0, 255,0));
            }
			else if (MapFile[level][i][j] == 3)
			{
			    rectfill(Buffer, i*BlockSize, j*BlockSize, i*BlockSize + BlockSize, j*BlockSize + BlockSize, makecol(255, 0 ,0));
			}
			else if (MapFile[level][i][j] == 4)
			{
			    rectfill(Buffer, i*BlockSize, j*BlockSize, i*BlockSize + BlockSize, j*BlockSize + BlockSize, makecol(255, 255 ,0));
			}
        }
    }
}

void Map::LoadMap(const char *filename, int level)
{
    ifstream openfile(filename);

    if (openfile.is_open())
    {
		getline(openfile, line);
		line.erase( remove( line.begin(), line.end(), ' ' ), line.end() );
		mapSizeX[level] = line.length();
		openfile.seekg(0, ios::beg);
		mapSizeY[level] = 0;
        while(!openfile.eof())
        {
            openfile >> MapFile[level][loadCounterX][loadCounterY];
            loadCounterX ++;
            if (loadCounterX >= mapSizeX[level])
            {
                loadCounterX = 0;
                loadCounterY ++;
				mapSizeY[level] ++;
            }
        }
        loadCounterX = loadCounterY = 0;
		//allegro_message("MapSizeX: %i", mapSizeX);
		//allegro_message("MapSizeY: %i", mapSizeY);
    }
    else
    {
        allegro_message("Could not load the specified map file");
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

int Map::getMapSizeX(int index)
{
	return mapSizeX[index];
}