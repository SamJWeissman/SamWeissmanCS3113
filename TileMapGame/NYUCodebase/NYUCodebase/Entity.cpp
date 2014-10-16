#include "Entity.h"

#define FIXED_TIMESTEP 0.0166666f
#define MAX_TIMESTEPS 6
#define GRAVITY_X 0.0f
#define GRAVITY_Y -15.0f

Entity::Entity(float xVal, float yVal, float uVal, float vVal, float w, float h, float accelX, float accelY, bool staticEnt) : 
					x(xVal), y(yVal), u(uVal), v(vVal), width(w), height(h), acceleration_x(accelX), acceleration_y(accelY), isStatic(staticEnt)
{
	velocity_x = 0.0f;
	velocity_y = 0.0f;
	friction_x = 5.0f;
	friction_y = 5.0f;
}
Entity::~Entity(){}

void Entity::Update(float elapsed)
{
	velocity_x += GRAVITY_X * elapsed;
	velocity_y += GRAVITY_Y * elapsed;
	resetCollisionBools();
}
void Entity::Render(){}
bool Entity::collidesWith(Entity *entity)
{
	if (y - (height / 2.0f) > (entity->y + ((entity->height) / 2.0f)) || (y + (height / 2.0f) < (entity->y - ((entity->height) / 2.0f))) || (x - (width / 2.0f) > (entity->x + ((entity->width) / 2.0f))) || (x + (width / 2.0f) < (entity->x - ((entity->width) / 2.0f))))
	{
		return false;
	}
	else
	{
		return true;
	}
}
void Entity::FixedUpdate()
{
	if (!isStatic)
	{
		velocity_x = lerp(velocity_x, 0.0f, FIXED_TIMESTEP * friction_x);
		velocity_y = lerp(velocity_y, 0.0f, FIXED_TIMESTEP * friction_y);

		velocity_x += acceleration_x * FIXED_TIMESTEP;
		velocity_y += acceleration_y * FIXED_TIMESTEP;
	}
}
float Entity::lerp(float v0, float v1, float t)
{
	return (1.0f - t) * v0 + t * v1;
}

void Entity::moveY()
{

	if (!isStatic)
	{
		y += velocity_y * FIXED_TIMESTEP;
	}
}

void Entity::moveX()
{

	if (!isStatic)
	{
		x += velocity_x * FIXED_TIMESTEP;
	}
}

void Entity::resetCollisionBools()
{
	collidedTop = false;
	collidedBottom = false;
	collidedLeft = false;
	collidedRight = false;
}