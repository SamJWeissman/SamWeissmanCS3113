#pragma once
#include "EntityManager.h"


EntityManager::EntityManager(Player* user) : player(user) 
{
	multiplier = 1.0f;
}
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
			player->takeDamage(3);
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
	entities[index]->explosion.maxLifetime = 0.5f;
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

void EntityManager::orangeWave()
{
	while (entities.size() > 1)
	{
		//delete(entities[entities.size() - 1]);
		entities.pop_back();
	}
	for (int i = 0; i < 10; i++)
	{
		entities.push_back(new Entity(-1.3f + ((rand() % 130) * .01f), 1.5f, 0.0f, 425.0f / 1024.0f, 384.0f / 1024.0f, 0.1f, 0.1f, 0.0f, -(.3f * multiplier +(rand() % 7 * .1f))));
		entities.push_back(new Entity(0.0f + ((rand() % 130) * .01f), 1.5f, 0.0f, 425.0f / 1024.0f, 384.0f / 1024.0f, 0.1f, 0.1f, 0.0f, -(.3f * multiplier + (rand() % 7 * .1f))));
	}
}

void EntityManager::greenWave()
{
	while (entities.size() > 1)
	{
		//delete(entities[entities.size() - 1]);
		entities.pop_back();
	}
	for (int i = 0; i < 10; i++)
	{
		entities.push_back(new Entity(-1.3f + ((rand() % 130) * .01f), 1.5f, 0.0f, 425.0f / 1024.0f, 552.0f / 1024.0f, 0.1f, 0.1f, 0.0f, -(.4f * multiplier + (rand() % 7 * .1f))));
		entities.push_back(new Entity(0.0f + ((rand() % 130) * .01f), 1.5f, 0.0f, 425.0f / 1024.0f, 552.0f / 1024.0f, 0.1f, 0.1f, 0.0f, -(.4f * multiplier + (rand() % 7 * .1f))));
	}
}

void EntityManager::blueWave()
{
	while (entities.size() > 1)
	{
		//delete(entities[entities.size() - 1]);
		entities.pop_back();
	}

	for (int i = 0; i < 10; i++)
	{
		entities.push_back(new Entity(-1.3f + ((rand() % 130) * .01f), 1.5f, 0.0f, 425.0f / 1024.0f, 468 / 1024.0f, 0.1f, 0.1f, 0.0f, -(.5f * multiplier + (rand() % 7 * .1f))));
		entities.push_back(new Entity(0.0f + ((rand() % 130) * .01f), 1.5f, 0.0f, 425.0f / 1024.0f, 468 / 1024.0f, 0.1f, 0.1f, 0.0f, -(.5f * multiplier + (rand() % 7 * .1f))));
	}
}

void EntityManager::sneakyWave() 
{
	float acceleration = -1.0f;
	float xPos = -.6f + ((rand() % 120) * .01f);
	for (int i = 0; i < 5; i++)
	{
		Entity* sneakyEnt = new Entity(xPos, 1.5f + (i * 0.1f), 0.0f, 423.0f / 1024.0f, 728.0f / 1024.0f, 0.1f, 0.1f, 0.0f, acceleration * multiplier);
		sneakyEnt->setSneaky(true);
		sneakyEnt->decrementTimeAlive(i * .1f);
		entities.push_back(sneakyEnt);
	}
}

void EntityManager::linearWave()
{
	float acceleration = -(.6f + (rand() % 7 * .1f));
	float xPos = -1.3f + ((rand() % 260) * .01f);
	for (int i = 0; i < 5; i++)
	{
		entities.push_back(new Entity(xPos, 1.5f + (i * 0.1f), 0.0f, 423.0f / 1024.0f, 728.0f / 1024.0f, 0.1f, 0.1f, 0.0f, acceleration * multiplier));
	}
}

void EntityManager::specialEnt()
{
	float acceleration = -1.0f;
	float xPos = -.6f + ((rand() % 120) * .01f);
	Entity* specialEnt = new Entity(xPos, 1.5f, 0.0f, 444.0f / 1024.0f, 91.0f / 1024.0f, 0.09f, 0.09f, 0.0f, acceleration * multiplier);
	specialEnt->setSneaky(true);
	specialEnt->setSpecial(true);
	entities.push_back(specialEnt);
}


void EntityManager::increaseSpeed()
{
	multiplier += 0.5f;
}

void EntityManager::resetSpeed()
{
	multiplier = 1.0f;
}
