#include "ParticleEmitter.h"

ParticleEmitter::ParticleEmitter()
{

}

ParticleEmitter::~ParticleEmitter()
{

}

void ParticleEmitter::Render()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPointSize(rand() % 4);
	std::vector<float> particleVertices;
	for (int i = 0; i < particles.size(); i++) 
	{
		particleVertices.push_back(particles[i].x);
		particleVertices.push_back(particles[i].y);
	}
	glVertexPointer(2, GL_FLOAT, 0, particleVertices.data());
	glEnableClientState(GL_VERTEX_ARRAY);
	glDrawArrays(GL_POINTS, 0, particleVertices.size() / 2);
	glDisable(GL_VERTEX_ARRAY);
	glDisable(GL_COLOR_ARRAY);

}

void ParticleEmitter::Update(float elapsed)
{
	alive += elapsed;
	if (alive < maxLifetime)
	for (int i = 0; i < particles.size(); i++)
	{
		particles[i].Update();
	}
	else
	{
		removeMe = true;
	}
}