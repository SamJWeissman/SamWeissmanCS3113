#include "Particle.h"

void Particle::Update()
{
	x += velocity_x;
	y += velocity_y;
}
