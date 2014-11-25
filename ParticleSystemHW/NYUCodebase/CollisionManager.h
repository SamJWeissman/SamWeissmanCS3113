#ifndef _COLLISIONMANAGER_H_
#define _COLLISIONMANAGER_H_

#include "Entity.h"
#include "EntityManager.h"
#include "Bullet.h"
#include "Player.h"
#include <vector>

class CollisionManager{
public:
	CollisionManager(std::vector<Bullet*> bullets, EntityManager* entityMgr, Player* user);
	~CollisionManager();
	bool bulletsVsEntities();
	bool entityVsPlayer();
	bool bulletsVsPlayer();

private:

	std::vector<Bullet*> playerBullets;
	std::vector<Bullet*> enemyBullets;
	EntityManager* entityManager;
	Player* player;
};

#endif