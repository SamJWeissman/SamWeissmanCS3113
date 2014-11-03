#include "Entity.h"

Entity::Entity(DrawingManager* drawingManager) : drawingMgr(drawingManager) 
{
	acceleration_x = -3.0f + rand() % 60 * .1f;
	acceleration_y = -3.0f + rand() % 60 * .1f;
	if (-1.0f <= acceleration_x && acceleration_x <= 1.0f) acceleration_x = 1.0f;
	if (-1.0f <= acceleration_y && acceleration_y <= 1.0f) acceleration_y = 1.0f;
	velocity_x = 0.0f;
	velocity_y = 0.0f;
	x = -0.5f + rand() % 10 * .1f;
	y = -0.5f + rand() % 10 * .1f;
	width = .2f + rand() % 3 * .1f;
	height = .2f + rand() % 3 * .1f;
	scale_x = 1.0f;
	scale_y = 1.0f;
	rotation = 0.0f;
	friction_x = 5.0f;
	friction_y = 5.0f;
	isPlayer = false;
}

void Entity::Update(float elapsed)
{
	resetCollisionBools();
}

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
	if (!isPlayer) rotation += 15 * FIXED_TIMESTEP;
	//if (rotation >= 360.0f) rotation = 0.0f;

	velocity_x = lerp(velocity_x, 0.0f, FIXED_TIMESTEP * friction_x);
	velocity_y = lerp(velocity_y, 0.0f, FIXED_TIMESTEP * friction_y);

	velocity_x += acceleration_x * FIXED_TIMESTEP;
	velocity_y += acceleration_y * FIXED_TIMESTEP;
}
float Entity::lerp(float v0, float v1, float t)
{
	return (1.0f - t) * v0 + t * v1;
}

void Entity::movePlayer()
{
	x += velocity_x * FIXED_TIMESTEP;
	y += velocity_y * FIXED_TIMESTEP;
}

void Entity::moveX()
{
	x += velocity_x * FIXED_TIMESTEP;
	if (x - width > 2.66f)
	{
		x = -2.66f;
	}
	else if (x + width < -2.66f)
	{
		x = 2.66f;
	}
}

void Entity::moveY()
{
	y += velocity_y * FIXED_TIMESTEP;
	if (y - height > 2.00f)
	{
		y = -2.00f;
	}
	else if (y + height < -2.00f)
	{
		y = 2.00f;
	}
}

void Entity::buildMatrix() {
	Matrix scale;
	Matrix rotate;
	Matrix translate;

	scale.m[0][0] = scale_x;
	scale.m[1][1] = scale_y;
	scale.m[2][2] = 0.0f;

	rotate.m[0][0] = cos(rotation * PI / 180.0f);
	rotate.m[1][0] = -sin(rotation * PI / 180.0f);
	rotate.m[0][1] = sin(rotation * PI / 180.0f);
	rotate.m[1][1] = cos(rotation * PI / 180.0f);

	translate.m[3][0] = x;
	translate.m[3][1] = y;
	translate.m[3][2] = 0.0f;

	matrix = scale * rotate * translate;
}

void Entity::renderMeteor()
{
	buildMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glMultMatrixf(matrix.ml);

	drawingMgr->DrawQuad(width, height, 1.0f, 0.0f, 0.0f);

	glPopMatrix();
}

void Entity::renderShip()
{
	buildMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glMultMatrixf(matrix.ml);

	drawingMgr->DrawQuad(width, height, 1.0f, 1.0f, 1.0f);

	glPopMatrix();
}

void Entity::resetCollisionBools()
{
	collidedBottom = false;
	collidedTop = false;
	collidedRight = false;
	collidedLeft = false;
}

