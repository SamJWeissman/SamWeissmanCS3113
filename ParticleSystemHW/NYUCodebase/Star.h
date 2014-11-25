#ifndef _STAR_H_
#define _STAR_H_

class Star
{
public:
	float x;
	float y;
	float size;
	Star(float xPos, float yPos, float size);
	void update(float elapsed, int wave);
};

#endif