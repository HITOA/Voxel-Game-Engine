#pragma once
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
};