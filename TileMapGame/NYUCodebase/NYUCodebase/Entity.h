#ifndef _ENTITY_H_
#define _ENTITY_H_

class Entity {
public:
	Entity(float xVal, float yVal, float uVal, float vVal, float w, float h, float accelX, float accelY, bool staticEnt);
	~Entity();
	void Update(float elapsed);
	void Render();
	bool collidesWith(Entity *entity);
	void FixedUpdate();
	void moveX();
	void moveY();
	void resetCollisionBools();
	float lerp(float v0, float v1, float t);
	float x;
	float y;
	float u;
	float v;
	float width;
	float height;
	float velocity_x;
	float velocity_y;
	float acceleration_x;
	float acceleration_y;
	float friction_x;
	float friction_y;
	float mass;
	bool isStatic;
	bool xChanged;
	bool yChanged;
	bool enableCollisions;
	bool collidedTop;
	bool collidedBottom;
	bool collidedLeft;
	bool collidedRight;
	int index;
};

#endif