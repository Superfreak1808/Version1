#include <allegro.h>

#ifndef PLAYER_H
#define PLAYER_H

class Player
{
private:
		int x, y;
		int origX, origY;
        int x2, y2;
        int width, height;
        int hDir, vDir;
        int velx, vely;
        int speed, jumpspeed;
        int gravity;
        bool Jump, Platform;
		int lives;
		int a, b;
    public:
        Player();
        ~Player();

        void Init();
		// Changed
        void Update();
        void Draw(BITMAP *Buffer, BITMAP *Sprite);

        void Controls();
        void SetPosition();

		int getX(); 
		int getY(); 
		int getX2(); 
		int getY2(); 
		int getA();
		int getB();
		int getSpeed(); 
		int getGravity();
		int getVDirection();
		int getHDirection();
		int getVelX(); 
		int getVelY();
		int getLives();
		int getOrigX(); 
		int getOrigY();
		bool getPlatform();
		bool getJump();
		

		void setPlatform(bool value);
		void setJump(bool value);
		void setX(int value); 
		void setY(int value);
		void setX2(int value); 
		void setY2(int value);
		void setVelX(int value); 
		void setVelY(int value);
		void setLives(int value);
};
#endif