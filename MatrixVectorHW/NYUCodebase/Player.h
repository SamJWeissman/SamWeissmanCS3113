#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "Entity.h"
#include "DrawingManager.h"

class Player
{
public:
	Player(DrawingManager* drawingMgr);

	Entity* ship;
	void checkInputControls(float elapsed);
	const Uint8* keys;
	void Update(float elapsed);
	int score;
};

#endif