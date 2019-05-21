#pragma once
#include <math.h>

inline float toRadians(float degree)
{
	return (float)(degree * (M_PI / 180.0f));
}
struct vec2
{
public:
	float x, y;

	vec2() = default;
	vec2(const float& x, const float& y)
	{
		this->x = x;
		this->y = y;
	}

	friend vec2& operator+(vec2& left, const vec2& right)
	{
		return left.add(right);
	}
	friend vec2& operator-(vec2& left, const vec2& right)
	{
		return left.subtract(right);
	}
	friend vec2& operator/(vec2& left, const vec2& right)
	{
		return left.divide(right);
	}
	friend vec2& operator*(vec2& left, const vec2& right)
	{
		return left.multiply(right);
	}

private:

	vec2& add(const vec2& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}
	vec2& subtract(const vec2& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}
	vec2& divide(const vec2& other)
	{
		x /= other.x;
		y /= other.y;
		return *this;
	}
	vec2& multiply(const vec2& other)
	{
		x *= other.x;
		y *= other.y;
		return *this;
	}

};
struct vec3
{
public:
	float x, y, z;

	vec3() = default;
	vec3(const float& x, const float& y, const float& z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	friend vec3& operator+(vec3& left, const vec3& right) { return left.add(right); }
	friend vec3& operator-(vec3& left, const vec3& right) {
		return left.subtract(right);
	}
	friend vec3& operator/(vec3& left, const vec3& right) {
		return left.divide(right);
	}
	friend vec3& operator*(vec3& left, const vec3& right) {
		return left.multiply(right);
	}


private:

	vec3& add(const vec3& other) {
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}
	vec3& subtract(const vec3& other) {
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}
	vec3& divide(const vec3& other) {
		x /= other.x;
		y /= other.y;
		z /= other.z;
		return *this;
	}
	vec3& multiply(const vec3& other) {
		x *= other.x;
		y *= other.y;
		z *= other.z;
		return *this;
	}

};
struct vec4
{
public:
	float x, y, z, a;

	vec4() = default;
	vec4(const float& x, const float& y, const float& z, const float& a)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->a = a;
	}

	friend vec4& operator+(vec4& left, const vec4& right) {
		return left.add(right);
	}
	friend vec4& operator-(vec4& left, const vec4& right) {
		return left.subtract(right);
	}
	friend vec4& operator/(vec4& left, const vec4& right) {
		return left.divide(right);
	}
	friend vec4& operator*(vec4& left, const vec4& right) {
		return left.multiply(right);
	}

private:

	vec4& add(const vec4& other) {
		x += other.x;
		y += other.y;
		z += other.z;
		a += other.a;
		return *this;
	}
	vec4& subtract(const vec4& other) {
		x -= other.x;
		y -= other.y;
		z -= other.z;
		a -= other.a;
		return *this;
	}
	vec4& divide(const vec4& other) {
		x /= other.x;
		y /= other.y;
		z /= other.z;
		a /= other.a;
		return *this;
	}
	vec4& multiply(const vec4& other) {
		x *= other.x;
		y *= other.y;
		z *= other.z;
		a *= other.a;
		return *this;
	}

};
struct mat4
{
public:
	union
	{
		float elements[4 * 4];
		vec4 colums[4];
	};


	mat4()
	{
		for (int i = 0; i < 4 * 4; i++)
			elements[i] = 0.0f;
	}
	mat4(float diagonal)
	{
		for (int i = 0; i < 4 * 4; i++)
			elements[i] = 0.0f;

		elements[0 + 0 * 4] = diagonal;
		elements[1 + 1 * 4] = diagonal;
		elements[2 + 2 * 4] = diagonal;
		elements[3 + 3 * 4] = diagonal;
	}

	static mat4 identity()
	{
		return mat4(1.0f);
	}

	static mat4 orthographic(float left, float right, float bot, float top, float Near, float Far)
	{
		mat4 result(1.0f);

		result.elements[0 + 0 * 4] = 2.0f / (right - left);

		result.elements[1 + 1 * 4] = 2.0f / (top - bot);

		result.elements[2 + 2 * 4] = 2.0f / (Near - Far);


		result.elements[0 + 3 * 4] = (left + right) / (left - right);

		result.elements[1 + 3 * 4] = (bot + top) / (bot - top);

		result.elements[2 + 3 * 4] = (Far + Near) / (Far - Near);

		return result;
	}
	static mat4 perspective(float fov, float aspectRatio, float Near, float Far)
	{
		mat4 result(1.0f);

		float q = 1.0f / (float)tan(toRadians(0.5f * fov));
		float a = q / aspectRatio;

		float b = (Near + Far) / (Near - Far);
		float c = (2.0f * Near * Far) / (Near - Far);

		result.elements[0 + 0 * 4] = a;
		result.elements[1 + 1 * 4] = q;
		result.elements[2 + 2 * 4] = -b;
		result.elements[3 + 2 * 4] = 1.0f;
		result.elements[2 + 3 * 4] = c;

		return result;
	}

	static mat4 translation(const vec4 & translation)
	{
		mat4 result(1.0f);

		result.elements[0 + 3 * 4] = translation.x;
		result.elements[1 + 3 * 4] = translation.y;
		result.elements[2 + 3 * 4] = translation.z;

		return result;
	}
	static mat4 rotation(float angle, const vec3 & axis)
	{
		mat4 result(1.0f);

		float r = toRadians(angle);
		float c = (float)cos(r);
		float s = (float)sin(r);
		float mc = 1.0f - c;

		float x = axis.x;
		float y = axis.y;
		float z = axis.z;

		result.elements[0 + 0 * 4] = x * mc + c;
		result.elements[1 + 0 * 4] = y * x * mc + z * s;
		result.elements[2 + 0 * 4] = x * z * mc - y * s;

		result.elements[0 + 1 * 4] = x * y * mc - z * s;
		result.elements[1 + 1 * 4] = y * mc + c;
		result.elements[2 + 1 * 4] = y * z * mc + x * s;


		result.elements[0 + 2 * 4] = x * z * mc + y * s;
		result.elements[1 + 2 * 4] = y * z * mc - x * s;
		result.elements[2 + 2 * 4] = z * mc + c;

		return result;
	}
	static mat4 scale(const vec3 & scale)
	{
		mat4 result(1.0f);

		result.elements[0 + 0 * 4] = scale.x;
		result.elements[1 + 1 * 4] = scale.y;
		result.elements[2 + 2 * 4] = scale.z;

		return result;
	}

	friend mat4& operator*(mat4 left, const mat4 & right)
	{
		return left.multiply(right);
	}

private:
	mat4& multiply(const mat4 & other)
	{
		for (int y = 0; y < 4; y++)
		{
			for (int x = 0; x < 4; x++)
			{
				float sum = 0.0f;
				for (int e = 0; e < 4; e++)
				{
					sum += elements[x + e * 4] * other.elements[e + y * 4];
				}
				elements[x + y * 4] = sum;
			}
		}
		return *this;
	}

};