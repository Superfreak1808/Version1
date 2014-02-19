#include "Collision.h"


Collision::Collision()
{

}


Collision::~Collision()
{

}

void Collision::Init()
{
	loadCounterX = loadCounterY = 0;
	Collision::LoadCollisionMap("colmap1.txt");
}

void Collision::Update(BITMAP *Buffer, Player &player)
{
	Collision::PlatformCollision(Buffer, player);

}

void Collision::Draw(BITMAP *Buffer)
{

}

void Collision::LoadCollisionMap(const char *filename)
{
	ifstream openfile(filename);
	if(openfile.is_open())
	{
		openfile >> mapSizeX >> mapSizeY;
		while(!openfile.eof())
		{
			openfile >> ColMapFile[loadCounterX][loadCounterY];
			loadCounterX ++;
			if(loadCounterX >= mapSizeX)
			{
				loadCounterX = 0;
				loadCounterY ++;
			}
		}
		loadCounterX = loadCounterY = 0;
	}
	else
	{
		allegro_message("Cannot find collision map");
	}
}

void Collision::PlatformCollision(BITMAP *Buffer, Player &player)
{
	for(int i = 0; i < mapSizeX; i++)
	{
		for(int j = 0; j < mapSizeY; j++)
		{
			if(ColMapFile[i][j] == 1)
			{
				if(player.x > i*BlockSize + BlockSize || player.y > j*BlockSize + BlockSize || player.x2 < i*BlockSize || player.y2 < j*BlockSize)
				{
					//No Collsion
					player.Platform = false;
				}
				else
				{
					if(player.vDir == 2 && player.y - player.vely <= j*BlockSize)
					{
						player.y = j*BlockSize - 10;
						player.y2 = player.y + 10;
						player.vely = 0;
						player.Platform = true;
						player.Jump = true;
					}
					else if(player.vDir == 1)
					{
						player.y += player.speed*2;
						player.y2 = player.y+10;
						player.vely = 0;
						player.Platform = false;
						player.Jump = false;
					}
					if(player.hDir == 1 && player.Platform == false)
					{
						player.x -= player.speed;
						player.x2 = player.x+10;
					}
					else if(player.hDir == 2 && player.Platform == false)
					{
						player.x += player.speed;
						player.x2 = player.x+10;
					}
				}
			}
		}
	}
}