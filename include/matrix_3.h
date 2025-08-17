/**
 * @file   matrix_3.h
 * @brief  matrix_3 header file
 *
 * @author Mario Galán Sobrino (galanso@esat-alumni.com)
 * @date   November 2021
 */

#ifndef __MATRIX3_H__
#define __MATRIX3_H__ 1

#include "vector_2.h"
#include "vector_3.h"

#include <assert.h>

class Matrix3x3 {
public:

	Matrix3x3();
	Matrix3x3(float *values_array);
	Matrix3x3(float value);
	Matrix3x3(Vector3 a, Vector3 b, Vector3 c);

	Matrix3x3(float f1, float f2, float f3,
			  float f4, float f5, float f6,
			  float f7, float f8, float f9);

	Matrix3x3(const Matrix3x3& copy);
	~Matrix3x3();

	static Matrix3x3 Identity();

	Matrix3x3 Multiply(const Matrix3x3& other) const;

	float Determinant() const;

	Matrix3x3 Adjoint() const;
	bool GetInverse(Matrix3x3& out) const;
	bool Inverse();

	Matrix3x3 Transpose() const;

	static Matrix3x3 Translate(const Vector2& position);
	static Matrix3x3 Translate(float x, float y);

	static Matrix3x3 Rotate(float radians);

	static Matrix3x3 Scale(const Vector2& scale);
	static Matrix3x3 Scale(float x, float y);

	Vector3 Mat3TransformVec3(const Vector3& v);
  	Vector2 Mat3TransformVec2(const Vector2& v);

	Vector3 GetColum(int colum) const;
	Vector3 GetLine(int line) const;

	inline Matrix3x3 operator+(const Matrix3x3& other) const;
	inline Matrix3x3& operator+=(const Matrix3x3& other);
	inline Matrix3x3 operator+(float value) const;
	inline Matrix3x3& operator+=(float value);
	inline Matrix3x3 operator-(const Matrix3x3& other) const;
	inline Matrix3x3& operator-=(const Matrix3x3& other);
	inline Matrix3x3 operator-(float value) const;
	inline Matrix3x3& operator-=(float value);
	inline Matrix3x3 operator*(float value) const;
	inline Matrix3x3& operator*=(float value);
	inline Matrix3x3 operator/(float value) const;
	inline Matrix3x3& operator/=(float value);
	bool operator==(const Matrix3x3& other) const;
	bool operator!=(const Matrix3x3& other) const;
	inline void operator=(const Matrix3x3& other);

	float m[9];
};


inline Matrix3x3::Matrix3x3() {
	m[0] = 0.0f; m[3] = 0.0f; m[6] = 0.0f;
	m[1] = 0.0f; m[4] = 0.0f; m[7] = 0.0f;
	m[2] = 0.0f; m[5] = 0.0f; m[8] = 0.0f;
}

inline Matrix3x3::Matrix3x3(float value) {
	this->m[0] = value; this->m[3] = value; this->m[6] = value;
	this->m[1] = value; this->m[4] = value; this->m[7] = value;
	this->m[2] = value; this->m[5] = value; this->m[8] = value;
}

inline Matrix3x3::Matrix3x3(float *values_array) {
	this->m[0] = values_array[0]; this->m[3] = values_array[3]; this->m[6] = values_array[6];
	this->m[1] = values_array[1]; this->m[4] = values_array[4]; this->m[7] = values_array[7];
	this->m[2] = values_array[2]; this->m[5] = values_array[5]; this->m[8] = values_array[8];
}

inline Matrix3x3::Matrix3x3(Vector3 a, Vector3 b, Vector3 c) {
	this->m[0] = a.x; this->m[3] = b.x; this->m[6] = c.x;
	this->m[1] = a.y; this->m[4] = b.y; this->m[7] = c.y;
	this->m[2] = a.z; this->m[5] = b.z; this->m[8] = c.z;
}

inline Matrix3x3::Matrix3x3(float f1, float f2, float f3,
			  				float f4, float f5, float f6,
			  				float f7, float f8, float f9) {
	this->m[0] = f1; this->m[3] = f4; this->m[6] = f7;
	this->m[1] = f2; this->m[4] = f5; this->m[7] = f8;
	this->m[2] = f3; this->m[5] = f6; this->m[8] = f9;
}

inline Matrix3x3::Matrix3x3(const Matrix3x3& copy) {
	this->m[0] = copy.m[0]; this->m[3] = copy.m[3]; this->m[6] = copy.m[6];
	this->m[1] = copy.m[1]; this->m[4] = copy.m[4]; this->m[7] = copy.m[7];
	this->m[2] = copy.m[2]; this->m[5] = copy.m[5]; this->m[8] = copy.m[8];
}

inline Matrix3x3::~Matrix3x3() {
}

inline Matrix3x3 Matrix3x3::operator+(const Matrix3x3& other) const {
	return Matrix3x3(
		m[0] + other.m[0], m[3] + other.m[3], m[6] + other.m[6],
		m[1] + other.m[1], m[4] + other.m[4], m[7] + other.m[7],
		m[2] + other.m[2], m[5] + other.m[5], m[8] + other.m[8]
	);
}

inline Matrix3x3& Matrix3x3::operator+=(const Matrix3x3& other) {
	m[0] += other.m[0]; m[3] += other.m[3]; m[6] += other.m[6];
	m[1] += other.m[1]; m[4] += other.m[4]; m[7] += other.m[7];
	m[2] += other.m[2]; m[5] += other.m[5]; m[8] += other.m[8];

	return *this;
}

inline Matrix3x3 Matrix3x3::operator+(float value) const {
	return Matrix3x3(
		m[0] + value, m[3] + value, m[6] + value,
		m[1] + value, m[4] + value, m[7] + value,
		m[2] + value, m[5] + value, m[8] + value
	);
}

inline Matrix3x3& Matrix3x3::operator+=(float value) {
	m[0] += value; m[3] += value; m[6] += value;
	m[1] += value; m[4] += value; m[7] += value;
	m[2] += value; m[5] += value; m[8] += value;

	return *this;
}

inline Matrix3x3 Matrix3x3::operator-(const Matrix3x3& other) const {
	return Matrix3x3(
		m[0] - other.m[0], m[3] - other.m[3], m[6] - other.m[6],
		m[1] - other.m[1], m[4] - other.m[4], m[7] - other.m[7],
		m[2] - other.m[2], m[5] - other.m[5], m[8] - other.m[8]
	);
}

inline Matrix3x3& Matrix3x3::operator-=(const Matrix3x3& other) {
	m[0] -= other.m[0]; m[3] -= other.m[3]; m[6] -= other.m[6];
	m[1] -= other.m[1]; m[4] -= other.m[4]; m[7] -= other.m[7];
	m[2] -= other.m[2]; m[5] -= other.m[5]; m[8] -= other.m[8];

	return *this;
}

inline Matrix3x3 Matrix3x3::operator-(float value) const {
	return Matrix3x3(
		m[0] - value, m[3] - value, m[6] - value,
		m[1] - value, m[4] - value, m[7] - value,
		m[2] - value, m[5] - value, m[8] - value
	);
}

inline Matrix3x3& Matrix3x3::operator-=(float value) {
	m[0] -= value; m[3] -= value; m[6] -= value;
	m[1] -= value; m[4] -= value; m[7] -= value;
	m[2] -= value; m[5] -= value; m[8] -= value;

	return *this;
}

inline Matrix3x3 Matrix3x3::operator*(float value) const {
	return Matrix3x3(
		m[0] * value, m[3] * value, m[6] * value,
		m[1] * value, m[4] * value, m[7] * value,
		m[2] * value, m[5] * value, m[8] * value
	);
}

inline Matrix3x3& Matrix3x3::operator*=(float value) {
	m[0] *= value; m[3] *= value; m[6] *= value;
	m[1] *= value; m[4] *= value; m[7] *= value;
	m[2] *= value; m[5] *= value; m[8] *= value;

	return *this;
}

inline Matrix3x3 Matrix3x3::operator/(float value) const {
	return Matrix3x3(
		m[0] / value, m[3] / value, m[6] / value,
		m[1] / value, m[4] / value, m[7] / value,
		m[2] / value, m[5] / value, m[8] / value
	);
}

inline Matrix3x3& Matrix3x3::operator/=(float value) {
	m[0] /= value; m[3] /= value; m[6] /= value;
	m[1] /= value; m[4] /= value; m[7] /= value;
	m[2] /= value; m[5] /= value; m[8] /= value;

	return *this;
}

inline bool Matrix3x3::operator==(const Matrix3x3& other) const {
	return (m[0] == other.m[0] && m[3] == other.m[3] && m[6] == other.m[6] &&
			m[1] == other.m[1] && m[4] == other.m[4] && m[7] == other.m[7] &&
			m[2] == other.m[2] && m[5] == other.m[5] && m[8] == other.m[8]);

}

inline bool Matrix3x3::operator!=(const Matrix3x3& other) const {
	return (m[0] != other.m[0] || m[3] != other.m[3] || m[6] != other.m[6] ||
			m[1] != other.m[1] || m[4] != other.m[4] || m[7] != other.m[7] ||
			m[2] != other.m[2] || m[5] != other.m[5] || m[8] != other.m[8]);
}

inline void Matrix3x3::operator=(const Matrix3x3& other) {
	m[0] = other.m[0]; m[3] = other.m[3]; m[6] = other.m[6];
	m[1] = other.m[1]; m[4] = other.m[4]; m[7] = other.m[7];
	m[2] = other.m[2]; m[5] = other.m[5]; m[8] = other.m[8];
}

inline Matrix3x3 Matrix3x3::Identity(){
	Matrix3x3 tmp;
	tmp.m[0] = 1.0f; tmp.m[3] = 0.0f; tmp.m[6] = 0.0f;
	tmp.m[1] = 0.0f; tmp.m[4] = 1.0f; tmp.m[7] = 0.0f;
	tmp.m[2] = 0.0f; tmp.m[5] = 0.0f; tmp.m[8] = 1.0f;

	return tmp;
}

inline float Matrix3x3::Determinant() const {
	float tmp = ((m[0] * m[4] * m[8]) +
				(m[3] * m[7] * m[2]) +
				(m[1] * m[5] * m[6])) -
				((m[6] * m[4] * m[2]) +
				(m[3] * m[1] * m[8]) +
				(m[7] * m[5] * m[0]));

	return tmp;
}

inline bool Matrix3x3::GetInverse(Matrix3x3& out) const {
	if(Determinant() != 0.0f) {
		out = out.Adjoint() / out.Determinant();
		return true;
	}

	return false;
}

inline bool Matrix3x3::Inverse() {
	/*if(Determinant() != 0.0f) {
		*this = this->Adjoint() / Determinant();
		return true;
	}

	return false;*/

	return GetInverse(*this);
}

//--------------------------------------------------------------------------------------------------------

inline Matrix3x3 Matrix3x3::Translate(const Vector2& position) {
	Matrix3x3 tmp = tmp.Identity();

	tmp.m[2] = position.x;
	tmp.m[5] = position.y;

	return tmp;
}

inline Matrix3x3 Matrix3x3::Translate(float x, float y) {
	Matrix3x3 tmp = tmp.Identity();

	tmp.m[2] = x;
	tmp.m[5] = y;

	return tmp;
}

inline Matrix3x3 Matrix3x3::Rotate(float radians) {
	Matrix3x3 tmp = tmp.Identity();

	tmp.m[0] = cosf(radians);
	tmp.m[1] = sinf(radians);
	tmp.m[3] = -sinf(radians);
	tmp.m[4] = cosf(radians);

	return tmp;
}

inline Matrix3x3 Matrix3x3::Scale(const Vector2& scale) {
	Matrix3x3 tmp = tmp.Identity();

	tmp.m[0] = scale.x;
	tmp.m[4] = scale.y;

	return tmp;
}

inline Matrix3x3 Matrix3x3::Scale(float x, float y) {
	Matrix3x3 tmp = tmp.Identity();

	tmp.m[0] = x;
	tmp.m[4] = y;

	return tmp;
}

//--------------------------------------------------------------------------------------------------------

inline Matrix3x3 Matrix3x3::Multiply(const Matrix3x3& other) const {
	Matrix3x3 tmp = {this->m[0] * other.m[0] + this->m[1] * other.m[3] + this->m[2] * other.m[6],
                	 this->m[0] * other.m[1] + this->m[1] * other.m[4] + this->m[2] * other.m[7],
                	 this->m[0] * other.m[2] + this->m[1] * other.m[5] + this->m[2] * other.m[8],

	                 this->m[3] * other.m[0] + this->m[4] * other.m[3] + this->m[5] * other.m[6],
	                 this->m[3] * other.m[1] + this->m[4] * other.m[4] + this->m[5] * other.m[7],
	                 this->m[3] * other.m[2] + this->m[4] * other.m[5] + this->m[5] * other.m[8],

	                 this->m[6] * other.m[0] + this->m[7] * other.m[3] + this->m[8] * other.m[6],
	                 this->m[6] * other.m[1] + this->m[7] * other.m[4] + this->m[8] * other.m[7],
	                 this->m[6] * other.m[2] + this->m[7] * other.m[5] + this->m[8] * other.m[8]};

	tmp.m[6] = tmp.m[2];
	tmp.m[2] = 0.0f;
	tmp.m[7] = tmp.m[5];
	tmp.m[5] = 0.0f;

	return tmp;
}

inline Matrix3x3 Matrix3x3::Adjoint() const {
	Matrix3x3 tmp;

	tmp.m[0] = ((m[4] * m[8]) - (m[7] * m[5])); tmp.m[3] = -((m[1] * m[8]) - (m[7] * m[2])); tmp.m[6] = ((m[1] * m[5]) - (m[4] * m[2]));
	tmp.m[1] = -((m[3] * m[8]) - (m[6] * m[5])); tmp.m[4] = ((m[0] * m[8]) - (m[6] * m[2])); tmp.m[7] = -((m[0] * m[5]) - (m[3] * m[2]));
	tmp.m[2] = ((m[3] * m[7]) - (m[6] * m[4])); tmp.m[5] = -((m[0] * m[7]) - (m[6] * m[1])); tmp.m[8] = ((m[0] * m[4]) - (m[3] * m[1]));

	return tmp;
}

inline Matrix3x3 Matrix3x3::Transpose() const {
	Matrix3x3 tmp;

	tmp.m[0] = this->m[0]; tmp.m[3] = this->m[1]; tmp.m[6] = this->m[2];
	tmp.m[1] = this->m[3]; tmp.m[4] = this->m[4]; tmp.m[7] = this->m[5];
	tmp.m[2] = this->m[6]; tmp.m[5] = this->m[7]; tmp.m[8] = this->m[8];

	return tmp;
}

inline Vector3 Matrix3x3::GetColum(int colum) const {
	assert(colum >= 0 && colum <= 2 && "Column out of bounds");

	return Vector3(m[0 + (colum * 3)], m[1 + (colum * 3)], m[2 + (colum * 3)]);
}

inline Vector3 Matrix3x3::GetLine(int line) const {
	assert(line >= 0 && line <= 2 && "Line out of bounds");

	return Vector3(m[line], m[line + 3], m[line + 6]);
}

inline Vector3 Matrix3x3::Mat3TransformVec3(const Vector3& v) {
	Vector3 tmp;

	tmp.x = m[0] * v.x + m[3] * v.y + m[6] * v.z;
	tmp.y = m[1] * v.x + m[4] * v.y + m[7] * v.z;
	tmp.z = m[2] * v.x + m[5] * v.y + m[8] * v.z;

	return tmp;
}

inline Vector2 Matrix3x3::Mat3TransformVec2(const Vector2& v) {

	Vector3 tmp;

	tmp.x = v.x;
	tmp.y = v.y;
	tmp.z = 1.0f;

	Vector3 convert = Mat3TransformVec3(tmp);

	convert.x = convert.x / convert.z;
	convert.y = convert.y / convert.z;

	Vector2 result(convert.x, convert.y);

	return result;

	/*
	Vector2 tmp;

	tmp.x = m[0] * v.x + m[3] * v.y +	m[6] * 1.0f;
	tmp.y = m[1] * v.x + m[4] * v.y +	m[7] * 1.0f;

	return tmp;
	*/
}

#endif
