#pragma once
#include "Entity.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <stdlib.h>

Entity::Entity(float xPos, float yPos, float rot, float xOnSheet, float yOnSheet, float w, float h, float accelX, float accelY) : x(xPos), y(yPos), rotation(rot), u(xOnSheet), v(yOnSheet), width(w), height(h), acceleration_x(accelX), acceleration_y(accelY)
{
	velocity_x = 0.0f;
	velocity_y = 0.0f;
	friction_x = 2.5f;
	friction_y = 2.5f;
}

Entity::~Entity()
{
}

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

void Entity::accelerationMultiply(float accelMultiply)
{
	acceleration_x *= accelMultiply;
}

void Entity::setAccelerationX(float updateAccelX)
{
	acceleration_x = updateAccelX;
}

void Entity::bankRight()
{
	velocity_x = float(1 + rand() % 3);
	velocity_y = -1.0f;
}

void Entity::bankLeft()
{
	velocity_x = float(-(1 + rand() % 3));
	velocity_y = -1.0f;
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

float Entity::lerp(float v0, float v1, float t) {
	return (1.0 - t) * v0 + t * v1;
}

void Entity::FixedUpdate()
{
	velocity_x = lerp(velocity_x, 0.0f, FIXED_TIMESTEP * friction_x);
	velocity_y = lerp(velocity_y, 0.0f, FIXED_TIMESTEP * friction_y);

	velocity_x += acceleration_x * FIXED_TIMESTEP;
	velocity_y += acceleration_y * FIXED_TIMESTEP;
}

void Entity::move(float elapsed)
{
	x += direction_x * elapsed * speed;
	y += direction_y * elapsed * speed;
}

void Entity::moveX()
{
	x += velocity_x * FIXED_TIMESTEP;
}

void Entity::moveY()
{
	y += velocity_y * FIXED_TIMESTEP;
}