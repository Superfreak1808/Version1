#include "Player.h"
#include "global.h"


Player::Player()
{

}

Player::~Player()
{

}

void Player::Init()
{
	lives = 3;
	width = 20;
	height = 31;
	x = 20;
	y = (ScreenHeight - width)/2;
	origX = x;
	origY = y;
	velx = 0;
	vely = 0;
	x2 = x + 31;
	y2 = y + 31;
	speed = 2;
	gravity = 1;
	Jump = Platform = false;
	jumpspeed = -20;
	hDir = 0;
	vDir = 2;
}

void Player::Update()
{
	Player::Controls();
	Player::SetPosition();
}

void Player::Draw(BITMAP* Buffer, BITMAP* Sprite)
{

	acquire_screen();
    draw_sprite(Buffer, Sprite, x, y);
    release_screen();

}

void Player::Controls()
{
    if (key[KEY_D])
    {
        velx = speed;
        hDir = 1;
    }
    else if (key[KEY_A])
    {
        velx = -speed;
        hDir = 2;
    }
    else
    {
        velx = 0;
        hDir = 0;
    }
    if (key[KEY_SPACE] && Jump == true)
    {
        vely = jumpspeed;
        Platform = false;
        Jump = false;
        vDir = 1;
    }
}
 

void Player::SetPosition()
{
	if(vely >= 0)
	{
		vDir = 2;
	}
	if(Platform == false)
	{
		vely +=gravity;
	}
	else
	{
		vely = 0;
	}
	
	x += velx;
	y += vely;
	x2 = x+width;
	y2 = y+height;
}

int Player::getX()
{
	return x;
}

int Player::getY()
{
	return y;
}

int Player::getX2()
{
	return x2;
}

int Player::getY2()
{
	return y2;
}

int Player::getSpeed()
{
	return speed;
}

int Player::getGravity()
{
	return gravity;
}

int Player::getVDirection()
{
	return vDir;
}

int Player::getHDirection()
{
	return hDir;
}

int Player::getVelX()
{
	return velx;
}

int Player::getVelY()
{
	return vely;
}

int Player::getLives()
{
	return lives;
}

int Player::getOrigX()
{
	return origX;
}

int Player::getOrigY()
{
	return origY;
}

bool Player::getPlatform()
{
	return Platform;
}

bool Player::getJump()
{
	return Jump;
}

// SET FUNCTIONS

void Player::setPlatform(bool value)
{
	Platform = value;
}

void Player::setJump(bool value)
{
	Jump = value;
}

void Player::setX(int value)
{
	x = value;
}

void Player::setY(int value)
{
	y = value;
}

void Player::setX2(int value)
{
	x2 = value;
}

void Player::setY2(int value)
{
	y2 = value;
}

void Player::setVelX(int value)
{
	velx = value;
}

void Player::setVelY(int value)
{
	vely = value;
}

void Player::setLives(int value)
{
	lives = value;
}