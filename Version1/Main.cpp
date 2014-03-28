#include <allegro.h>
#include <iostream>
#include <sstream>
#include <ctime>
#include "enemy.h"
#include "Player.h"
#include "global.h"
#include "camera.h"
#include "map.h"
#include "Collision.h"

using namespace std;

volatile long counter = 0;

void Increment()
{
	counter ++;
}

int main(){
 
    allegro_init();
    install_keyboard();
	install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, "A");
	set_color_depth(32);
    set_gfx_mode( GFX_AUTODETECT_WINDOWED, ScreenWidth, ScreenHeight, 0, 0);

	LOCK_VARIABLE(counter);
	LOCK_FUNCTION(Increment);

	install_int_ex(Increment, BPS_TO_TIMER(100));

	srand(time(0));

	Player player;
	Camera camera;
	Map map;
	Collision collision;
	Enemy enemy;

	player.Init();
	camera.Init();
	map.Init();
	enemy.Init();
	collision.Init();

	BITMAP *Buffer = create_bitmap (6000, 600);
	BITMAP *Sprite;
	Sprite = load_bitmap( "first.bmp", NULL);
	BITMAP *Enemy;
	Enemy = load_bitmap( "test2.bmp", NULL);
	BITMAP *Brick;
	Brick = load_bitmap( "brick.bmp", NULL);
	BITMAP *Floor;
	Floor = load_bitmap( "floor.bmp", NULL);
	BITMAP *Floor2;
	Floor2 = load_bitmap( "floor2.bmp", NULL);
	BITMAP *Floor3;
	Floor3 = load_bitmap( "floor3.bmp", NULL);
	BITMAP *Cloud;
	Cloud = load_bitmap( "cloud.bmp", NULL);

	bool done = false;

	while (!done)
	{
		while (counter > 0)
		{
			//Input
			if(key[KEY_ESC])
			{
				done = true;
			}
			//Update
			map.Update();
			player.Update();
			enemy.Update(map.getLevel());
			collision.Update(Buffer, player, enemy, map);
			camera.Update(player.getX(), player.getY());
			counter --;
		}

		//Draw
		map.Draw(Buffer, Brick, Floor, Floor2, Floor3, Cloud);
		player.Draw(Buffer, Sprite);
		enemy.Draw(Buffer, Enemy, map.getLevel());
		stringstream str;
		str << player.getLives();
		textout_ex(Buffer, font, str.str().c_str(), 10, 10, makecol(255,0,0), -1);
		camera.Draw(Buffer);
		clear_bitmap(Buffer);
	}
    
    return 0;
    
}   
END_OF_MAIN()