#include "Player.h"


Player::Player()
{

}

Player::~Player()
{

}

void Player::Init()
{
	x = 10;
	y = 10;
	width = 10;
	height = 10;
	velx = 0;
	vely = 0;
	x2 = x + 10;
	y2 = y + 10;
	speed = 2;
	gravity = 1;
	Jump = Platform = false;
	jumpspeed = -15;
	hDir = 0;
	vDir = 2;
}

void Player::Update()
{
	Player::Controls();
	Player::SetPosition();
}

void Player::Draw(BITMAP* Buffer)
{
	rectfill (Buffer, x, y, x2, y2, makecol(255,0,0));
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