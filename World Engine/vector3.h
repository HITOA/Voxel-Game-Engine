#pragma once
#include <cmath>

struct Vector3
{
public:
	float x;
	float y;
	float z;
	Vector3();
	Vector3(float x, float y, float z);
	static Vector3 Forward() { return Vector3(0, 0, 1); }
	static Vector3 Up() { return Vector3(0, 1, 0); }
	static Vector3 Cross(Vector3 a, Vector3 b);
	static float Distance(Vector3 a, Vector3 b);
	static float DistanceSquared(Vector3 a, Vector3 b);
	Vector3 operator+(Vector3 a);
	Vector3 operator-(Vector3 a);
	void Normalize();
};