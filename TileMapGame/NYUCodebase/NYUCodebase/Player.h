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
	void resetPlayerEnts();
	void collectPrize(std::vector<Entity*> &prizes, Entity *entity);
	Entity* playerEntLegs;
	Entity* playerEntTorso;
	int health;
	int score;
	int energy;
};

#endif