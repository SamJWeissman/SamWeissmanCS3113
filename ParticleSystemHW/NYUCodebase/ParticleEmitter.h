#ifndef _PARTICLEEMITTER_H_
#define _PARTICLEEMITTER_H_

#include "Vector.h"
#include "Particle.h"
#include <vector>
#include <SDL_opengl.h>

class ParticleEmitter {
public:
	//ParticleEmitter(unsigned int particleCount);
	ParticleEmitter();
	~ParticleEmitter();
	void Update(float elapsed);
	void Render();
	Vector position;
	Vector gravity;
	float x;
	float y;
	float alive;
	float maxLifetime;
	bool removeMe;
	std::vector<Particle> particles;
};

#endif