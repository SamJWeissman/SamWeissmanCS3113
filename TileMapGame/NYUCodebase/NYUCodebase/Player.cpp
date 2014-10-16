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
			playerEntLegs->acceleration_y = 25.0f;
			energy -= 5;
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

