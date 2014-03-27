#ifndef ENEMY_H
#define ENEMY_H

#include <fstream>
#include <cmath>
#include <allegro.h>

using namespace std;

class Enemy
{
private:
	int x[10], y[10];
	int speed[10];
	int rangeCounter[10];
	int range[10];
	int dir[10];
	int level[10];
	int width[10]; 
	int height [10];
	int Increase[10];
	int loadCounter;
	int amountOfEnemies;
public:
	Enemy();
	~Enemy();

	void Init();
	void Update(int level);
	void Draw(BITMAP *Buffer, int level);

	void LoadEnemies(const char*filename);
	void Move(int level);

	int getAmountOfEnemies();
	int getX(int index);
	int getY(int index);
	int getX2(int index);
	int getY2(int index);
	int getLevel(int index);

};

#endif