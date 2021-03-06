#include "Bullet.h"
#include <math.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include "Entity.h"
#include <random>

const float PI = 3.141595359f;

Bullet::Bullet(bool isEnemy) : isEnemyBullet(isEnemy)
{
	size = .01f;
	speed = 0.0f;
}

void Bullet::impact()
{
	x = 0.0f;
	y = -1.5f;
	speed = 0.0f;
}

void Bullet::fire(float xStart, float yStart)
{
	if (isEnemyBullet)
	{
		x = xStart + 0.0f;
		y = yStart - 0.1f + (rand() % 10 * .01);
		speed = 1.0f;
		angle = 267 + (rand() % 6);
	}
	else
	{
		x = xStart + 0.0f;
		y = yStart + 0.1f + (rand() % 10 * .01);
		speed = 1.5f;
		angle = 87 + (rand() % 6);
	}
}

void Bullet::update(float elapsed)
{
	x += cos(angle * PI / 180.0f) * elapsed * speed;
	y += sin(angle * PI / 180.0f) * elapsed * speed;
	timeAlive += elapsed;
}

float Bullet::getX()
{
	return x;
}

void Bullet::setX(float updateX)
{
	x = updateX;
}

float Bullet::getY()
{
	return y;
}

void Bullet::setY(float updateY)
{
	y = updateY;
}
float Bullet::getAngle()
{
	return angle;
}

float Bullet::getSize()
{
	return size;
}

bool Bullet::isVisible()
{
	if ((-1.33f < x < 1.33f) && (-1.0f < y < 1.0f))
	{
		return true;
	}
	else
	{
		return false;
	}
}