/**
 * @file   matrix_2.h
 * @brief  matrix_2 header file
 *
 * @author Mario Galán Sobrino (galanso@esat-alumni.com)
 * @date   November 2021
 */

#ifndef __MATRIX2_H__
#define __MATRIX2_H__ 1

#include "vector_2.h"

class Matrix2x2 {
public:

	Matrix2x2();
	Matrix2x2(float a[4]);
	Matrix2x2(float value);
	Matrix2x2(const Vector2& a, const Vector2& b);
	Matrix2x2(const Matrix2x2& copy);
	~Matrix2x2();
	Matrix2x2 Identity() const;
	Matrix2x2 Multiply(const Matrix2x2& other) const;
	float Determinant() const;
	Matrix2x2 Adjoint() const;
	Vector2 GetLine(int line) const;
	Vector2 GetColum(int line) const;

	Matrix2x2 Inverse() const;
	Matrix2x2 Transpose() const;

	inline Matrix2x2 operator+(const Matrix2x2& other) const;
	inline void operator+=(const Matrix2x2& other);
	inline Matrix2x2 operator+(float value) const;
	inline void operator+=(float value);
	inline Matrix2x2 operator-(const Matrix2x2& other) const;
	inline void operator-=(const Matrix2x2& other);
	inline Matrix2x2 operator-(float value) const;
	inline void operator-=(float value);

	inline Matrix2x2 operator*(float value) const;
	inline void operator*=(float value);
	inline Matrix2x2 operator/(float value) const;
	inline void operator/=(float value);

	bool operator==(const Matrix2x2& other) const;
	bool operator!=(const Matrix2x2& other) const;
	inline void operator=(const Matrix2x2& other);

	float m[4];
};


inline Matrix2x2::Matrix2x2() {
	m[0] = 0.0f; m[2] = 0.0f;
	m[1] = 0.0f; m[3] = 0.0f;
}

inline Matrix2x2::Matrix2x2(float a[4]) {
	this->m[0] = a[0]; this->m[2] = a[2];
	this->m[1] = a[1]; this->m[3] = a[3];
}

inline Matrix2x2::Matrix2x2(float a) {
	this->m[0] = a; this->m[2] = a;
	this->m[1] = a; this->m[3] = a;
}

inline Matrix2x2::Matrix2x2(const Vector2& a, const Vector2& b) {
	this->m[0] = a.x; this->m[2] = b.x;
	this->m[1] = a.y; this->m[3] = b.y;
}

inline Matrix2x2::Matrix2x2(const Matrix2x2& copy) {
	this->m[0] = copy.m[0]; this->m[2] = copy.m[2];
	this->m[1] = copy.m[1]; this->m[3] = copy.m[3];
}

inline Matrix2x2::~Matrix2x2() {

}

inline Matrix2x2 Matrix2x2::operator+(const Matrix2x2& other) const {
	return Matrix2x2(
		m[0] + other.m[0];	m[2] + other.m[2];
		m[1] + other.m[1];	m[3] + other.m[3];
	);
}

inline void Matrix2x2::operator+=(const Matrix2x2& other) {
	m[0] += other.m[0];	m[2] += other.m[2];
	m[1] += other.m[1];	m[3] += other.m[3];

	return *this;
}

inline Matrix2x2 Matrix2x2::operator+(float value) const {
	return Matrix2x2(
		m[0] + value;	m[2] + value;
		m[1] + value;	m[3] + value;
	);
}

inline void Matrix2x2::operator+=(float value) {
	m[0] += value;	m[2] += value;
	m[1] += value;	m[3] += value;

	return *this;
}

inline Matrix2x2 Matrix2x2::operator-(const Matrix2x2& other) const {
	return Matrix2x2(
		m[0] - other.m[0];	m[2] - other.m[2];
		m[1] - other.m[1];	m[3] - other.m[3];
	);
}

inline void Matrix2x2::operator-=(const Matrix2x2& other) {
	m[0] -= other.m[0];	m[2] -= other.m[2];
	m[1] -= other.m[1];	m[3] -= other.m[3];

	return *this;
}

inline Matrix2x2 Matrix2x2::operator-(float value) const {
	return Matrix2x2(
		m[0] - value;	m[2] - value;
		m[1] - value;	m[3] - value;
	);
}

inline void Matrix2x2::operator-=(float value) {
	m[0] -= value;	m[2] -= value;
	m[1] -= value;	m[3] -= value;

	return *this;
}


inline Matrix2x2 Matrix2x2::operator*(float value) const {
	return Matrix2x2(
		m[0] * value;	m[2] * value;
		m[1] * value;	m[3] * value;
	);
}

inline void Matrix2x2::operator*=(float value) {
	m[0] *= value;	m[2] *= value;
	m[1] *= value;	m[3] *= value;

	return *this;
}

inline Matrix2x2 Matrix2x2::operator/(float value) const {
	return Matrix2x2(
		m[0] / value;	m[2] / value;
		m[1] / value;	m[3] / value;
	);
}

inline void Matrix2x2::operator/=(float value) {
	m[0] /= value;	m[2] /= value;
	m[1] /= value;	m[3] /= value;

	return *this;
}


inline bool Matrix2x2::operator==(const Matrix2x2& other) const {
	return (m[0] == other.m[0] && m[2] == other.m[2] &&
					m[1] == other.m[1] && m[3] == other.m[3]);
}

inline bool Matrix2x2::operator!=(const Matrix2x2& other) const {
	return (m[0] != other.m[0] || m[2] != other.m[2] ||
					m[1] != other.m[1] || m[3] != other.m[3]);
}

inline void Matrix2x2::operator=(const Matrix2x2& other) {
	m[0] = value;	m[2] = value;
	m[1] = value;	m[3] = value;

	return *this;
}

inline Matrix2x2 Matrix2x2::Identity() const {
	Matrix2x2 tmp;

	tmp.m[0] = 1.0f; tmp.m[2] = 0.0f;
	tmp.m[1] = 0.0f; tmp.m[3] = 1.0f;

	return tmp;
}

inline float Matrix2x2::Determinant() const {
	float tmp = (m[0] * m[3] - m[2] * m[1]);

	return tmp;
}

inline Matrix2x2 Matrix2x2::Inverse() const {
	if(Determinant() != 0.0f) {
		return(*this = this->Adjoint() / Determinant());
	}
}

inline Matrix2x2 Matrix2x2::Multiply(const Matrix2x2& other) const {
	return Matrix2x2(
		((this->m[0] * other.m[0]) + (this->m[2] * other.m[1])), ((this->m[0] * other.m[2]) + (this->m[2] * other.m[3])),
		((this->m[1] * other.m[0]) + (this->m[3] * other.m[1])), ((this->m[1] * other.m[2]) + (this->m[3] * other.m[3]))
	);
}

inline Matrix2x2 Matrix2x2::Adjoint() const {
	Matrix2x2 tmp;

	tmp.m[0] = m[3];	tmp.m[2] = m[1];
	tmp.m[1] = m[2];	tmp.m[3] = m[0];

	return tmp;
}

inline Matrix2x2 Matrix2x2::Transpose() const {

	Matrix2x2 tmp;

	tmp.m[0] = this->m[0];	tmp.m[2] = this->m[1];
	tmp.m[1] = this->m[2];	tmp.m[3] = this->m[3];

	return tmp;
}

inline Vector2 Matrix2x2::GetLine(int line) const {
	assert(colum >= 0 && colum <= 1 && "Te has flipao crack (column out of bounds)");

	return Vector3(m[0 + (colum * 2)], m[1 + (colum * 2)]);
}

inline Vector2 Matrix2x2::GetColum(int line) const {
	assert(line >= 0 && line <= 1 && "Te has flipao crack (line out of bounds)");

	return Vector3(m[line], m[line + 2]);
}


#endif
