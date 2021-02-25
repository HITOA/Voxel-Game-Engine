#include "pch.h"
#include "vector3.h"

Vector3::Vector3() {
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

Vector3::Vector3(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3 Vector3::Cross(Vector3 a, Vector3 b)
{
	return Vector3(a.y * b.z - b.y * a.z,
		-(a.x * b.z - b.x * a.z),
		a.x * b.y - b.x * a.y);
}

float Vector3::Distance(Vector3 a, Vector3 b)
{
	return sqrt(DistanceSquared(a, b));
}

float Vector3::DistanceSquared(Vector3 a, Vector3 b)
{
	return (a.x - b.x) * (a.x - b.x) +
		   (a.y - b.y) * (a.y - b.y) +
		   (a.z - b.z) * (a.z - b.z);
}

Vector3 Vector3::operator+(Vector3 a)
{
	return Vector3(x + a.x, y + a.y, z + a.z);
}

Vector3 Vector3::operator-(Vector3 a)
{
	return Vector3(x - a.x, y - a.y, z - a.z);
}

void Vector3::Normalize()
{
	float factor = Distance(Vector3(x, y, z), Vector3(0, 0, 0));
	factor = 1.0f / factor;
	x = x * factor;
	y = y * factor;
	z = z * factor;
}
