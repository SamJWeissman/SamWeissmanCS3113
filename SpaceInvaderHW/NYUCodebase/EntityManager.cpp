#pragma once
#include "EntityManager.h"
#include "Entity.h"
#include "Player.h"
#include <vector>

EntityManager::EntityManager(Player* user) : player(user) {}
EntityManager::~EntityManager(){}

void EntityManager::moveAll(float elapsed)
{
	for (int i = 0; i < entities.size(); i++)
	{
		entities[i]->move(elapsed);
		if (entities[i]->getY() <= -1.0)
		{
			entities[i] = entities[entities.size() - 1];
			entities.pop_back();
			player->takeDamage(7);
		}
	}
}

Entity* EntityManager::getEntityAt(int index)
{
	return entities[index];
}

void EntityManager::removeEntityAt(int index)
{
	entities[index] = entities[entities.size() - 1];
	entities.pop_back();
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
		entities.pop_back();
	}
	for (int i = 0; i < 10; i++)
	{
		entities.push_back(new Entity(-1.3f + ((rand() % 130) * .01f), 1.5f, 0.0f, 425.0f / 1024.0f, 384.0f / 1024.0f, 0.1f, 0.1f, .2f + (rand() % 20 * .01f), 0.0f, -1.0f));
		entities.push_back(new Entity(0.0f + ((rand() % 130) * .01f), 1.5f, 0.0f, 425.0f / 1024.0f, 384.0f / 1024.0f, 0.1f, 0.1f, .2f + (rand() % 20 * .01f), 0.0f, -1.0f));
	}
}

void EntityManager::secondWave()
{
	while (entities.size() > 1)
	{
		entities.pop_back();
	}
	for (int i = 0; i < 10; i++)
	{
		entities.push_back(new Entity(-1.3f + ((rand() % 130) * .01f), 1.5f, 0.0f, 425.0f / 1024.0f, 552.0f / 1024.0f, 0.1f, 0.1f, .2f + (rand() % 25 * .01f), 0.0f, -1.0f));
		entities.push_back(new Entity(0.0f + ((rand() % 130) * .01f), 1.5f, 0.0f, 425.0f / 1024.0f, 552.0f / 1024.0f, 0.1f, 0.1f, .2f + (rand() % 25 * .01f), 0.0f, -1.0f));
	}
}

void EntityManager::thirdWave()
{
	while (entities.size() > 1)
	{
		entities.pop_back();
	}

	for (int i = 0; i < 10; i++)
	{
		entities.push_back(new Entity(-1.3f + ((rand() % 130) * .01f), 1.5f, 0.0f, 425.0f / 1024.0f, 468 / 1024.0f, 0.1f, 0.1f, .2f + (rand() % 30 * .01f), 0.0f, -1.0f));
		entities.push_back(new Entity(0.0f + ((rand() % 130) * .01f), 1.5f, 0.0f, 425.0f / 1024.0f, 468 / 1024.0f, 0.1f, 0.1f, .2f + (rand() % 30 * .01f), 0.0f, -1.0f));
	}
}

void EntityManager::clusterWave()
{
	float xPos = -1.3f + ((rand() % 260) * .01f);
	for (int i = 0; i < 5; i++)
	{
		entities.push_back(new Entity(xPos, 1.5f, 0.0f, 423.0f / 1024.0f, 728.0f / 1024.0f, 0.1f, 0.1f, .3f + (rand() % 20 * .01f), 0.0f, -1.0f));
	}
}