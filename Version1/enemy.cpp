#include "Enemy.h"
 
 
Enemy::Enemy()
{
 
}
 
 
Enemy::~Enemy()
{
 
}
 
void Enemy::Init()
{
    loadCounter = 0;
    amountOfEnemies = 0;
    Enemy::LoadEnemies("Enemy.txt");
    for(int i = 0; i < amountOfEnemies; i++)
    {
        rangeCounter[i] = 0;
        int Rand = rand()%2 + 1;
        /* Note: This is not needed. It doesn't matter if it increases first or decrease first. It will have the same effect 
        no matter what. Just getting used to the fact of using the rand function */
        if(Rand == 1)
        {
            Increase[i] = true;
        }
        else
        {
            Increase[i] = false;
        }
    }
}
 
void Enemy::Update(int level)
{
    Enemy::Move(level);
}
 
void Enemy::Draw(BITMAP *Buffer, int level)
{
    for(int i = 0; i < amountOfEnemies; i++)
    {
        if(this->level[i] == level)
		{
            rectfill(Buffer, x[i], y[i], x[i] + width[i], y[i] + height[i], makecol(0, 0, 255));
		}
    }
}
 
// You can have 3 different enemy files. 
// enemy1.txt, enemy2.txt enemy3.txt
 
void Enemy::LoadEnemies(const char*filename)
{
    ifstream openfile(filename);
    if(openfile.is_open())
    {
        while(!openfile.eof())
        {
            openfile >> x[loadCounter] >> y[loadCounter] >> speed[loadCounter] >> dir[loadCounter] >> range[loadCounter] >> 
                level[loadCounter] >> width[loadCounter] >> height[loadCounter];
            loadCounter ++;
            amountOfEnemies ++;
        }
        loadCounter = 0;
    }
    else
    {
        allegro_message("Could not locate the enemy file");
    }
}
 
void Enemy::Move(int level)
{
    for(int i = 0; i < amountOfEnemies; i++)
    {
        if(this->level[i] == level)
        {
            if(Increase[i])
                rangeCounter[i] ++;
            else
                rangeCounter[i] --;
 
            if(labs(rangeCounter[i]) == range[i])
            {
                if(dir[i] == 1)
                {
                    dir[i] = 2;
                }
                else if(dir[i] == 2)
                {
                    dir[i] = 1;
                }
                else if(dir[i] == 3)
                {
                    dir[i] = 4;
                }
                else if(dir[i] == 4)
                {
                    dir[i] = 3;
                }
 
                if(Increase[i])
                {
                    Increase[i] = false;
                }
                else
                {
                    Increase[i] = true;
                }
            }
 
 
            if(dir[i] == 1)
            {
                x[i] += speed[i];
            }
            else if (dir[i] == 2)
            {
                x[i] -= speed[i];
            }
            else if (dir[i] == 3)
            {
                y[i] -= speed[i];
            }
            else if (dir[i] == 4)
            {
                y[i] += speed[i];
            }
        }
    }
}