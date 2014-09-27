#ifndef _BULLET_H_
#define _BULLET_H_
#include "Entity.h"

class Bullet
{
public:
	Bullet(bool isEnemy);
	~Bullet();

	float getX();
	void setX(float updateX);
	float getY();
	void setY(float updateY);
	float getAngle();
	float getSize();
	bool isVisible();
	void fire(float x, float y);
	void impact();
	void update(float elapsed);

private:
	float size;
	float x;
	float y;
	float speed;
	float angle;
	bool visible;
	bool isEnemyBullet;
	float timeAlive;
};

#endif