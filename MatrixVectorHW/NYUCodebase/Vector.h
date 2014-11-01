#ifndef _VECTOR_H_
#define _VECTOR_H_
#include "Math.h"

class Vector
{
public:
	Vector();
	Vector(float x, float y, float z);
	float length();
	void normalize();
	float x;
	float y;
	float z;
};

#endif