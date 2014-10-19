#include "Player.h"
#include <vector>

Player::Player()
{
	score = 0;
	energy = 300;
	playerEntLegs = new Entity(-2.66f, 2.0f, 0.0f, 0.0f, .1f, .15f, 0.0f, 0.0f, false);
	playerEntTorso = new Entity(-2.66f, 2.15f, 0.0f, 0.0f, .075f, .1f, 0.0f, 0.0f, false);
	keys = SDL_GetKeyboardState(NULL);
}
Player::~Player(){}

void Player::Update(float elapsed)
{
	score += 1;
	if (energy <= 0)
	{
		if (!playerEntLegs->collidedBottom)
		{
			energy = 0;
		}
		else
		{
			energy += 5;
		}
	}
	else if(0 < energy && energy < 300)
	{
		energy += 1;
		if (playerEntLegs->collidedBottom)
		{
			energy += 3;
		}
	}
	else
	{
		energy = 300;
	}
	playerEntLegs->acceleration_x = 20.00f;
	playerEntLegs->acceleration_y = 0;
	playerEntLegs->Update(elapsed);
	playerEntTorso->x = playerEntLegs->x;
	playerEntTorso->y = playerEntLegs->y + playerEntLegs->height / 2.0;
}
void Player::checkInputControls()
{
	if (keys[SDL_SCANCODE_SPACE])
	{
		if (energy > 0){
			playerEntLegs->acceleration_y = 35.0f;
			energy -= 5;
			jetPack = true;
		}
	}
	if (keys[SDL_SCANCODE_DOWN])
	{
		playerEntLegs->height = .075;
		playerEntTorso->height = .0375;
	}
}	

void Player::resetPlayerEnts()
{
	playerEntLegs->height = .15;
	playerEntTorso->height = .075;
}

void Player::collectPrize(std::vector<Entity*> &prizes, Entity *entity)
{
	for (int i = 0; i < prizes.size(); i++)
	{
		if (playerEntTorso->collidesWith(prizes[i]) || playerEntLegs->collidesWith(prizes[i]))
		{
			prizes[i] = prizes[prizes.size() - 1];
			prizes.pop_back();
			score += 500;
			collectedPrize = true;
			if (rand() % 100 > 75){
				energy = 300;
				playerEntLegs->velocity_y += 10.0f;
				playerEntLegs->velocity_x += 5.0f;
			}
		}
	}
}

