#pragma once
#include "Player.h"

Player::Player()
{
	bulletCounter = 0;
	score = 0;
	health = 100;
	bigGun = false;
	for (int i = 0; i < 40; i++)
	{
		bullets.push_back(new Bullet(false));
	}
	keys = SDL_GetKeyboardState(NULL);
	spaceShip = new Entity(0.0f, -0.9f, 0.0f, 346.0f / 1024.0f, 75.0f / 1024.0f, 98.0f / 1024.0f, 75.0f / 1024.0f, 0.0f, 0.0f);
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

void Player::shoot(bool special)
{
	if (bullets[bulletCounter] != nullptr)
	{
		bullets[bulletCounter]->fire(spaceShip->getX(), spaceShip->getY(), special);
	}
	bulletCounter++;
	if (bulletCounter == 20)
	{
		bulletCounter = 0;
	}
}

bool Player::getBoost()
{
	return boost;
}

void Player::placeWarp()
{
	warp = spaceShip->getX();
	warpSet = true;
}

bool Player::playerWarped()
{
	return warped;
}

void Player::setWarped(bool updateWarped)
{
	warped = updateWarped;
}

bool Player::isWarp()
{
	return warpSet;
}

float Player::getWarpX()
{
	return warp;
}

void Player::moveToWarp()
{
	if (warpSet)
	{
		spaceShip->setX(warp);
		warpSet = false;
		warped = true;
	}
}

void Player::setBigGun(bool updateBigGun)
{
	bigGun = updateBigGun;
}

bool Player::getBigGun()
{
	return bigGun;
}

void Player::checkInputControls()
{
	if (keys[SDL_SCANCODE_LEFT] == 1)
	{
		if (-1.32f < spaceShip->getX())
		{
			spaceShip->setAccelerationX(-3.0f);
		}
	}
	else if (keys[SDL_SCANCODE_RIGHT] == 1)
	{
		if (spaceShip->getX() < 1.32f)
		{
			spaceShip->setAccelerationX(3.0f);
		}
	}
	else
	{
		spaceShip->setAccelerationX(0.0f);
	}

	if (keys[SDL_SCANCODE_LSHIFT] == 1)
	{
		spaceShip->accelerationMultiply(2.0f);
		boost = true;
	}
	else
	{
		boost = false;
	}

	if (keys[SDL_SCANCODE_Z] == 1)
	{
		placeWarp();
	}
	if (keys[SDL_SCANCODE_X] == 1)
	{
		moveToWarp();
	}
}
