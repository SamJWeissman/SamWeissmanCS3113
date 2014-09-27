#ifndef _ENTITYMANAGER_H_
#define _ENTITYMANAGER_H_

#include "Entity.h"
#include <vector>
#include "Player.h"

class EntityManager
{
public:
	EntityManager(Player* user);
	~EntityManager();
	void moveAll(float elapsed);
	Entity* getEntityAt(int index);
	void removeEntityAt(int index);
	void pushEntity(Entity* entity);
	void removeLastEntity(Entity* entity);
	void firstWave();
	void secondWave();
	void thirdWave();
	void clusterWave();
	int numEntities();
private:
	std::vector<Entity*> entities;
	Player* player;
};

#endif