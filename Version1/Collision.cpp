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
	Collision::LoadCollisionMap("colmap1.txt", 0);
	Collision::LoadCollisionMap("colmap2.txt", 1);
	Collision::LoadCollisionMap("colmap3.txt", 2);
}

void Collision::Update(BITMAP *Buffer, Player &player, Enemy &enemy, Map &map)
{
	Collision::PlatformCollision(Buffer, player, map);
	Collision::EPCollision(player, enemy);
	Collision::LevelEnd(player, map);

}

void Collision::Draw(BITMAP *Buffer)
{

}

void Collision::LoadCollisionMap(const char *filename, int level)
{
	ifstream openfile(filename);
	if(openfile.is_open())
	{
		getline(openfile, line);
		line.erase( remove( line.begin(), line.end(), ' '), line.end() );
		mapSizeX = line.length();
		openfile.seekg(0, ios::beg);
		mapSizeY = 0;
		while(!openfile.eof())
		{
			openfile >> ColMapFile[level][loadCounterX][loadCounterY];
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
		allegro_message("Cannot find collision map");
	}
}

void Collision::PlatformCollision(BITMAP *Buffer, Player &player, Map &map)
{
	for(int i = 0; i < mapSizeX; i++)
	{
		for(int j = 0; j < mapSizeY; j++)
		{
			if(ColMapFile[map.getLevel()][i][j] == 1)
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

void Collision::EPCollision(Player &player, Enemy &enemy)
{
	for(int i = 0; i < enemy.getAmountOfEnemies(); i++)
	{
			if(player.x > enemy.getX2(i) || player.y > enemy.getY2(i) || player.x2 < enemy.getX(i) || player.y2 < enemy.getY(i))
			{
				// No Collision
			}
			else 
			{
				// Player Dies(loses a life)
				player.lives --;
			}
	}
}

void Collision::LevelEnd(Player &player, Map &map)
{
	for(int i = 0; i < mapSizeX; i++)
	{
		for(int j = 0; j < mapSizeY; j++)
		{
			if(ColMapFile[map.getLevel()][i][j] == 2)
			{
				if(player.x > i*BlockSize + BlockSize || player.y > j*BlockSize + BlockSize || player.x2 < i*BlockSize || player.y2 < j*BlockSize)
				{
					//No Collsion
					player.Platform = false;
				}
				else
				{
					int level = map.getLevel();
					level ++;
					map.setLevel(level);
					if(level >2)
					{
						map.setLevel(0);
					}
					player.x = player.origX;
					player.y = player.origY;
					clear_to_color(screen, makecol(0,0,0));
					rest(1000);
				}
			}
		}
	}
}
