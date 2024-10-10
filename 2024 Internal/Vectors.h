#pragma once

/* Header protector */
#ifndef VECTORS_H
#define VECTORS_H

struct Vector3
{
	float x, y, z;

	Vector3() : x{ 0.0f }, y{ 0.0f }, z{ 0.0f } { }

	Vector3(float x, float y, float z) : x{ x }, y{ y }, z{ z } { }

	Vector3 operator+(Vector3& other)
	{
		Vector3 result;

		result.x = x + other.x;
		result.y = y + other.y;
		result.z = z + other.z;

		return result;
	}

	Vector3 operator-(Vector3& other)
	{
		Vector3 result;

		result.x = x - other.x;
		result.y = y - other.y;
		result.z = z - other.z;

		return result;
	}	
	
	Vector3 operator*(Vector3& other)
	{
		Vector3 result;

		result.x = x * other.x;
		result.y = y * other.y;
		result.z = z * other.z;

		return result;
	}

	Vector3 operator/(Vector3& other)
	{
		Vector3 result;

		/* Dividing by zero */
		if (other.x == 0 || other.y == 0 || other.z == 0)
		{
			return Vector3(0, 0, 0);
		}

		result.x = x / other.x;
		result.y = y / other.y;
		result.z = z / other.z;

		return result;
	}

	bool operator==(Vector3& other)
	{
		return x == other.x && y == other.y && z == other.z;
	}	

	bool operator==(Vector3& other)
	{
		return !(*this == other);
	}

	void operator+=(Vector3& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
	}

	void operator-=(Vector3& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
	}

	void operator*=(Vector3& other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
	}

	void operator/=(Vector3& other)
	{
		/* Dividing by zero */
		if (other.x == 0 || other.y == 0 || other.z == 0)
		{
			x = 0;
			y = 0;
			z = 0;
		}

		x /= other.x;
		y /= other.y;
		z /= other.z;
	}
};

#endif