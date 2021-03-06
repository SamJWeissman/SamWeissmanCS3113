#ifndef _ENTITYMANAGER_H_
#define _ENTITYMANAGER_H_

#include "Entity.h"
#include "Player.h"
#include "Particle.h"
#include "ParticleEmitter.h"
#include <vector>

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
	void orangeWave();
	void greenWave();
	void blueWave();
	void sneakyWave();
	void linearWave();
	void specialEnt();
	void renderParticles();
	void updateEmitters(float elapsed);
	int numEntities();
	void increaseSpeed();
	void resetSpeed();
private:
	std::vector<Entity*> entities;
	std::vector<ParticleEmitter> particleEmitters;
	Player* player;
	float multiplier;
};

#endif