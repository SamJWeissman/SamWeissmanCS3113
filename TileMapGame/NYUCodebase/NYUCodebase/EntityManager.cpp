#include "EntityManager.h"
#include <vector>

EntityManager::EntityManager(Player *thePlayer) : player(thePlayer)
{
	eruption = false;
}
EntityManager::~EntityManager(){}

void EntityManager::spawnPrize(std::vector<Entity*> &prizes)
{
	if (rand() % 1000 > 975)
	{
		Entity* prize = new Entity(player->playerEntLegs->x + 1.33f, -1.0f + rand() % 150 * .01f, 0.0f, 0.0f, .2f, 0.2f, 0.0f, 0.0f, true);
		prizes.push_back(prize);
	}
	if (prizes.size() > 0){
		for (int i = 0; i < prizes.size(); i++)
		{
			if (fabs(player->playerEntLegs->x - prizes[i]->x) > 2.66f){
				prizes[i] = prizes[prizes.size() - 1];
				prizes.pop_back();
			}
		}
	}
}

void EntityManager::lavaEruption()
{
	if (!eruption)
	{
		float eruptionXPos = -2.66f + rand() % 532 * .01f;
		for (int i = 0; i < 20; i++)
		{
			lavaBlobs.push_back(new Entity(eruptionXPos, -2.1f - (i * .3), 0.0f, 0.0f, .1f, .1f, -1.0f + rand() % 200 * .01f, 20 + rand() % 5, false));
		}
	}
	eruption = true;
}

void EntityManager::lavaBlobCollisions(Player* player)
{
	if (eruption)
	{
		for (int i = 0; i < lavaBlobs.size(); i++)
		{
			if (player->playerEntLegs->collidesWith(lavaBlobs[i])) //hits player
			{
				lavaBlobs[i] = lavaBlobs[lavaBlobs.size() - 1];
				lavaBlobs.pop_back();
				player->health -= 5;
			}
			if (lavaBlobs[lavaBlobs.size() - 1]->y > 2.0f) //off screen
			{
				while (lavaBlobs.size() > 0)
				{
					lavaBlobs.pop_back();
				}
				eruption = false;
			}
		}
	}
}