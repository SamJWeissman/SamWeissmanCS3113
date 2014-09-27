#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <SDL.h>
#include "Entity.h"
#include "Bullet.h"
#include <vector>

class Player
{
public:

	Player();
	~Player();
	Entity* getSpaceship();
	std::vector<Bullet*> getBullets();
	void takeDamage(int damage);
	void changeScore(int points);
	int getHealth();
	void increaseHealth();
	int getScore();
	void resetScore();
	void shoot();
	void clearBullets();
	const Uint8* getKeys();
	void checkInputControls();
	void setHealth(int health);

private:
	int bulletCounter;
	int score;
	int health;
	std::vector<Bullet*> bullets;
	const Uint8* keys;
	Entity* spaceShip;
};

#endif
