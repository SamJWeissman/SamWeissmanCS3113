#pragma once
#include "CollisionManager.h"



CollisionManager::CollisionManager(std::vector<Bullet*> bullets, EntityManager* entityMgr, Player* user) : enemyBullets(bullets), entityManager(entityMgr), player(user) 
{
	playerBullets = player->getBullets();
}
CollisionManager::~CollisionManager(){}

bool CollisionManager::bulletsVsEntities()
{
	bool enemyDestroyed = false;
	for (int i = 0; i < playerBullets.size(); i++)
	{
		for (int j = 0; j < entityManager->numEntities(); j++)
		{
			if (playerBullets[i]->getY() - (playerBullets[i]->getSize() / 2.0f) >(entityManager->getEntityAt(j)->getY() + ((entityManager->getEntityAt(j)->getHeight()) / 2.0f)) ||
				(playerBullets[i]->getY() + (playerBullets[i]->getSize() / 2.0f) < (entityManager->getEntityAt(j)->getY() - ((entityManager->getEntityAt(j)->getHeight()) / 2.0f))) ||
				(playerBullets[i]->getX() - (playerBullets[i]->getSize() / 2.0f) > (entityManager->getEntityAt(j)->getX() + ((entityManager->getEntityAt(j)->getWidth()) / 2.0f))) ||
				(playerBullets[i]->getX() + (playerBullets[i]->getSize() / 2.0f) < (entityManager->getEntityAt(j)->getX() - ((entityManager->getEntityAt(j)->getWidth()) / 2.0f))))
			{
				continue;
			}
			else
			{
				playerBullets[i]->impact();
				entityManager->removeEntityAt(j);
				player->changeScore(5);
				player->increaseHealth();
				enemyDestroyed = true;
			}
		}
	}
	return enemyDestroyed;
}

bool CollisionManager::entityVsPlayer()
{
	bool shakeScreen = false;
	for (int i = 1; i < entityManager->numEntities(); i++)
	{
		if (entityManager->getEntityAt(0)->getY() - (entityManager->getEntityAt(0)->getHeight() / 2.0f) > (entityManager->getEntityAt(i)->getY() + ((entityManager->getEntityAt(i)->getHeight()) / 2.0f)) ||
			(entityManager->getEntityAt(0)->getY() + (entityManager->getEntityAt(0)->getHeight() / 2.0f) < (entityManager->getEntityAt(i)->getY() - ((entityManager->getEntityAt(i)->getHeight()) / 2.0f))) ||
			(entityManager->getEntityAt(0)->getX() - (entityManager->getEntityAt(0)->getWidth() / 2.0f) > (entityManager->getEntityAt(i)->getX() + ((entityManager->getEntityAt(i)->getWidth()) / 2.0f))) ||
			(entityManager->getEntityAt(0)->getX() + (entityManager->getEntityAt(0)->getWidth() / 2.0f) < (entityManager->getEntityAt(i)->getX() - ((entityManager->getEntityAt(i)->getWidth()) / 2.0f))))
		{
			continue;
		}
		else
		{
			entityManager->removeEntityAt(i);
			player->takeDamage(2);
			shakeScreen = true;
		}
	}
	return shakeScreen;
}

bool CollisionManager::bulletsVsPlayer()
{
	bool shakeScreen = false;
	for (int i = 0; i < enemyBullets.size(); i++)
	{
		for (int j = 0; j < entityManager->numEntities(); j++)
		{
			if (enemyBullets[i]->getY() - (enemyBullets[i]->getSize() / 2.0f) >(entityManager->getEntityAt(0)->getY() + ((entityManager->getEntityAt(0)->getHeight()) / 2.0f)) ||
				(enemyBullets[i]->getY() + (enemyBullets[i]->getSize() / 2.0f) < (entityManager->getEntityAt(0)->getY() - ((entityManager->getEntityAt(0)->getHeight()) / 2.0f))) ||
				(enemyBullets[i]->getX() - (enemyBullets[i]->getSize() / 2.0f) > (entityManager->getEntityAt(0)->getX() + ((entityManager->getEntityAt(0)->getWidth()) / 2.0f))) ||
				(enemyBullets[i]->getX() + (enemyBullets[i]->getSize() / 2.0f) < (entityManager->getEntityAt(0)->getX() - ((entityManager->getEntityAt(0)->getWidth()) / 2.0f))))
				{
					continue;
				}
				else
				{
					enemyBullets[i]->impact();
					player->takeDamage(1);
					shakeScreen = true;
				}
		}
	}
	return shakeScreen;
}