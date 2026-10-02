#pragma once

#ifndef MATH_H
#define MATH_H

#include <iostream>
#include <ostream>

#define PI 3.14154

struct Vector3
{
	float x, y, z;

	Vector3() : x{ 0.0f }, y{ 0.0f }, z{ 0.0f } {}

	Vector3(float x, float y, float z) : x{ x }, y{ y }, z{ z } {}


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

    Vector4() : x{ 0.0f }, y{ 0.0f }, z{ 0.0f }, w{ 0.0f } {}

    Vector4(float x, float y, float z, float w) : x{ x }, y{ y }, z{ z }, w{ w } {}


    Vector4 operator+(const Vector4& other) const
    {
        Vector4 result;

        result.x = x + other.x;
        result.y = y + other.y;
        result.z = z + other.z;
        result.w = w + other.w;

        return result;
    }


    Vector4 operator-(const Vector4& other) const
    {
        Vector4 result;

        result.x = x - other.x;
        result.y = y - other.y;
        result.z = z - other.z;
        result.w = w - other.w;

        return result;
    }


    Vector4 operator*(const Vector4& other) const
    {
        Vector4 result;

        result.x = x * other.x;
        result.y = y * other.y;
        result.z = z * other.z;
        result.w = w * other.w;

        return result;
    }


    Vector4 operator/(const Vector4& other) const
    {
        Vector4 result;

        if (other.x == 0 || other.y == 0 || other.z == 0 || other.w == 0)
        {
            throw std::invalid_argument("Division by zero in Vector4.");
        }

        result.x = x / other.x;
        result.y = y / other.y;
        result.z = z / other.z;
        result.w = w / other.w;

        return result;
    }


    bool operator==(const Vector4& other) const
    {
        return x == other.x && y == other.y && z == other.z && w == other.w;
    }


    bool operator!=(const Vector4& other) const
    {
        return !(*this == other);
    }


    void operator+=(const Vector4& other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        w += other.w;
    }


    void operator-=(const Vector4& other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        w -= other.w;
    }


    void operator*=(const Vector4& other)
    {
        x *= other.x;
        y *= other.y;
        z *= other.z;
        w *= other.w;
    }


    void operator/=(const Vector4& other)
    {
        if (other.x == 0 || other.y == 0 || other.z == 0 || other.w == 0)
        {
            throw std::invalid_argument("Division by zero in Vector4.");
        }

        x /= other.x;
        y /= other.y;
        z /= other.z;
        w /= other.w;
    }


    double get4DDistance(const Vector4& other)
    {
        return sqrt(
            (other.x - x) * (other.x - x) +
            (other.y - y) * (other.y - y) +
            (other.z - z) * (other.z - z) +
            (other.w - w) * (other.w - w));
    }


    friend std::ostream& operator<<(std::ostream& stream, Vector4& print)
    {
        stream << "(" << print.x << ", " << print.y << ", " << print.z << ", " << print.w << ")";
        return stream;
    }
};



struct ViewAngles
{
    float yaw, pitch, roll;

    ViewAngles() : yaw(0.f), pitch(0.f), roll(0.f) {}
    ViewAngles(float p, float y, float r = 0.f) : yaw(y), pitch(p), roll(r) {}

    ViewAngles operator+(const ViewAngles& o) const { return { pitch + o.pitch, yaw + o.yaw, roll + o.roll }; }
    ViewAngles operator-(const ViewAngles& o) const { return { pitch - o.pitch, yaw - o.yaw, roll - o.roll }; }
    ViewAngles operator+(float c) const { return { pitch + c, yaw + c, roll }; }
    ViewAngles operator/(float s) const { return { pitch / s, yaw / s, roll / s }; }
    ViewAngles operator*(float s) const { return { pitch * s, yaw * s, roll * s }; }

    friend std::ostream& operator<<(std::ostream& stream, const ViewAngles& v)
    {
        return stream << "(" << v.pitch << ", " << v.yaw << ", " << v.roll << ")";
    }
};



static bool world_to_screen(Vector3 pos, Vector3& screen, float* matrix, int window_width, int window_height)
{
	Vector4 clip_coords;

	clip_coords.x = pos.x * matrix[0] + pos.y * matrix[4] + pos.z * matrix[8] + matrix[12];
	clip_coords.y = pos.x * matrix[1] + pos.y * matrix[5] + pos.z * matrix[9] + matrix[13];
	clip_coords.z = pos.x * matrix[2] + pos.y * matrix[6] + pos.z * matrix[10] + matrix[14];
	clip_coords.w = pos.x * matrix[3] + pos.y * matrix[7] + pos.z * matrix[11] + matrix[15];

	if (clip_coords.w < 0.1f)
		return false;

	Vector3 NDC;
	NDC.x = clip_coords.x / clip_coords.w;
	NDC.y = clip_coords.y / clip_coords.w;
	NDC.z = clip_coords.z / clip_coords.w;

	screen.x = (window_width / 2 * NDC.x) + (NDC.x + window_width / 2);
	screen.y = -(window_height / 2 * NDC.y) + (NDC.y + window_height / 2);

	return true;
}





#endif