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
	//vector.x = x;
	//vector.y = y;
	//vector.z = 0.0f;
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
	//velocity_x += GRAVITY_X * elapsed;
	//velocity_y += GRAVITY_Y * elapsed;
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
	if (!isPlayer) rotation += FIXED_TIMESTEP;
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

void Entity::moveY()
{
	y += cos(rotation * PI / 180.0f ) * velocity_y * FIXED_TIMESTEP;

	if (y - height > 2.0f)
	{
		y = -2.0f;
	}
	if (y + height < -2.0f)
	{
		y = 2.0f;
	}
}

void Entity::moveX()
{
	x += sin(rotation * PI / 180.0f) * velocity_y * FIXED_TIMESTEP;

	if (x - width > 2.66f)
	{
		x = -2.66f;
	}
	if (x + width < -2.66f)
	{
		x = 2.66f;
	}
}

void Entity::movePlayer()
{
	//Vector v;
	velocity.x += sin(rotation * PI / 180.0f) * velocity_y * FIXED_TIMESTEP;
	velocity.y += cos(rotation * PI / 180.0f) * velocity_y * FIXED_TIMESTEP;
	//velocity.x = velocity_x;
	//velocity.y = velocity_y;
	//v.z = 0.0f;

//	v = matrix * v;
	//x += v.x;
	//y += v.y;
}

void Entity::buildMatrix()
{
	matrix.identity();
	
	Matrix tmp;

	tmp.m[0][0] = scale_x;
	tmp.m[0][1] = 0;
	tmp.m[0][2] = 0;
	tmp.m[0][3] = 0;

	tmp.m[1][0] = 0;
	tmp.m[1][1] = scale_y;
	tmp.m[1][2] = 0;
	tmp.m[1][3] = 0;

	tmp.m[2][0] = 0;
	tmp.m[2][1] = 0;
	tmp.m[2][2] = 0; //scale_z
	tmp.m[2][3] = 0;

	tmp.m[3][0] = 0;
	tmp.m[3][1] = 0;
	tmp.m[3][2] = 0;
	tmp.m[3][3] = 1;

	matrix = matrix * tmp;

	tmp.m[0][0] = cos(rotation);
	tmp.m[0][1] = sin(rotation);
	tmp.m[0][2] = 0;
	tmp.m[0][3] = 0;

	tmp.m[1][0] = -sin(rotation);
	tmp.m[1][1] = cos(rotation);
	tmp.m[1][2] = 0;
	tmp.m[1][3] = 0;

	tmp.m[2][0] = 0;
	tmp.m[2][1] = 0;
	tmp.m[2][2] = 1;
	tmp.m[2][3] = 0;

	tmp.m[3][0] = 0;
	tmp.m[3][1] = 0;
	tmp.m[3][2] = 0;
	tmp.m[3][3] = 1;

	matrix = matrix * tmp;

	tmp.m[0][0] = 1;
	tmp.m[0][1] = 0;
	tmp.m[0][2] = 0;
	tmp.m[0][3] = 0;

	tmp.m[1][0] = 0;
	tmp.m[1][1] = 1;
	tmp.m[1][2] = 0;
	tmp.m[1][3] = 0;

	tmp.m[2][0] = 0;
	tmp.m[2][1] = 0;
	tmp.m[2][2] = 1;
	tmp.m[2][3] = 0;

	tmp.m[3][0] = velocity.x;
	tmp.m[3][1] = velocity.y;
	tmp.m[3][2] = 0;
	tmp.m[3][3] = 1;

	matrix = matrix * tmp;
}

void Entity::renderMeteor()
{
	buildMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glMultMatrixf(matrix.ml);

	drawingMgr->DrawQuad(width, height);

	glPopMatrix();
}

void Entity::renderShip()
{
	buildMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glMultMatrixf(matrix.ml);

	drawingMgr->DrawTriangle(width, height);

	glPopMatrix();
}

void Entity::resetCollisionBools()
{
	collidedBottom = false;
	collidedTop = false;
	collidedRight = false;
	collidedLeft = false;
}

