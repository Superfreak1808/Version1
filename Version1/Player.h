#include <allegro.h>

#ifndef PLAYER_H
#define PLAYER_H

class Player
{
private:


public:
	Player();
	~Player();

	void Init();
	void Update();
	void Draw(BITMAP *Buffer);

	void Controls();
	void SetPosition();

	int x;
	int y;
	int origX, origY;
	int x2, y2;
	int width, height;
	int hDir, vDir;
	int gravity;
	bool Jump, Platform;
	int velx;
	int vely;
	int speed;
	int jumpspeed;
	int lives;



};
#endif