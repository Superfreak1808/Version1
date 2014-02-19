#include <allegro.h>
#include "global.h"

class Camera
{
public:
	Camera();
	~Camera();

	void Init();
	void Update(int x, int y);
	void Draw(BITMAP *buffer);

	void SetPosition(int x, int y);


private:
int cameraX, cameraY;

};

