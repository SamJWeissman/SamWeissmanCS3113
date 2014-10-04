#ifndef _ENTITYMANAGER_H_
#define _ENTITYMANAGER_H_

#include "Entity.h"
#include "Player.h"
#include "DrawingManager.h"
#include <vector>

class EntityManager
{
public:
	EntityManager();
	~EntityManager();
	void createLanding(std::vector<Entity*> &entities);
	void removeLanding(std::vector<Entity*> &entities);
	void spawnPrize(std::vector<Entity*> &prizes);
	void lavaEruption();
	void lavaBlobCollisions(Player* player);

	std::vector<Entity*> lavaBlobs;
	bool eruption;
};

#endif