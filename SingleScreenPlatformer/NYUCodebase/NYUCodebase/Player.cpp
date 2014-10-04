#include "Player.h"
#include <vector>

Player::Player()
{
	health = 100;
	score = 0;
	energy = 500;
	playerEnt = new Entity(0.0f, 2.0f, 70.0f / 256.0f, 95.0f / 512.0f, 66.0f / 256.0f, 92.0f / 512.0f, 0.0f, 0.0f, false);
	keys = SDL_GetKeyboardState(NULL);
}
Player::~Player(){}

void Player::Update(float elapsed)
{
	if (energy <= 0)
	{
		if (!playerEnt->collidedBottom)
		{
			energy = 0;
		}
		else
		{
			energy += 5;
		}
	}
	else if(0 < energy && energy < 500)
	{
		energy += 1;
		if (playerEnt->collidedBottom)
		{
			energy += 3;
		}
	}
	else
	{
		energy = 500;
	}

	if (playerEnt->y < -1.2f)
	{
		health -= .5;
	}

	playerEnt->acceleration_x = 0;
	playerEnt->acceleration_y = 0;
	playerEnt->Update(elapsed);
}
void Player::checkInputControls()
{
	if (keys[SDL_SCANCODE_LEFT] == 1)
	{
			playerEnt->acceleration_x = -8.0f;
	}
	else if (keys[SDL_SCANCODE_RIGHT] == 1)
	{
		playerEnt->acceleration_x = 8.0f;
	}
	if (keys[SDL_SCANCODE_SPACE])
	{
		if (energy > 0){
			playerEnt->acceleration_y = 25.0f;
			energy -= 5;
		}
		else
		{
			playerEnt->acceleration_y = 30.0f;
			health -= 1;
		}
	}
}

void Player::resetPlayerEnt()
{
	playerEnt->x = 0.0f;
	playerEnt->y = 2.5f;
	playerEnt->velocity_x = 0.0f;
	playerEnt->velocity_y = 0.0f;
	playerEnt->acceleration_x = 0.0f;
	playerEnt->acceleration_y = 0.0f;
}

void Player::collectPrize(std::vector<Entity*> &prizes)
{
	for (int i = 0; i < prizes.size(); i++)
	{
		if (playerEnt->collidesWith(prizes[i]))
		{
			prizes[i] = prizes[prizes.size() - 1];
			prizes.pop_back();
			score += 10;
			if (rand() % 1000 > 750)
			{
				health += 5;
			}
			if (rand() % 1000 > 800)
			{
				energy += 50;
			}
		}
	}
}
