#include "camera.h"


Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::Init()
{
	cameraX = 0;
	cameraY = 0;
}

void Camera::Update(int x, int y)
{
	Camera::SetPosition(x, y);
}

void Camera::Draw( BITMAP *Buffer)
{
	blit (Buffer, screen, cameraX, cameraY, 0, 0, ScreenWidth, ScreenHeight);
}

void Camera:: SetPosition(int x, int y)
{
	cameraX = x - ScreenWidth / 2;
	cameraY = 0;

	if (cameraX < 0)
	{
		cameraX = 0;
	}
}