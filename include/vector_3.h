/**
 * @file   vector_3.h
 * @brief  vector_3 header file
 *
 * @author Mario Galán Sobrino (galanso@esat-alumni.com)
 * @date   November 2021
 */

#ifndef __VECTOR3_H__
#define __VECTOR3_H__ 1

#include "math_utils.h"

#include <math.h>

class Vector3 {

public:
	Vector3();
	Vector3(float value);
	Vector3(float x, float y, float z);
	Vector3(float* values_array);
	Vector3(const Vector3& other);
	~Vector3();

	Vector3 operator+(const Vector3& other) const;
	Vector3 operator+(float value) const;
	Vector3& operator+=(const Vector3& other);
	Vector3& operator+=(float value);
	Vector3 operator-(const Vector3& other) const;
	Vector3 operator-(float value) const;
	Vector3& operator-=(const Vector3& other);
	Vector3& operator-=(float value);
	bool operator==(const Vector3& other) const;
	bool operator!=(const Vector3& other) const;
	void operator=(const Vector3& other);
	void operator=(float value);
	Vector3 operator*(float value) const;
	Vector3& operator*=(float value);
	Vector3 operator/(float value) const;
	Vector3& operator/=(float value);

	float Magnitude() const;
	Vector3 Normalized() const;
	void Normalize();
	float SqrMagnitude() const;
	void Scale(const Vector3& other);

	static Vector3 Lerp(const Vector3& a, const Vector3& b, float t);
	static Vector3 LerpUnclamped(const Vector3& a, const Vector3& b, float t);
	static float DotProduct(const Vector3& a, const Vector3& b);
	static float Angle(const Vector3& a, const Vector3& b);
	static Vector3 CrossProduct(const Vector3& a,const Vector3& b);
	static float Distance(const Vector3& a, const Vector3& b);
	static Vector3 Reflect(const Vector3& direction, const Vector3& normal);

	static const Vector3 up;
	static const Vector3 down;
	static const Vector3 right;
	static const Vector3 left;
	static const Vector3 forward;
	static const Vector3 back;
	static const Vector3 zero;
	static const Vector3 unit;

	float x;
	float y;
	float z;
};
inline Vector3::Vector3() {
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

inline Vector3::Vector3(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

inline Vector3::Vector3(float* values_array) {
	this->x = values_array[0];
	this->y = values_array[1];
	this->z = values_array[2];
}

inline Vector3::Vector3(float value) {
	this->x = value;
	this->y = value;
	this->z = value;
}

inline Vector3::Vector3(const Vector3& other) {
	x = other.x;
	y = other.y;
	z = other.z;
}

inline Vector3::~Vector3() {}

inline float Vector3::Magnitude() const {
	return sqrtf((x * x) + (y * y) + (z * z));
}

inline void Vector3::Normalize() {
	float inverseMagnitude = 1.0f / Magnitude();
	*this *= inverseMagnitude;
}

inline Vector3 Vector3::Normalized() const {
	Vector3 tmp(*this);

	tmp.Normalize();

	return tmp;
}

inline float Vector3::DotProduct(const Vector3& a, const Vector3& other)  {
	return ((a.x * other.x) + (a.y * other.y) + (a.z * other.z));
}

inline float Vector3::Angle(const Vector3& a, const Vector3& other)  {

	float tmp = acosf(DotProduct(a, other)/(a.Magnitude() * other.Magnitude()));

	return tmp;
}

inline Vector3 Vector3::CrossProduct(const Vector3& a, const Vector3& other)  {
	return Vector3((a.y * other.z) - (a.z * other.y), (a.z * other.x) - (a.x * other.z), (a.x * other.y) - (a.y * other.x));
}

inline float Vector3::SqrMagnitude() const {
	Vector3 tmp1 = Vector3(x, y, z);

 	return tmp1.Magnitude() * tmp1.Magnitude();
}

inline void Vector3::Scale(const Vector3& other) {
	x *= other.x;
	y *= other.y;
	z *= other.z;
}

inline Vector3 Vector3::Lerp(const Vector3& a, const Vector3& b, float t) {

	if (t < 0.0f) t = 0.0f;
	if (t > 1.0f) t = 1.0f;

	return (a + ((b - a) * t));
}

inline Vector3 Vector3::LerpUnclamped(const Vector3& a, const Vector3& b, float t) {
	return (a + ((b - a) * t));
}

inline float Vector3::Distance(const Vector3& a, const Vector3& b) {
	return sqrtf(((a.x - b.x) * (a.x - b.x)) + ((a.y - b.y) * (a.y - b.y)) + ((a.z - b.z) * (a.z - b.z)));
}

inline Vector3 Vector3::Reflect(const Vector3& direction, const Vector3& normal) {
	float tmp = 2.0f * direction.DotProduct(direction, normal);
	return (direction - (normal * tmp));
}

inline Vector3 Vector3::operator+(const Vector3& other) const {
	return Vector3(x + other.x, y + other.y, z + other.z);
}

inline Vector3 Vector3::operator+(float value) const {
	return Vector3(x + value, y + value, z + value);
}

inline Vector3& Vector3::operator+=(const Vector3& other) {
	x += other.x;
	y += other.y;
	z += other.z;

	return *this;
}

inline Vector3& Vector3::operator+=(float value) {
	x += value;
	y += value;
	z += value;

	return *this;
}

inline Vector3 Vector3::operator-(const Vector3& other) const {
	return Vector3(x - other.x, y - other.y, z - other.z);
}

inline Vector3 Vector3::operator-(float value) const {
	return Vector3(x - value, y - value, z - value);
}

inline Vector3& Vector3::operator-=(const Vector3& other) {
	x -= other.x;
	y -= other.y;
	z -= other.z;

	return *this;
}

inline Vector3& Vector3::operator-=(float value) {
	this->x -= value;
	this->y -= value;
	this->z -= value;

  return *this;
}

inline bool Vector3::operator==(const Vector3& other) const {
	return (x == other.x && y == other.y && z == other.z);
}

inline bool Vector3::operator!=(const Vector3& other) const {
  return (x != other.x || y != other.y || z != other.z);
}

inline void Vector3::operator=(const Vector3& other) {
	x = other.x;
	y = other.y;
	z = other.z;
}

inline void Vector3::operator=(float value) {
	this->x = value;
	this->y = value;
	this->z = value;
}

inline Vector3 Vector3::operator*(float value) const {
	return Vector3(x * value, y * value, z * value);
}

inline Vector3& Vector3::operator*=(float value) {
	this->x *= value;
	this->y *= value;
	this->z *= value;

  	return *this;
}

inline Vector3 Vector3::operator/(float value) const {
	return Vector3(x / value, y / value, z / value);
}

inline Vector3& Vector3::operator/=(float value) {
	x /= value;
	y /= value;
	z /= value;

	return *this;
}

#endif
