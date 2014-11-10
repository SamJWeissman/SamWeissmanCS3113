#ifndef _PARTICLE_H_
#define _PARTICLE_H_

class Particle {
public:
	//Vector position;
	//Vector velocity;
	float velocity_x;
	float velocity_y;
	float x;
	float y;
	float angle;
	float lifetime;
	void Update();
};

#endif