#pragma once
#include "Player.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include "Entity.h"
#include <vector>

Player::Player()
{
	bulletCounter = 0;
	score = 0;
	health = 100;
	for (int i = 0; i < 30; i++)
	{
		bullets.push_back(new Bullet(false));
	}
	keys = SDL_GetKeyboardState(NULL);
	spaceShip = new Entity(0.0f, -0.9f, 0.0f, 346.0f / 1024.0f, 75.0f / 1024.0f, 98.0f / 1024.0f, 75.0f / 1024.0f, 1.0f, 0.0f, 0.0f);
}

Player::~Player()
{

}

void Player::takeDamage(int damage)
{
	health -= damage;
}

void Player::changeScore(int points)
{
	score += points;
}

void Player::resetScore()
{
	score = 0;
}
int Player::getHealth()
{
	return health;
}

void Player::increaseHealth()
{
	if (rand() % 10 > 5)
	{
		health++;
	}
}

int Player::getScore()
{
	return score;
}

void Player::setHealth(int newHealth)
{
	health = newHealth;
}

const Uint8* Player::getKeys()
{
	return keys;
}

Entity* Player::getSpaceship()
{
	return spaceShip;
}

std::vector<Bullet*> Player::getBullets()
{
	return bullets;
}

void Player::shoot()
{
	if (bullets[bulletCounter] != nullptr)
	{
		bullets[bulletCounter]->fire(spaceShip->getX(), spaceShip->getY());
	}
	bulletCounter++;
	if (bulletCounter == 15)
	{
		bulletCounter = 0;
	}
}

void Player::clearBullets()
{
	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i]->setX(0.0f);
		bullets[i]->setY(-1.5f);
	}
}

void Player::checkInputControls()
{
	if (keys[SDL_SCANCODE_LEFT] == 1)
	{
		if (-1.32f < spaceShip->getX())
		{
			spaceShip->setDirX(-1.0f);
		}
	}
	else if (keys[SDL_SCANCODE_RIGHT] == 1)
	{
		if (spaceShip->getX() < 1.32f)
		{
			spaceShip->setDirX(1.0f);
		}
	}
	if (keys[SDL_SCANCODE_LSHIFT] == 1)
	{
		spaceShip->setSpd(2.0f);
	}
}
