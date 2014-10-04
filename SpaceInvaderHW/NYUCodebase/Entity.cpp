#pragma once
#include "Entity.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <stdlib.h>

Entity::Entity(float xPos, float yPos, float rot, float xOnSheet, float yOnSheet, float w, float h, float spd, float dir_x, float dir_y) : x(xPos), y(yPos), rotation(rot), u(xOnSheet), v(yOnSheet), width(w), height(h), speed(spd), direction_x(dir_x), direction_y(dir_y){}

float Entity::getX()
{
		return x;
}

void Entity::setX(float updateX)
{
	x = updateX;
}

float Entity::getY()
{
	return y;
}

float Entity::getU()
{
	return u;
}

float Entity::getV()
{
	return v;
}

float Entity::getWidth()
{
	return width;
}

float Entity::getHeight()
{
	return height;
}

void Entity::setDirX(float xDir)
{
	direction_x = xDir;
}

void Entity::setDirY(float yDir)
{
	direction_y = yDir;
}

void Entity::setSpd(float updateSpd)
{
	speed = updateSpd;
}

bool Entity::checkEntitytoEntityCollision(Entity* other)
{
	if (y - (height / 2.0f) > (other->y + ((other->height) / 2.0f)) || (y + (height / 2.0f) < (other->y - ((other->height) / 2.0f))) || (x - (width / 2.0f) > (other->x + ((other->width) / 2.0f))) || (x + (width / 2.0f) < (other->x - ((other->width) / 2.0f))))
	{
		return false;
	}
	else
	{
		return true;
	}
}

void Entity::move(float elapsed)
{
	x += direction_x * elapsed * speed;
	y += direction_y * elapsed * speed;
}