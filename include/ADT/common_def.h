// common_def.h
// Escuela Superior de Arte y Tecnologia
// Algoritmos & Inteligencia Artificial
// ESAT 2020-2021
//
#ifndef __COMMON_DEF_H__
#define __COMMON_DEF_H__ 1

#define VERBOSE_

typedef enum {
  kErrorCode_Ok = 0,
  kErrorCode_MemNodeNull = -1,
  kErrorCode_DataNull = -2,
  kErrorCode_Zerosize = -3,
  kErrorCode_Memory = -4,
  kErrorCode_VectorNull = -5,
  kErrorCode_VectorStorageNull = -6,
  kErrorCode_VectorTailZero = -7,
  kErrorCode_EqualResize = -8,
  kErrorCode_VectorFull = -9,
  kErrorCode_PositionNotAble = -10
}ErrorCode;

#endif // __COMMON_DEF_H__