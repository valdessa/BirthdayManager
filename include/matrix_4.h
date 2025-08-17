/**
 * @file   matrix4.h
 * @brief  matrix4 header file
 *
 * @author Sebastián Valdés Sánchez (valdessa@esat-alumni.com)
 * @date   November 2021
 */

#ifndef __MATRIX4_H__
#define __MATRIX4_H__ 1

#include "vector_3.h"
#include "vector_4.h"
#include "matrix_3.h"

class Matix4x4{
 public:

  Matix4x4();
  Matix4x4(float a[16]);
  Matix4x4(float value);
  Matix4x4(const Matix4x4& copy);
  ~Matix4x4();

  Matix4x4 Identity() const;
  Matix4x4 Multiply(const Matix4x4& other) const;

  float Determinant() const;
  Matix4x4 Adjoint() const;
  bool GetInverse(Matix4x4& out) const;
  bool Inverse();

  Matix4x4 Transpose() const;


  static Matix4x4 Translate(const Vector3& distance);
  static Matix4x4 Translate(float x, float y, float z);

  static Matix4x4 Scale(const Vector3& scale);
  static Matix4x4 Scale(float x, float y, float z);

  static Matix4x4 RotateX(float radians);
  static Matix4x4 RotateY(float radians);
  static Matix4x4 RotateZ(float radians);

  static Matix4x4 GetTransform(const Vector3& translate, const Vector3& scale,
                               float rotateX, float rotateY, float rotateZ);

  static Matix4x4 GetTransform(float trans_x, float trans_y, float trans_z,
                               float scale_x, float scale_y, float scale_Z,
                               float rotateX, float rotateY, float rotateZ);

  Matix4x4 PerspectiveMatrix(float fov, float aspect,
    float near, float far) const;

  Matix4x4 OrthoMatrix(float right, float left, float top, float valueottom,
    float near, float far) const;

  Vector4 Matix4x4::Mat4TransformVec4(const Vector4& v);
  Vector3 Matix4x4::Mat4TransformVec3(const Vector3& v);
  Matix4x4 Matix4x4::Mat4Projection() const;

  Vector4 GetColum(int colum) const;
  Vector4 GetLine(int line) const;

  Matix4x4 operator+(const Matix4x4& other) const;
  Matix4x4& operator+=(const Matix4x4& other);
  Matix4x4 operator+(float value) const;
  Matix4x4& operator+=(float value);
  Matix4x4 operator-(const Matix4x4& other) const;
  Matix4x4& operator-=(const Matix4x4& other);
  Matix4x4 operator-(float value) const;
  Matix4x4& operator-=(float value);
  Matix4x4& operator*=(float value);
  Matix4x4 operator*(float value) const;
  Matix4x4& operator/=(float value);
  Matix4x4 operator/(float value) const;
  bool operator==(const Matix4x4& other);
  bool operator!=(const Matix4x4& other);
  void operator=(const Matix4x4& other);

  float m[16];
  const float PI = 3.14159265358979f;
};


inline Matix4x4::Matix4x4() {
  m[0] = 0.0f; m[4] = 0.0f; m[8] = 0.0f;  m[12] = 0.0f;
  m[1] = 0.0f; m[5] = 0.0f; m[9] = 0.0f;  m[13] = 0.0f;
  m[2] = 0.0f; m[6] = 0.0f; m[10] = 0.0f; m[14] = 0.0f;
  m[3] = 0.0f; m[7] = 0.0f; m[11] = 0.0f; m[15] = 0.0f;
}

inline Matix4x4::Matix4x4(float array[16]) {
  m[0] = array[0]; m[4] = array[4]; m[8] = array[8];   m[12] = array[12];
  m[1] = array[1]; m[5] = array[5]; m[9] = array[9];   m[13] = array[13];
  m[2] = array[2]; m[6] = array[6]; m[10] = array[10]; m[14] = array[14];
  m[3] = array[3]; m[7] = array[7]; m[11] = array[11]; m[15] = array[15];
}

inline Matix4x4::Matix4x4(float value) {
  m[0] = value; m[4] = value; m[8] = value;  m[12] = value;
  m[1] = value; m[5] = value; m[9] = value;  m[13] = value;
  m[2] = value; m[6] = value; m[10] = value; m[14] = value;
  m[3] = value; m[7] = value; m[11] = value; m[15] = value;
}

inline Matix4x4::Matix4x4(const Matix4x4& copy) {
  m[0] = copy.m[0]; m[4] = copy.m[4]; m[8] = copy.m[8];  m[12] = copy.m[12];
  m[1] = copy.m[1]; m[5] = copy.m[5]; m[9] = copy.m[9];  m[13] = copy.m[13];
  m[2] = copy.m[2]; m[6] = copy.m[6]; m[10] = copy.m[10]; m[14] = copy.m[14];
  m[3] = copy.m[3]; m[7] = copy.m[7]; m[11] = copy.m[11]; m[15] = copy.m[15];
}

inline Matix4x4::~Matix4x4() {

}

inline Matix4x4 Matix4x4::Identity() const {
  Matix4x4 tmp;
  tmp.m[0] = 1.0f; tmp.m[4] = 0.0f; tmp.m[8] = 0.0f;  tmp.m[12] = 0.0f;
  tmp.m[1] = 0.0f; tmp.m[5] = 1.0f; tmp.m[9] = 0.0f;  tmp.m[13] = 0.0f;
  tmp.m[2] = 0.0f; tmp.m[6] = 0.0f; tmp.m[10] = 1.0f; tmp.m[14] = 0.0f;
  tmp.m[3] = 0.0f; tmp.m[7] = 0.0f; tmp.m[11] = 0.0f; tmp.m[15] = 1.0f;
  return tmp;
}

inline Matix4x4 Matix4x4::Multiply(const Matix4x4& other)const {
  float tmp[16];

  tmp[0]  = (this->m[0] * other.m[0]) + (this->m[4] * other.m[1]) + (this->m[8] * other.m[2]) + (this->m[12] * other.m[3]);
  tmp[4]  = (this->m[0] * other.m[4]) + (this->m[4] * other.m[5]) + (this->m[8] * other.m[6]) + (this->m[12] * other.m[7]);
  tmp[8]  = (this->m[0] * other.m[8]) + (this->m[4] * other.m[9]) + (this->m[8] * other.m[10]) + (this->m[12] * other.m[11]);
  tmp[12] = (this->m[0] * other.m[12]) + (this->m[4] * other.m[13]) + (this->m[8] * other.m[14]) + (this->m[12] * other.m[15]);

  tmp[1]  = (this->m[1] * other.m[0]) + (this->m[5] * other.m[1]) + (this->m[9] * other.m[2]) + (this->m[13] * other.m[3]);
  tmp[5]  = (this->m[1] * other.m[4]) + (this->m[5] * other.m[5]) + (this->m[9] * other.m[6]) + (this->m[13] * other.m[7]);
  tmp[9]  = (this->m[1] * other.m[8]) + (this->m[5] * other.m[9]) + (this->m[9] * other.m[10]) + (this->m[13] * other.m[11]);
  tmp[13] = (this->m[1] * other.m[12]) + (this->m[5] * other.m[13]) + (this->m[9] * other.m[14]) + (this->m[13] * other.m[15]);

  tmp[2] = (this->m[2] * other.m[0]) + (this->m[6] * other.m[1]) + (this->m[10] * other.m[2]) + (this->m[14] * other.m[3]);
  tmp[6] = (this->m[2] * other.m[4]) + (this->m[6] * other.m[5]) + (this->m[10] * other.m[6]) + (this->m[14] * other.m[7]);
  tmp[10] = (this->m[2] * other.m[8]) + (this->m[6] * other.m[9]) + (this->m[10] * other.m[10]) + (this->m[14] * other.m[11]);
  tmp[14] = (this->m[2] * other.m[12]) + (this->m[6] * other.m[13]) + (this->m[10] * other.m[14]) + (this->m[14] * other.m[15]);

  tmp[3] = (this->m[3] * other.m[0]) + (this->m[7] * other.m[1]) + (this->m[11] * other.m[2]) + (this->m[15] * other.m[3]);
  tmp[7] = (this->m[3] * other.m[4]) + (this->m[7] * other.m[5]) + (this->m[11] * other.m[6]) + (this->m[15] * other.m[7]);
  tmp[11] = (this->m[3] * other.m[8]) + (this->m[7] * other.m[9]) + (this->m[11] * other.m[10]) + (this->m[15] * other.m[11]);
  tmp[15] = (this->m[3] * other.m[12]) + (this->m[7] * other.m[13]) + (this->m[11] * other.m[14]) + (this->m[15] * other.m[15]);


  return Matix4x4(tmp);
}


inline float Matix4x4::Determinant() const {
  return (m[3] * m[6] * m[9] * m[12] - m[2] * m[7] * m[9] * m[12] -
          m[3] * m[5] * m[10] * m[12] + m[1] * m[7] * m[10] * m[12] +
          m[2] * m[5] * m[11] * m[12] - m[1] * m[6] * m[11] * m[12] -
          m[3] * m[6] * m[8] * m[13] + m[2] * m[7] * m[8] * m[13] +
          m[3] * m[4] * m[10] * m[13] - m[0] * m[7] * m[10] * m[13] -
          m[2] * m[4] * m[11] * m[13] + m[0] * m[6] * m[11] * m[13] +
          m[3] * m[5] * m[8] * m[14] - m[1] * m[7] * m[8] * m[14] -
          m[3] * m[4] * m[9] * m[14] + m[0] * m[7] * m[9] * m[14] +
          m[1] * m[4] * m[11] * m[14] - m[0] * m[5] * m[11] * m[14] -
          m[2] * m[5] * m[8] * m[15] + m[1] * m[6] * m[8] * m[15] +
          m[2] * m[4] * m[9] * m[15] - m[0] * m[6] * m[9] * m[15] -
          m[1] * m[4] * m[10] * m[15] + m[0] * m[5] * m[10] * m[15]);
}


inline Matix4x4 Matix4x4::Adjoint() const {
  Matix4x4 tmp;

  tmp.m[0] = (((m[5] * m[10] * m[15]) +
           (m[6] * m[11] * m[13]) +
           (m[9] * m[14] * m[7])) -
           ((m[13] * m[10] * m[7]) +
           (m[9] * m[6] * m[15]) +
           (m[14] * m[11] * m[5])));

  tmp.m[1] = -(((m[4] * m[10] * m[15]) +
           (m[6] * m[11] * m[12]) +
           (m[8] * m[14] * m[7])) -
           ((m[12] * m[10] * m[7]) +
           (m[8] * m[6] * m[15]) +
           (m[14] * m[11] * m[4])));

  tmp.m[2] = (((m[4] * m[9] * m[15]) +
           (m[5] * m[11] * m[12]) +
           (m[8] * m[13] * m[7])) -
           ((m[12] * m[9] * m[7]) +
           (m[8] * m[5] * m[15]) +
           (m[13] * m[11] * m[4])));

  tmp.m[3] = -(((m[4] * m[9] * m[14]) +
           (m[5] * m[10] * m[12]) +
           (m[8] * m[13] * m[6])) -
           ((m[12] * m[9] * m[6]) +
           (m[8] * m[5] * m[14]) +
           (m[13] * m[10] * m[4])));

  tmp.m[4] = -(((m[1] * m[10] * m[15]) +
           (m[2] * m[11] * m[13]) +
           (m[9] * m[14] * m[3])) -
           ((m[13] * m[10] * m[3]) +
           (m[9] * m[2] * m[15]) +
           (m[14] * m[11] * m[1])));

  tmp.m[5] = (((m[0] * m[10] * m[15]) +
           (m[2] * m[11] * m[12]) +
           (m[8] * m[14] * m[3])) -
           ((m[12] * m[10] * m[3]) +
           (m[8] * m[2] * m[15]) +
           (m[14] * m[11] * m[0])));

  tmp.m[6] = -(((m[0] * m[9] * m[15]) +
           (m[1] * m[11] * m[12]) +
           (m[8] * m[13] * m[3])) -
           ((m[12] * m[9] * m[3]) +
           (m[8] * m[1] * m[15]) +
           (m[13] * m[11] * m[0])));

  tmp.m[7] = +(((m[0] * m[9] * m[14]) +
           (m[1] * m[10] * m[12]) +
           (m[8] * m[13] * m[2])) -
           ((m[12] * m[9] * m[2]) +
           (m[8] * m[1] * m[14]) +
           (m[13] * m[10] * m[0])));

  tmp.m[8] = (((m[1] * m[6] * m[15]) +
           (m[2] * m[7] * m[13]) +
           (m[5] * m[14] * m[3])) -
           ((m[13] * m[6] * m[3]) +
           (m[5] * m[2] * m[15]) +
           (m[14] * m[7] * m[1])));

  tmp.m[9] = -(((m[0] * m[6] * m[15]) +
           (m[2] * m[7] * m[12]) +
           (m[4] * m[14] * m[3])) -
           ((m[12] * m[6] * m[3]) +
           (m[4] * m[2] * m[15]) +
           (m[14] * m[7] * m[0])));

  tmp.m[10] = (((m[0] * m[5] * m[15]) +
           (m[1] * m[7] * m[12]) +
           (m[4] * m[13] * m[3])) -
           ((m[12] * m[5] * m[3]) +
           (m[4] * m[1] * m[15]) +
           (m[13] * m[7] * m[0])));

  tmp.m[11] = -(((m[0] * m[5] * m[14]) +
           (m[1] * m[6] * m[12]) +
           (m[4] * m[13] * m[2])) -
           ((m[12] * m[5] * m[2]) +
           (m[4] * m[1] * m[14]) +
           (m[13] * m[6] * m[0])));

  tmp.m[12] = -(((m[1] * m[6] * m[11]) +
           (m[2] * m[7] * m[9]) +
           (m[5] * m[10] * m[3])) -
           ((m[9] * m[6] * m[3]) +
           (m[5] * m[2] * m[11]) +
           (m[10] * m[7] * m[1])));

  tmp.m[13] = (((m[0] * m[6] * m[11]) +
           (m[2] * m[7] * m[8]) +
           (m[4] * m[10] * m[3])) -
           ((m[8] * m[6] * m[3]) +
           (m[4] * m[2] * m[11]) +
           (m[10] * m[7] * m[0])));

  tmp.m[14] = -(((m[0] * m[5] * m[11]) +
           (m[1] * m[7] * m[8]) +
           (m[4] * m[9] * m[3])) -
           ((m[8] * m[5] * m[3]) +
           (m[4] * m[1] * m[11]) +
           (m[9] * m[7] * m[0])));

  tmp.m[15] = (((m[0] * m[5] * m[10]) +
           (m[1] * m[6] * m[8]) +
           (m[4] * m[9] * m[2])) -
           ((m[8] * m[5] * m[2]) +
           (m[4] * m[1] * m[10]) +
           (m[9] * m[6] * m[0])));

  return tmp;
}

inline bool Matix4x4::Inverse() {
  // if(Determinant() != 0.0f) {
  //   *this = this->Adjoint().Transpose() / Determinant();
  //   return true;
  // }
  //
  // return false;
  return GetInverse(*this);
}

inline bool Matix4x4::GetInverse(Matix4x4& out) const {
  if(Determinant() != 0.0f) {
    out = out.Adjoint().Transpose() / out.Determinant();
    return true;
  }

  return false;
}

inline Matix4x4 Matix4x4::Transpose() const {
  float tmp[16];

  tmp[0] = this->m[0];  tmp[4] = this->m[1];  tmp[8] =  this->m[2];  tmp[12] = this->m[3];
  tmp[1] = this->m[4];  tmp[5] = this->m[5];  tmp[9] =  this->m[6];  tmp[13] = this->m[7];
  tmp[2] = this->m[8];  tmp[6] = this->m[9];  tmp[10] = this->m[10]; tmp[14] = this->m[11];
  tmp[3] = this->m[12]; tmp[7] = this->m[13]; tmp[11] = this->m[14]; tmp[15] = this->m[15];

  return Matix4x4(tmp);
}

inline Matix4x4 Matix4x4::Translate(const Vector3& distance){
  Matix4x4 tmp = tmp.Identity();
  tmp.m[12] = distance.x;
  tmp.m[13] = distance.y;
  tmp.m[14] = distance.z;

  return tmp;
}

inline Matix4x4 Matix4x4::Translate(float x, float y, float z){
  Matix4x4 tmp = tmp.Identity();
  tmp.m[12] = x;
  tmp.m[13] = y;
  tmp.m[14] = z;

  return tmp;
}

inline Matix4x4 Matix4x4::Scale(const Vector3& scale){
  Matix4x4 tmp = tmp.Identity();
  tmp.m[0]  = scale.x;
  tmp.m[5]  = scale.y;
  tmp.m[10] = scale.z;

  return tmp;
}

inline Matix4x4 Matix4x4::Scale(float x, float y, float z){
  Matix4x4 tmp = tmp.Identity();
  tmp.m[0]  = x;
  tmp.m[5]  = y;
  tmp.m[10] = z;

  return tmp;
}

inline Matix4x4 Matix4x4::RotateX(float radians){
  Matix4x4 tmp = tmp.Identity();
  tmp.m[5]  = cosf(radians);
  tmp.m[6]  = sinf(radians);
  tmp.m[9]  = -sinf(radians);
  tmp.m[10] = cosf(radians);

  return tmp;
}

inline Matix4x4 Matix4x4::RotateY(float radians){
  Matix4x4 tmp = tmp.Identity();
  tmp.m[0]  = cosf(radians);
  tmp.m[2]  = -sinf(radians);
  tmp.m[8]  = sinf(radians);
  tmp.m[10] = cosf(radians);

  return tmp;
}

inline Matix4x4 Matix4x4::RotateZ(float radians) {
  Matix4x4 tmp = tmp.Identity();
  tmp.m[0]  = cosf(radians);
  tmp.m[1]  = sinf(radians);
  tmp.m[4]  = -sinf(radians);
  tmp.m[5] = cosf(radians);

  return tmp;
}

inline Matix4x4 Matix4x4::GetTransform(const Vector3& translate,
                                       const Vector3& scale,
                                       float rotateX, float rotateY, float rotateZ)   {

  Matix4x4 result;
  Matix4x4 translation;
  Matix4x4 scaling;
  Matix4x4 rotation;

  // R = Rx · Ry · Rz
  rotation = rotation.RotateX(rotateX).Multiply(rotation.RotateY(rotateY).Multiply(rotation.RotateZ(rotateZ)));

  // MT = T · R · S
  result = translation.Translate(translate.x, translate.y, translate.z).Multiply(rotation.Multiply(scaling.Scale(scale.x, scale.y, scale.z)));

  return result;
}

inline Matix4x4 Matix4x4::GetTransform(float trans_x, float trans_y, float trans_z,
                                       float scale_x, float scale_y, float scale_Z,
                                       float rotateX, float rotateY, float rotateZ)  {

   Matix4x4 result;
   Matix4x4 translation;
   Matix4x4 scaling;
   Matix4x4 rotation;

   // R = Rx · Ry · Rz
   rotation = rotation.RotateX(rotateX).Multiply(rotation.RotateY(rotateY).Multiply(rotation.RotateZ(rotateZ)));

   // MT = T · R · S
   result = translation.Translate(trans_x, trans_y, trans_z).Multiply(rotation.Multiply(scaling.Scale(scale_x, scale_y, scale_Z)));

   return result;
 }

inline Vector4 Matix4x4::GetColum(int colum) const {
  assert(colum >= 0 && colum < 4 && "Index out of range");

  return Vector4(this->m[(colum * 4) + 0], this->m[(colum * 4) + 1], this->m[(colum * 4) + 2], this->m[(colum * 4) + 3]);
}

inline Vector4 Matix4x4::GetLine(int line) const {
  assert(line >= 0 && line < 4 && "Line out of bounds");

  return Vector4(this->m[(0 * 4) + line], this->m[(1 * 4) + line], this->m[(2 * 4) + line], this->m[(3 * 4) + line]);
}

inline Matix4x4 Matix4x4::PerspectiveMatrix(float fov, float aspect,
                                            float near, float far) const {

  Matix4x4 tmp = Matix4x4();
  tmp.m[0] = (1.0f / tanf((fov * PI / 180.0f) / 2.0f)) / (fov / aspect);
  tmp.m[5] = 1.0f / tanf((fov * PI / 180.0f) / 2.0f);
  tmp.m[10] = (far + near) / (near - far);
  tmp.m[11] = (2.0f * far * near) / (near - far);
  tmp.m[14] = -1.0f;

  return tmp;
}

inline Matix4x4 Matix4x4::OrthoMatrix(float right, float left, float top, float valueottom,
                                      float near, float far) const {

  Matix4x4 tmp = Matix4x4();
  tmp.m[0] = 2.0f / (right - left);
  tmp.m[3] = -((right + left) / (right -left));
  tmp.m[5] = 2.0f / (top - valueottom);
  tmp.m[7] = ((top + valueottom) / (top - valueottom));
  tmp.m[10] = 2.0f / (far - near);
  tmp.m[11] = -((far + near) / (far - near));

  return tmp;
}

inline Vector4 Matix4x4::Mat4TransformVec4(const Vector4& v) {
	Vector4 tmp;

	tmp.x = m[0] * v.x + m[4] * v.y +	m[8] * v.z +  m[12] * v.w;
	tmp.y = m[1] * v.x + m[5] * v.y + m[9] * v.z +  m[13] * v.w;
	tmp.z = m[2] * v.x + m[6] * v.y + m[10] * v.z + m[14] * v.w;
  tmp.w = m[3] * v.x + m[7] * v.y + m[11] * v.z + m[15] * v.w;

	return tmp;
}

inline Vector3 Matix4x4::Mat4TransformVec3(const Vector3& v) {
  Vector4 tmp;
  tmp.x = v.x;
  tmp.y = v.y;
  tmp.z = v.z;
  tmp.w = 1.0f;

  Vector4 result = Mat4TransformVec4(tmp);
  result.x = result.x / result.w;
  result.y = result.y / result.w;
  result.z = result.z / result.w;

  Vector3 k(result.x, result.y, result.z);

  return k;
}

inline Matix4x4 Matix4x4::Mat4Projection() const {
  Matix4x4 tmp = tmp.Identity();
  tmp.m[11] = 1.0f;
  tmp.m[15] = 0.0f;

  return tmp;
}



inline Matix4x4 Matix4x4::operator+(const Matix4x4& other) const {
  Matix4x4 tmp;
    tmp.m[0] = m[0] + other.m[0]; tmp.m[4] = m[4] + other.m[4]; tmp.m[8] =  m[8] +  other.m[8],  tmp.m[12] = m[12] + other.m[12];
    tmp.m[1] = m[1] + other.m[1]; tmp.m[5] = m[5] + other.m[5]; tmp.m[9] =  m[9] +  other.m[9],  tmp.m[13] = m[13] + other.m[13];
    tmp.m[2] = m[2] + other.m[2]; tmp.m[6] = m[6] + other.m[6]; tmp.m[10] = m[10] + other.m[10], tmp.m[14] = m[14] + other.m[14];
    tmp.m[3] = m[3] + other.m[3]; tmp.m[7] = m[7] + other.m[7]; tmp.m[11] = m[11] + other.m[11], tmp.m[15] = m[15] + other.m[15];
  return tmp;
}

inline Matix4x4& Matix4x4::operator+=(const Matix4x4& other) {
  m[0] += other.m[0]; m[4] += other.m[4]; m[8] +=  other.m[8],  m[12] += other.m[12];
  m[1] += other.m[1]; m[5] += other.m[5]; m[9] +=  other.m[9],  m[13] += other.m[13];
  m[2] += other.m[2]; m[6] += other.m[6]; m[10] += other.m[10], m[14] += other.m[14];
  m[3] += other.m[3]; m[7] += other.m[7]; m[11] += other.m[11], m[15] += other.m[15];
  return *this;
}

inline Matix4x4 Matix4x4::operator+(float value) const {
  Matix4x4 tmp;
  tmp.m[0] = m[0] + value; tmp.m[4] = m[4] + value; tmp.m[8] =  m[8] +  value, tmp.m[12] = m[12] + value;
  tmp.m[1] = m[1] + value; tmp.m[5] = m[5] + value; tmp.m[9] =  m[9] +  value, tmp.m[13] = m[13] + value;
  tmp.m[2] = m[2] + value; tmp.m[6] = m[6] + value; tmp.m[10] = m[10] + value, tmp.m[14] = m[14] + value;
  tmp.m[3] = m[3] + value; tmp.m[7] = m[7] + value; tmp.m[11] = m[11] + value, tmp.m[15] = m[15] + value;
  return tmp;
}

inline Matix4x4& Matix4x4::operator+=(float value) {
  m[0] += value; m[4] += value; m[8] +=  value, m[12] += value;
  m[1] += value; m[5] += value; m[9] +=  value, m[13] += value;
  m[2] += value; m[6] += value; m[10] += value, m[14] += value;
  m[3] += value; m[7] += value; m[11] += value, m[15] += value;
  return *this;
}


inline Matix4x4 Matix4x4::operator-(const Matix4x4& other) const  {
  Matix4x4 tmp;
    tmp.m[0] = m[0] - other.m[0]; tmp.m[4] = m[4] - other.m[4]; tmp.m[8] =  m[8] -  other.m[8],  tmp.m[12] = m[12] - other.m[12];
    tmp.m[1] = m[1] - other.m[1]; tmp.m[5] = m[5] - other.m[5]; tmp.m[9] =  m[9] -  other.m[9],  tmp.m[13] = m[13] - other.m[13];
    tmp.m[2] = m[2] - other.m[2]; tmp.m[6] = m[6] - other.m[6]; tmp.m[10] = m[10] - other.m[10], tmp.m[14] = m[14] - other.m[14];
    tmp.m[3] = m[3] - other.m[3]; tmp.m[7] = m[7] - other.m[7]; tmp.m[11] = m[11] - other.m[11], tmp.m[15] = m[15] - other.m[15];
  return tmp;
}

inline Matix4x4& Matix4x4::operator-=(const Matix4x4& other) {
  m[0] -= other.m[0]; m[4] -= other.m[4]; m[8] -=  other.m[8],  m[12] -= other.m[12];
  m[1] -= other.m[1]; m[5] -= other.m[5]; m[9] -=  other.m[9],  m[13] -= other.m[13];
  m[2] -= other.m[2]; m[6] -= other.m[6]; m[10] -= other.m[10], m[14] -= other.m[14];
  m[3] -= other.m[3]; m[7] -= other.m[7]; m[11] -= other.m[11], m[15] -= other.m[15];
  return *this;
}

inline Matix4x4 Matix4x4::operator-(float value) const  {
  Matix4x4 tmp;
  tmp.m[0] = m[0] - value; tmp.m[4] = m[4] - value; tmp.m[8] =  m[8] -  value, tmp.m[12] = m[12] - value;
  tmp.m[1] = m[1] - value; tmp.m[5] = m[5] - value; tmp.m[9] =  m[9] -  value, tmp.m[13] = m[13] - value;
  tmp.m[2] = m[2] - value; tmp.m[6] = m[6] - value; tmp.m[10] = m[10] - value, tmp.m[14] = m[14] - value;
  tmp.m[3] = m[3] - value; tmp.m[7] = m[7] - value; tmp.m[11] = m[11] - value, tmp.m[15] = m[15] - value;
  return tmp;
}

inline Matix4x4& Matix4x4::operator-=(float value) {
  m[0] -= value; m[4] -= value; m[8] -=  value, m[12] -= value;
  m[1] -= value; m[5] -= value; m[9] -=  value, m[13] -= value;
  m[2] -= value; m[6] -= value; m[10] -= value, m[14] -= value;
  m[3] -= value; m[7] -= value; m[11] -= value, m[15] -= value;
  return *this;
}

inline Matix4x4 Matix4x4::operator*(float value) const  {
  Matix4x4 tmp;
  tmp.m[0] = m[0] * value; tmp.m[4] = m[4] * value; tmp.m[8] =  m[8] *  value, tmp.m[12] = m[12] * value;
  tmp.m[1] = m[1] * value; tmp.m[5] = m[5] * value; tmp.m[9] =  m[9] *  value, tmp.m[13] = m[13] * value;
  tmp.m[2] = m[2] * value; tmp.m[6] = m[6] * value; tmp.m[10] = m[10] * value, tmp.m[14] = m[14] * value;
  tmp.m[3] = m[3] * value; tmp.m[7] = m[7] * value; tmp.m[11] = m[11] * value, tmp.m[15] = m[15] * value;
  return tmp;
}

inline Matix4x4& Matix4x4::operator*=(float value) {
  m[0] *= value; m[4] *= value; m[8] *=  value, m[12] *= value;
  m[1] *= value; m[5] *= value; m[9] *=  value, m[13] *= value;
  m[2] *= value; m[6] *= value; m[10] *= value, m[14] *= value;
  m[3] *= value; m[7] *= value; m[11] *= value, m[15] *= value;
  return *this;
}

inline Matix4x4 Matix4x4::operator/(float value) const {
  Matix4x4 tmp;
  float  tmp_value = 1 / value;
  tmp.m[0] = m[0] * tmp_value; tmp.m[4] = m[4] * tmp_value; tmp.m[8] =  m[8] * tmp_value,  tmp.m[12] = m[12] * tmp_value;
  tmp.m[1] = m[1] * tmp_value; tmp.m[5] = m[5] * tmp_value; tmp.m[9] =  m[9] * tmp_value,  tmp.m[13] = m[13] * tmp_value;
  tmp.m[2] = m[2] * tmp_value; tmp.m[6] = m[6] * tmp_value; tmp.m[10] = m[10] * tmp_value, tmp.m[14] = m[14] * tmp_value;
  tmp.m[3] = m[3] * tmp_value; tmp.m[7] = m[7] * tmp_value; tmp.m[11] = m[11] * tmp_value, tmp.m[15] = m[15] * tmp_value;
  return tmp;
}

inline Matix4x4& Matix4x4::operator/=(float value) {
  float tmp_value = 1 / value;
  m[0] *= tmp_value; m[4] *= tmp_value; m[8] *=  tmp_value, m[12] *= tmp_value;
  m[1] *= tmp_value; m[5] *= tmp_value; m[9] *=  tmp_value, m[13] *= tmp_value;
  m[2] *= tmp_value; m[6] *= tmp_value; m[10] *= tmp_value, m[14] *= tmp_value;
  m[3] *= tmp_value; m[7] *= tmp_value; m[11] *= tmp_value, m[15] *= tmp_value;
  return *this;
}

inline bool Matix4x4::operator==(const Matix4x4& other) {
  return (m[0] == other.m[0] && m[4] == other.m[4] && m[8] ==  other.m[8] &&  m[12] == other.m[12] &&
          m[1] == other.m[1] && m[5] == other.m[5] && m[9] ==  other.m[9] &&  m[13] == other.m[13] &&
          m[2] == other.m[2] && m[6] == other.m[6] && m[10] == other.m[10] && m[14] == other.m[14] &&
          m[3] == other.m[3] && m[7] == other.m[7] && m[11] == other.m[11] && m[15] == other.m[15]);
}

inline bool Matix4x4::operator!=(const Matix4x4& other) {
  return (m[0] != other.m[0] || m[4] != other.m[4] || m[8] !=  other.m[8] ||  m[12] != other.m[12] ||
          m[1] != other.m[1] || m[5] != other.m[5] || m[9] !=  other.m[9] ||  m[13] != other.m[13] ||
          m[2] != other.m[2] || m[6] != other.m[6] || m[10] != other.m[10] || m[14] != other.m[14] ||
          m[3] != other.m[3] || m[7] != other.m[7] || m[11] != other.m[11] || m[15] != other.m[15]);
}

inline void Matix4x4::operator=(const Matix4x4& other) {
  m[0] = other.m[0]; m[4] = other.m[4]; m[8] =  other.m[8];  m[12] = other.m[12];
  m[1] = other.m[1]; m[5] = other.m[5]; m[9] =  other.m[9];  m[13] = other.m[13];
  m[2] = other.m[2]; m[6] = other.m[6]; m[10] = other.m[10]; m[14] = other.m[14];
  m[3] = other.m[3]; m[7] = other.m[7]; m[11] = other.m[11]; m[15] = other.m[15];
}

#endif
