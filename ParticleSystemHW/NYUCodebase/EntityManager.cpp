#pragma once
#include "EntityManager.h"
#include "Entity.h"
#include "Player.h"
#include <vector>

EntityManager::EntityManager(Player* user) : player(user) {}
EntityManager::~EntityManager(){}

bool EntityManager::enemyShipBrokeThrough()
{
	bool shipsBrokeThrough = false;
	for (int i = 0; i < entities.size(); i++)
	{
		if (entities[i]->getY() <= -1.0)
		{
			entities[i] = entities[entities.size() - 1];
			//delete(entities[entities.size() - 1]);
			entities.pop_back();
			player->takeDamage(4);
			shipsBrokeThrough = true;
		}
	}
	return shipsBrokeThrough;
}

void EntityManager::updateEmitters(float elapsed)
{
	for (int i = 0; i < particleEmitters.size(); i++)
	{
		particleEmitters[i].Update(elapsed);
		if (particleEmitters[i].removeMe)
		{
			particleEmitters[i] = particleEmitters[particleEmitters.size() - 1];
			//delete(particleEmitters[particleEmitters.size() - 1]);
			particleEmitters.pop_back();
		}
	}
}

Entity* EntityManager::getEntityAt(int index)
{
	return entities[index];
}

void EntityManager::removeEntityAt(int index)
{
	//entities[index]->particleEmitter = new ParticleEmitter();
	entities[index]->explosion.x = entities[index]->getX();
	entities[index]->explosion.y = entities[index]->getY();
	entities[index]->explosion.removeMe = false;
	
	for (int i = 0; i < 10; i++)
	{
		Particle particle;
		particle.x = entities[index]->explosion.x;
		particle.y = entities[index]->explosion.y;
		particle.velocity_x = -.05f + rand() % 10 * .01f;
		particle.velocity_y = -.05f + rand() % 10 * .01f;
		entities[index]->explosion.particles.push_back(particle);
	}
	entities[index]->explosion.maxLifetime = 0.25f;
	particleEmitters.push_back(entities[index]->explosion);
	entities[index] = entities[entities.size() - 1];
	//delete(entities[entities.size() - 1]);
	entities.pop_back();
}

void EntityManager::renderParticles()
{
	for (int i = 0; i < particleEmitters.size(); i++)
	{
		particleEmitters[i].Render();
	}
}

void EntityManager::pushEntity(Entity* entity)
{
	entities.push_back(entity);
}

void EntityManager::removeLastEntity(Entity* entity)
{
	entities.pop_back();
}

int EntityManager::numEntities()
{
	return entities.size();
}

void EntityManager::firstWave()
{
	while (entities.size() > 1)
	{
		//delete(entities[entities.size() - 1]);
		entities.pop_back();
	}
	for (int i = 0; i < 10; i++)
	{
		entities.push_back(new Entity(-1.3f + ((rand() % 130) * .01f), 1.5f, 0.0f, 425.0f / 1024.0f, 384.0f / 1024.0f, 0.1f, 0.1f, 0.0f, -(.3f + (rand() % 7 * .1f))));
		entities.push_back(new Entity(0.0f + ((rand() % 130) * .01f), 1.5f, 0.0f, 425.0f / 1024.0f, 384.0f / 1024.0f, 0.1f, 0.1f, 0.0f, -(.3f + (rand() % 7 * .1f))));
	}
}

void EntityManager::secondWave()
{
	while (entities.size() > 1)
	{
		//delete(entities[entities.size() - 1]);
		entities.pop_back();
	}
	for (int i = 0; i < 10; i++)
	{
		entities.push_back(new Entity(-1.3f + ((rand() % 130) * .01f), 1.5f, 0.0f, 425.0f / 1024.0f, 552.0f / 1024.0f, 0.1f, 0.1f, 0.0f, -(.4f + (rand() % 7 * .1f))));
		entities.push_back(new Entity(0.0f + ((rand() % 130) * .01f), 1.5f, 0.0f, 425.0f / 1024.0f, 552.0f / 1024.0f, 0.1f, 0.1f, 0.0f, -(.4f + (rand() % 7 * .1f))));
	}
}

void EntityManager::thirdWave()
{
	while (entities.size() > 1)
	{
		//delete(entities[entities.size() - 1]);
		entities.pop_back();
	}

	for (int i = 0; i < 10; i++)
	{
		entities.push_back(new Entity(-1.3f + ((rand() % 130) * .01f), 1.5f, 0.0f, 425.0f / 1024.0f, 468 / 1024.0f, 0.1f, 0.1f, 0.0f, -(.5f + (rand() % 7 * .1f))));
		entities.push_back(new Entity(0.0f + ((rand() % 130) * .01f), 1.5f, 0.0f, 425.0f / 1024.0f, 468 / 1024.0f, 0.1f, 0.1f, 0.0f, -(.5f + (rand() % 7 * .1f))));
	}
}

void EntityManager::clusterWave()
{
	float acceleration = -(.6f + (rand() % 7 * .1f));
	float xPos = -1.3f + ((rand() % 260) * .01f);
	for (int i = 0; i < 5; i++)
	{
		entities.push_back(new Entity(xPos, 1.5f + (i * 0.1f), 0.0f, 423.0f / 1024.0f, 728.0f / 1024.0f, 0.1f, 0.1f, 0.0f, acceleration));
	}
}