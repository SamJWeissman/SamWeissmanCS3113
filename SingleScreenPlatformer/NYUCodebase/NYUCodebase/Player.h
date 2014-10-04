#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <SDL.h>
#include "Entity.h"
#include <vector>

class Player
{
public:

	Player();
	~Player();
	void checkInputControls();
	const Uint8* keys;
	void Update(float elapsed);
	void resetPlayerEnt();
	void collectPrize(std::vector<Entity*> &prizes);
	Entity* playerEnt;
	int health;
	int score;
	int energy;
};

#endif