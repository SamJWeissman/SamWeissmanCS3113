#ifndef _ENTITY_H_
#define _ENTITY_H_
#include <SDL_opengl.h>
#include "DrawingManager.h"
#include "Matrix.h"
#include "Vector.h"
#define FIXED_TIMESTEP 0.0166666f
#define MAX_TIMESTEPS 6
#define GRAVITY_X 0.0f
#define GRAVITY_Y 0.0f
#define PI 3.14159265359

class Entity 
{
public:

	Entity(DrawingManager* drawingManager);
	Matrix matrix;
	Vector velocity;
	DrawingManager* drawingMgr;
	float x;
	float y;
	float angle;
	float scale_x;
	float scale_y;
	float rotation;
	float width;
	float height;
	float velocity_x;
	float velocity_y;
	float friction_x;
	float friction_y;
	float acceleration_x;
	float acceleration_y;
	bool collidedBottom;
	bool collidedTop;
	bool collidedRight;
	bool collidedLeft;
	bool isPlayer;

	void renderMeteor();
	void renderShip();
	void resetCollisionBools();
	void buildMatrix();
	void Update(float elapsed);
	void FixedUpdate();
	void moveX();
	void moveY();
	void movePlayer();

	void converToOtherEntityObjectSpace(Entity* entity);
	float lerp(float v0, float v1, float t);
	bool collidesWith(Entity* entity);
};

#endif