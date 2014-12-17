#ifndef _ENTITY_H_
#define _ENTITY_H_
#include "ParticleEmitter.h"
#include "Particle.h"

#define FIXED_TIMESTEP 0.0166666f
#define MAX_TIMESTEPS 6

class Entity {
public:

	Entity(float xPos, float yPos, float rot, float xOnSheet, float yOnSheet, float w, float h, float accelX, float accelY);
	~Entity();

	ParticleEmitter explosion;
	ParticleEmitter jetTrail;

	bool checkEntitytoEntityCollision(Entity* other);
	
	float getX();
	void setX(float updateX);

	float getY();
	void setY(float updateY);

	float getU();
	float getV();

	float getWidth();
	float getHeight();

	float getSpd();
	void setSpd(float updateSpd);

	float getVelocityX();
	void setVelocityX(float updateVelX);

	float getVelocityY();
	void setVelocityY(float updateVelY);

	float getAccelerationX();
	void setAccelerationX(float updateAccelX);

	float getAccelerationY();
	void setAccelerationY(float updateAccelY);
	void accelerationMultiply(float accelMult);

	float getFrictionX();
	void setFrictionX(float updateFrictX);

	float getFrictionY();
	void setFrictionY(float updateFrictY);

	float getDirX();
	void setDirX(float xDir);
	
	float getDirY();
	void setDirY(float yDir);

	float getTimeAlive();

	float lerp(float v0, float v1, float t);

	void bankRight();
	void bankLeft();
	void setSneaky(bool updateSneaky);
	void setSpecial(bool updateSpecial);
	bool getSpecial();
	void decrementTimeAlive(float val);

	void FixedUpdate();
	void move(float elapsed);
	void moveX();
	void moveY();

private:
	bool sneaky;
	bool special;
	float x;
	float y;
	float u;
	float v;
	float rotation;
	float width;
	float height;
	float speed;
	float velocity_x;
	float velocity_y;
	float acceleration_x;
	float acceleration_y;
	float friction_x;
	float friction_y;
	float direction_x;
	float direction_y;
	float timeAlive;

};

#endif
