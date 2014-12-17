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
	void shoot(bool special);
	const Uint8* getKeys();
	void checkInputControls();
	void setHealth(int health);
	void placeWarp();
	void moveToWarp();
	void setWarped(bool updateWarped);
	bool playerWarped();
	bool getBoost();
	void setBigGun(bool updateBigGun);
	bool getBigGun();
	bool isWarp();
	float getWarpX();

private:
	int bulletCounter;
	int score;
	int health;
	float warp;
	bool warpSet;
	bool warped;
	bool boost;
	bool bigGun;
	std::vector<Bullet*> bullets;
	const Uint8* keys;
	Entity* spaceShip;
};

#endif
