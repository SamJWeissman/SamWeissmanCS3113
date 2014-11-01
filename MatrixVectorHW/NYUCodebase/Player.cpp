#include "Player.h"


Player::Player(DrawingManager* drawingMgr)
{
	score = 0;

	ship = new Entity(drawingMgr);
	ship->acceleration_x = 0.0f;
	ship->acceleration_y = 0.0f;
	ship->velocity_x = 0.0f;
	ship->velocity_y = 0.0f;
	ship->x = 0.0f;
	ship->y = 0.0f;
	//ship->vector.x = 0.0f;
	//ship->vector.y = 0.0f;
	//ship->vector.z = 0.0f;
	ship->width = .2f;
	ship->height = .2f;
	ship->scale_x = 1.0f;
	ship->scale_y = 1.0f;
	ship->rotation = 0.0f;
	ship->friction_x = 2.0f;
	ship->friction_y = 2.0f;
	ship->isPlayer = true;

	keys = SDL_GetKeyboardState(NULL);
}

void Player::Update(float elapsed)
{
	//if (ship->acceleration_x >= 0.0f)ship->acceleration_x -= 0.8f;
	//if (ship->acceleration_x <= 0.0f)ship->acceleration_x += 0.8f;
	//if(ship->acceleration_y >= 0.0f) ship->acceleration_y -= 0.8f;
	//if (ship->acceleration_y <= 0.0f)ship->acceleration_y += 0.8f;
	ship->velocity_x = 0.0f;
	ship->velocity_y = 0.0f;
}

void Player::checkInputControls(float elapsed)
{
	if (keys[SDL_SCANCODE_SPACE])
	{
		//shoot();
	}
	if (keys[SDL_SCANCODE_DOWN])
	{
		ship->acceleration_y -= 1.0f;
	}
	if (keys[SDL_SCANCODE_UP])
	{
		ship->acceleration_y += 1.0f;
	}
	if (keys[SDL_SCANCODE_LEFT])
	{
		//ship->acceleration_x -= 1.0f;
		//ship->acceleration_x += 2.0f;
		//if (ship->angle >= 360.0f) ship->angle = 0.0f;
		ship->rotation += 1.0f * FIXED_TIMESTEP;
	}
	if (keys[SDL_SCANCODE_RIGHT])
	{
		//ship->acceleration_x += 1.0f;
		//ship->acceleration_x += 2.0f;
		//if (ship->angle <= -360.0f) ship->angle = 0.0f;
		ship->rotation -= 1.0f * FIXED_TIMESTEP;
	}
}