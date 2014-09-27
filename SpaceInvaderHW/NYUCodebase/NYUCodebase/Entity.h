#ifndef _ENTITY_H_
#define _ENTITY_H_

class Entity {
public:

	Entity(float xPos, float yPos, float rot, float xOnSheet, float yOnSheet, float w, float h, float spd, float dir_x, float dir_y);
	~Entity();

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

	float getDirX();
	void setDirX(float xDir);
	
	float getDirY();
	void setDirY(float yDir);

	void move(float elapsed);

private:
	float x;
	float y;
	float u;
	float v;
	float rotation;
	float width;
	float height;
	float speed;
	float direction_x;
	float direction_y;

};

#endif
