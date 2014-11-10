#ifndef _ENTITYMANAGER_H_
#define _ENTITYMANAGER_H_

#include "Entity.h"
#include <vector>
#include "Player.h"
#include "Particle.h"
#include "ParticleEmitter.h"

class EntityManager
{
public:
	EntityManager(Player* user);
	~EntityManager();
	void moveAll(float elapsed);
	bool enemyShipBrokeThrough();
	Entity* getEntityAt(int index);
	void removeEntityAt(int index);
	void pushEntity(Entity* entity);
	void removeLastEntity(Entity* entity);
	void firstWave();
	void secondWave();
	void thirdWave();
	void clusterWave();
	void renderParticles();
	void updateEmitters(float elapsed);
	int numEntities();
private:
	std::vector<Entity*> entities;
	std::vector<ParticleEmitter> particleEmitters;
	Player* player;
};

#endif