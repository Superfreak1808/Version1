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
	Collision::Boundaries(player, map);
}

void Collision::Draw(BITMAP *Buffer)
{

}

void Collision::LoadCollisionMap(const char*filename, int level)
{
	ifstream openfile(filename);
	if(openfile.is_open())
	{
		getline(openfile, line); 
		line.erase( remove( line.begin(), line.end(), ' ' ), line.end() );
		mapSizeX[level] = line.length();
		openfile.seekg(0, ios::beg);
		mapSizeY[level] = 0;
		while(!openfile.eof())
		{
			openfile >> ColMapFile[level][loadCounterX][loadCounterY];
			loadCounterX ++;
			if (loadCounterX >= mapSizeX[level])
			{
				loadCounterX = 0; 
				loadCounterY ++;
				mapSizeY[level] ++;
			}
		}
		loadCounterX = loadCounterY = 0;
	}
	else 
	{
		allegro_message("Cannot find the collision map file");
	}
}

void Collision::PlatformCollision(BITMAP *Buffer, Player &player, Map &map)
{
	for (int i = 0; i < mapSizeX[map.getLevel()]; i++)
	{
		for (int j = 0; j < mapSizeY[map.getLevel()]; j++)
		{
			if(ColMapFile[map.getLevel()][i][j] == 1)
			{
				if(player.getX() > i*BlockSize + BlockSize || player.getY() > j*BlockSize + BlockSize || player.getX2() < i*BlockSize 
					|| player.getY2() < j*BlockSize)
				{
					// No Collision 
					player.setPlatform(false);
				}
				else 
				{
				    if(player.getVDirection() == 2 && player.getY() - player.getVelY() <= j*BlockSize)
					{
						player.setY(j*BlockSize - 31);
						player.setY2(player.getY() + 31);
						player.setVelY(0);
						player.setPlatform(true); 
						player.setJump(true); 
				    }
					else if (player.getVDirection() == 1)
					{
						player.setY(player.getY() + player.getSpeed()*2);
						player.setY2(player.getY() + 31); 
						player.setVelY(0); 
						player.setPlatform(false);
						player.setJump(false);
					}
					if (player.getHDirection() == 1 && player.getPlatform() == false)
					{
						player.setX(player.getX() - player.getSpeed()); 
						player.setX2(player.getX() + 31); 
					}
					else if (player.getHDirection() == 2 && player.getPlatform() == false)
					{
						player.setX(player.getX() + player.getSpeed()); 
						player.setX2(player.getX() + 31);
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
				player.setX(player.getX()-75 );
			}
		}
	}
}

void Collision::LevelEnd(Player &player, Map &map)
{
	for (int i = 0; i < mapSizeX[map.getLevel()]; i++)
	{
		for (int j = 0; j < mapSizeY[map.getLevel()]; j++)
		{
			if(ColMapFile[map.getLevel()][i][j] == 2)
			{
				if(player.getX() > i*BlockSize + BlockSize || player.getY() > j*BlockSize + BlockSize || 
					player.getX2() < i*BlockSize || player.getY2() < j*BlockSize)
				{
					// No Collision 
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

void Collision::Boundaries(Player &player, Map &map)
{
	if(player.getX() < 0)
		player.setX(0); 
	else if(player.getX() > map.getMapSizeX(map.getLevel()) * BlockSize - (player.getX2() - player.getX()))
		player.setX(map.getMapSizeX(map.getLevel()) * BlockSize - (player.getX2() - player.getX()));
}