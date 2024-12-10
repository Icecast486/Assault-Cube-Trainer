#pragma once

#include <iostream>
#include <sstream>


/* Header protector */
#ifndef VECTORS_H
#define VECTORS_H

struct Vector3
{
	float x, y, z;

	Vector3() : x{ 0.0f }, y{ 0.0f }, z{ 0.0f } { }

	Vector3(float x, float y, float z) : x{ x }, y{ y }, z{ z } { }


	Vector3 operator+(Vector3& other) const
	{
		Vector3 result;

		result.x = x + other.x;
		result.y = y + other.y;
		result.z = z + other.z;

		return result;
	}


	Vector3 operator-(const Vector3& other) const
	{
		Vector3 result;

		result.x = x - other.x;
		result.y = y - other.y;
		result.z = z - other.z;

		return result;
	}	
	

	Vector3 operator*(const Vector3& other) const
	{
		Vector3 result;

		result.x = x * other.x;
		result.y = y * other.y;
		result.z = z * other.z;

		return result;
	}


	Vector3 operator/(const Vector3& other) const
	{
		Vector3 result;

		/* Dividing by zero */
		if (other.x == 0 || other.y == 0 || other.z == 0)
		{
			throw std::invalid_argument("Division by zero in Vector3.");
		}

		result.x = x / other.x;
		result.y = y / other.y;
		result.z = z / other.z;

		return result;
	}


	bool operator==(const Vector3& other) const
	{
		return x == other.x && y == other.y && z == other.z;
	}	


	bool operator!=(const Vector3& other) const
	{
		return !(*this == other);
	}


	void operator+=(const Vector3& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
	}


	void operator-=(const Vector3& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
	}


	void operator*=(const Vector3& other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
	}


	void operator/=(const Vector3& other)
	{
		/* Dividing by zero */
		if (other.x == 0 || other.y == 0 || other.z == 0)
		{
			throw std::invalid_argument("Division by zero in Vector3.");
		}

		x /= other.x;
		y /= other.y;
		z /= other.z;
	}


	double get3DDistance(const Vector3& other) 
	{
		double distance = sqrt(
			(other.x - x) * (other.x - x) + (other.y - y) * (other.y - y) + (other.z - z) * (other.z - z));

		return distance;
	}


	friend std::ostream& operator<<(std::ostream& stream, Vector3& print)
	{
		stream << "(" << print.x << ", " << print.y << ", " << print.z << ")";
		return stream;
	}
};


struct Vector4
{
	float x, y, z, w;
};

struct ViewAngles
{
public:
	float yaw, pitch, roll;

	ViewAngles() : yaw{ 0.0f }, pitch{ 0.0f }, roll{ 0.0f } {}

	friend std::ostream& operator<<(std::ostream& stream, ViewAngles& print)
	{
		stream << "(" << print.pitch << ", " << print.yaw << ", " << print.roll << ")";
		return stream;
	}
};

#endif