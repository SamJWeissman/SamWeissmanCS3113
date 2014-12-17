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
	glPointSize(rand() % 5);
	std::vector<float> particleVertices;
	std::vector<float> colorVertices;
	for (int i = 0; i < particles.size(); i++) 
	{
		particleVertices.push_back(particles[i].x);
		particleVertices.push_back(particles[i].y);
	}
	for (int i = 0; i < particles.size(); i++)
	{
		colorVertices.push_back(1.0f);
		colorVertices.push_back(rand() % 11 * .1f);
		colorVertices.push_back(0.0f);
		colorVertices.push_back(1.0f);
	}
	glVertexPointer(2, GL_FLOAT, 0, particleVertices.data());
	glEnableClientState(GL_VERTEX_ARRAY);
	glColorPointer(4, GL_FLOAT, 0, colorVertices.data());
	glEnableClientState(GL_COLOR_ARRAY);
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