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
	Collision::EPCollision(player, enemy, map);
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
				if(player.getX() > i*BlockSize + BlockSize || player.getY() > j*BlockSize + BlockSize || player.getX2() < i*BlockSize || player.getY2() < j*BlockSize)
				{
					//No Collsion
					player.setPlatform(false);
				}
				else
				{
					if(player.getVDirection() == 2 && player.getY() - player.getVelY() <= j*BlockSize)
					{
						player.setY(j*BlockSize - 10);
						player.setY2(player.getY() + 10);
						player.setVelY(0);
						player.setPlatform(true);
						player.setJump(true);
					}
					else if (player.getVDirection() == 1)
					{
						player.setY(player.getY() + player.getSpeed()*2);
						player.setY2(player.getY() + 10); 
						player.setVelY(0); 
						player.setPlatform(false);
						player.setJump(false);
					}
					if (player.getHDirection() == 1 && player.getPlatform() == false)
					{
						player.setX(player.getX() - player.getSpeed()); 
						player.setX2(player.getX() + 10); 
					}
					else if (player.getHDirection() == 2 && player.getPlatform() == false)
					{
						player.setX(player.getX() + player.getSpeed()); 
						player.setX2(player.getX() + 10);
					}
				}
			}
		}
	}
}

void Collision::EPCollision(Player &player, Enemy &enemy, Map& map)
{
	for(int i = 0; i < enemy.getAmountOfEnemies(); i++)
	{
		if(enemy.getLevel(i) == map.getLevel())
		{
			if(player.getX() > enemy.getX2(i) || player.getY() > enemy.getY2(i) || player.getX2() < enemy.getX(i) || player.getY2() < enemy.getY(i))
			{
				// No Collision
			}
			else 
			{
				// Player Dies(loses a life)
				player.setLives(player.getLives()-1);
			}
		}
	}
}

void Collision::LevelEnd(Player &player, Map &map)
{
	for (int i = 0; i < mapSizeX; i++)
	{
		for (int j = 0; j < mapSizeY; j++)
		{
			if(ColMapFile[map.getLevel()][i][j] == 2)
			{
				if(player.getX() > i*BlockSize + BlockSize || player.getY() > j*BlockSize + BlockSize || 
					player.getX2() < i*BlockSize || player.getY2() < j*BlockSize)
				{
					
				}
				else 
				{
					int level = map.getLevel();
					level ++;
					map.setLevel(level);
					if(level > 2)
					{
						map.setLevel(0);
					}
					player.setX(player.getOrigX());
					player.setY(player.getOrigY());
					clear_to_color(screen, makecol(0, 0, 0));
					rest(1000);
				}
			}
		}
	}
}