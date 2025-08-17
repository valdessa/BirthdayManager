// adt_vector.h
// Escuela Superior de Arte y Tecnologia
// Algoritmos & Inteligencia Artificial
// ESAT 2020-2021
//

#ifndef __ADT_VECTOR_H__
#define __ADT_VECTOR_H__

#include "adt_memory_node.h"

typedef struct adt_vector_s {
	u16 head_;
	u16 tail_; // Corresponds to the first free place of the vector
	u16 capacity_;
	MemoryNode *storage_;
	struct vector_ops_s *ops_;
} Vector;

struct vector_ops_s {
	
/**
 * @brief Destroys the vector and its data
 * @param *Vector pointer to the Vector to be destroyed
 * @return s16 kErrorCode_VectorNull if Vector is NULL
 * @return s16 kErrorCode_VectorStorageNull if Vector->Storage is NULL
 * @return s16 kErrorCode_Ok if everything is OK
*/
	s16 (*destroy)(Vector *vector);

/**
 * @brief Soft resets vector's data
 * @param *Vector pointer to the Vector to be softReseted
 * @return s16 kErrorCode_VectorNull if Vector is NULL
 * @return s16 kErrorCode_VectorTailZero if Vector->tail is 0
 * @return s16 kErrorCode_VectorStorageNull if Vector->Storage is NULL
 * @return s16 kErrorCode_Ok if everything is OK
*/
  s16 (*softReset)(Vector *vector);	

/**
 * @brief Resets vector's data
 * @param *Vector pointer to the Vector to be Reseted
 * @return s16 kErrorCode_VectorNull if Vector is NULL
 * @return s16 kErrorCode_VectorStorageNull if Vector->Storage is NULL
 * @return s16 kErrorCode_Ok if everything is OK
*/
  s16 (*reset)(Vector *vector);

/**
 * @brief Resizes the capacity of the vector
 * @param *Vector pointer to the Vector to be Reseted
 * @param u16 new_size New size of the Vector
 * @return s16 kErrorCode_VectorNull if Vector is NULL
 * @return s16 kErrorCode_Zerosize if new_size if 0 
 * @return s16 kErrorCode_EqualResize if Vector->Capacity is equal to new_size
 * @return s16 kErrorCode_VectorStorageNull if Vector->Storage is NULL
 * @return s16 kErrorCode_Memory if there is not enough memory to allocate a block
 * @return s16 kErrorCode_Ok if everything is OK
*/
	s16 (*resize)(Vector *vector, u16 new_size); 

	// State queries

/**
 * @brief Returns the maximum number of elemets to store
 * @param *Vector pointer to the Vector to know its capacity
 * @return 0 if Vector is NULL
 * @return u16 Capacity of the Vector if everything is OK
*/
	u16 (*capacity)(Vector *vector);

/**
 * @brief Current number of elements (<= capacity)
 * @param *Vector pointer to the Vector to know its lenght
 * @return 0 if Vector is NULL
 * @return u16 Tail of the Vector if everything is OK
*/
	u16 (*length)(Vector *vector);

/**
 * @brief Vector is empty
 * @param *Vector pointer to the Vector to know if its Empty
 * @return False if Vector is NULL
 * @return boolean True if Vector is Empty
 * @return boolean False if Vector is not Empty
*/			
	boolean (*isEmpty)(Vector *vector);

/**
 * @brief Vector is full
 * @param *Vector pointer to the Vector to know if its Full
 * @return False if Vector is NULL
 * @return boolean True if Vector is Full
 * @return boolean False if Vector is not Full
*/			
	boolean (*isFull)(Vector *vector);

	// Data queries

/**
 * @brief Returns a reference to the first element of the vector
 * @param *Vector pointer to the Vector to take the reference of its first element
 * @return NULL if Vector is NULL
 * @return NULL if Vector->Storage is NULL
 * @return *void first element of the Vector if everything is OK
*/	
	void* (*first)(Vector *vector); 

/**
 * @brief Returns a reference to the last element of the vector
 * @param *Vector pointer to the Vector to take the reference of its last element
 * @return NULL if Vector is NULL
 * @return NULL if Vector->Storage is NULL
 * @return NULL if Vector->Tail is 0
 * @return *void last element of the Vector if everything is OK
*/	
	void* (*last)(Vector *vector);

/**
 * @brief Returns a reference to the element at a given position
 * @param *Vector pointer to the Vector
 * @param u16 position position to take the element
 * @return NULL if Vector is NULL
 * @return NULL if Vector->Storage is NULL
 * @return NULL if Vector->Tail is 0
 * @return NULL if position is bigger or equal to the Tail of the Vector
 * @return *void element at a given position if everything is OK
*/	
	void* (*at)(Vector *vector, u16 position); 

	// Insertion

/**
 * @brief Inserts an element in the first position of the vector
 * @param *Vector pointer to the Vector that a data will be inserted at its first position
 * @param *void data Data that is going to be inserted in the Vector
 * @param u16 bytes size of the data
 * @return s16 kErrorCode_VectorNull if Vector is NULL
 * @return s16 kErrorCode_VectorStorageNull if Vector->Storage is NULL
 * @return s16 kErrorCode_DataNull if data is NULL
 * @return s16 kErrorCode_Zerosize if bytes is 0
 * @return s16 kErrorCode_VectorFull if Vector->Tail is equal to Vector->Capacity
 * @return s16 kErrorCode_Ok if everything is OK
*/	
	s16 (*insertFirst)(Vector *vector, void *data, u16 bytes); 

/**
 * @brief Inserts an element in the last position of the vector
 * @param *Vector pointer to the Vector that a data will be inserted at its last position
 * @param *void data Data that is going to be inserted in the Vector
 * @param u16 bytes size of the data
 * @return s16 kErrorCode_VectorNull if Vector is NULL
 * @return s16 kErrorCode_VectorStorageNull if Vector->Storage is NULL
 * @return s16 kErrorCode_DataNull if data is NULL
 * @return s16 kErrorCode_Zerosize if bytes is 0
 * @return s16 kErrorCode_VectorFull if Vector->Tail is equal to Vector->Capacity
 * @return s16 kErrorCode_Ok if everything is OK
*/	
	s16 (*insertLast)(Vector *vector, void *data, u16 bytes);

/**
 * @brief Inserts an element at the given position of the vector
 * @param *Vector pointer to the Vector that a data will be inserted at a given position
 * @param *void data Data that is going to be inserted in the Vector
 * @param u16 bytes size of the data
 * @param u16 position position to insert the element
 * @return s16 kErrorCode_VectorNull if Vector is NULL
 * @return s16 kErrorCode_VectorStorageNull if Vector->Storage is NULL
 * @return s16 kErrorCode_DataNull if data is NULL
 * @return s16 kErrorCode_Zerosize if bytes is 0
 * @return s16 kErrorCode_VectorFull if Vector->Tail is equal to Vector->Capacity
 * @return s16 kErrorCode_PositionNotAble if position is bigger than Vector->Capacity
 * @return s16 kErrorCode_Ok if everything is OK
*/	
	s16 (*insertAt)(Vector *vector, void *data, u16 bytes, u16 position); 

	// Extraction

/**
 * @brief Extracts the first element of the vector
 * @param *Vector pointer to the Vector that a data will be extracted at its first element
 * @return NULL if Vector is NULL
 * @return NULL if Vector->Capacity is 0
 * @return NULL if Vector->Tail is 0
 * @return NULL if Vector->Storage is NULL
 * @return *void first element of the Vector if everything is OK
*/	
	void* (*extractFirst)(Vector *vector); 
  /*
	// For debugging:
#if DEBUG
	void* (*extractFirst)(Vector *vector, u16 *size);
#endif // DEBUG
	void* (*extractFirst)(Vector *vector
#if DEBUG
	, u16 *size
#endif // DEBUG
		);
  */

/**
 * @brief Extracts the last element of the vector
 * @param *Vector pointer to the Vector that a data will be extracted at its last element
 * @return NULL if Vector is NULL
 * @return NULL if Vector->Capacity is 0
 * @return NULL if Vector->Tail is 0
 * @return NULL if Vector->Storage is NULL
 * @return *void last element of the Vector if everything is OK
*/	
	void* (*extractLast)(Vector *vector); 

/**
 * @brief Extracts the element of the vector at the given position
 * @param *Vector pointer to the Vector that a data will be extracted at a given position
 * @param u16 position position to extract the element
 * @return NULL if Vector is NULL
 * @return NULL if Vector->Capacity is 0
 * @return NULL if Vector->Tail is 0
 * @return NULL if Vector->Storage is NULL
 * @return *void element at a given position if everything is OK
*/	
	void* (*extractAt)(Vector *vector, u16 position);

	// Miscellaneous

/**
 * @brief Concatenates two vectors
 * @param *Vector pointer to the base Vector
 * @param *Vector pointer to the Vector to concat to the base Vector
 * @return s16 kErrorCode_VectorNull if Vector is NULL
 * @return s16 kErrorCode_VectorNull if Vector_src is NULL
 * @return s16 kErrorCode_VectorStorageNull if Vector->Storage is NULL
 * @return s16 kErrorCode_VectorStorageNull if Vector_src->Storage is NULL
 * @return s16 kErrorCode_Memory if there is not enough memory to allocate a block
 * @return s16 kErrorCode_Ok if everything is OK
*/	
	s16 (*concat)(Vector *vector, Vector *vector_src);

/**
 * @brief Calls to a function from all elements of the vector
 * @param *Vector pointer to the Vector
 * @param *void pointer to a callback from MemoryNode
 * @return s16 kErrorCode_VectorNull if Vector is NULL
 * @return s16 kErrorCode_VectorStorageNull if Vector->Stoage is NULL
 * @return s16 kErrorCode_Ok if everything is OK
*/
	s16 (*traverse)(Vector *vector, void (*callback)(MemoryNode *));

/**
 * @brief Prints the features and content of the vector
 * @param *Vector pointer to the Vector to be printed
*/
	void (*print)(Vector *vector);
};

/**
 * @brief Creates a new vector
 * @param u16 capacity of the New Vector
 * @return NULL if capacity is 0
 * @return NULL if there is not enough memory to allocate the Vector
 * @return NULL if there is not enough memory to allocate a block
 * @return *Vector if everything is OK
*/
Vector* VECTOR_create(u16 capacity); 
#endif //__ADT_VECTOR_H__
