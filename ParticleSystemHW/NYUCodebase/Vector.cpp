#include "Vector.h"


Vector::Vector()
{
}
Vector::Vector(float x, float y, float z) : x(x), y(y), z(z)
{
}

float Vector::length()
{
	float length = sqrt((x * x) + (y * y) + ( z * z));
	return length;
}

void Vector::normalize()
{
	float length = this->length();
	x = x / length;
	y = y / length;
	z = z / length;
}