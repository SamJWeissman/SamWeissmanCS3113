#include "Star.h"

Star::Star(float xPos, float yPos, float s) : x(xPos), y(yPos), size(s)
{

}

void Star::update(float elapsed, int wave)
{
	y -= elapsed * ( wave / 2.0f);
	if (y < -1.2f)
	{
		y = 1.2f;
	}
}