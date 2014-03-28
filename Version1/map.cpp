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

void Map::Draw(BITMAP *Buffer, BITMAP *Brick, BITMAP *Floor, BITMAP *Floor2, BITMAP *Floor3, BITMAP *Cloud)
{
    for (int i = 0; i < mapSizeX[level]; i++)
    {
        for (int j = 0; j < mapSizeY[level]; j++)
        {
            if (MapFile[level][i][j] == 1)
            {
                rectfill(Buffer, i*BlockSize, j*BlockSize, i*BlockSize + BlockSize, j*BlockSize + BlockSize, makecol(135, 206, 235));
            }
            else if (MapFile[level][i][j] == 2)
            {
                acquire_screen();
				draw_sprite(Buffer, Floor2, i*BlockSize, j*BlockSize);
				release_screen();
            }
			else if (MapFile[level][i][j] == 3)
			{
				acquire_screen();
				draw_sprite(Buffer, Brick, i*BlockSize, j*BlockSize);
				release_screen();
			    
			}
			else if (MapFile[level][i][j] == 4)
			{
			    acquire_screen();
				draw_sprite(Buffer, Floor3, i*BlockSize, j*BlockSize);
				release_screen();
			}

			else if (MapFile[level][i][j] == 5)
			{
			    acquire_screen();
				draw_sprite(Buffer, Floor, i*BlockSize, j*BlockSize);
				release_screen();
			}

		}
	}


	for (int k = 10; k < 2400; (k = k+300) )
	{
				acquire_screen();
				draw_sprite(Buffer, Cloud, k, 10);
				release_screen();
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