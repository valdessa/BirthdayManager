// adt_vector.c
// Escuela Superior de Arte y Tecnologia
// Algoritmos & Inteligencia Artificial
// ESAT 2020-2021
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common_def.h"
#include "adt_vector.h"

#include "EDK_MemoryManager/edk_memory_manager.h"

//Vector Declarations
static s16 VECTOR_destroy(Vector *vector);
static s16 VECTOR_softReset(Vector *vector);
static s16 VECTOR_reset(Vector *vector);
static s16 VECTOR_resize(Vector *vector, u16 new_size);
static u16 VECTOR_capacity(Vector *vector);
static u16 VECTOR_length(Vector *vector);
static boolean VECTOR_isEmpty(Vector *vector);
static boolean VECTOR_isFull(Vector *vector);
static void* VECTOR_first(Vector *vector);
static void* VECTOR_last(Vector *vector);
static void* VECTOR_at(Vector *vector, u16 position);
static s16 VECTOR_insertFirst(Vector *vector, void *data, u16 bytes);
static s16 VECTOR_insertLast(Vector* vector, void* data, u16 bytes);
static s16 VECTOR_insertAt(Vector *vector, void *data, u16 bytes, u16 position);
static void* VECTOR_extractFirst(Vector *vector);
static void* VECTOR_extractLast(Vector *vector);
static void* VECTOR_extractAt(Vector *vector, u16 position);
static s16 VECTOR_concat(Vector *vector, Vector *vector_src);
static s16 VECTOR_traverse(Vector *vector, void (*callback)(MemoryNode *));
static void VECTOR_print(Vector *vector);

//Vector API Definitions
struct vector_ops_s vector_ops = { .destroy = VECTOR_destroy,
																	 .softReset = VECTOR_softReset,
																	 .reset = VECTOR_reset,
																	 .resize = VECTOR_resize,
	                                 .capacity = VECTOR_capacity,
																	 .length = VECTOR_length,
																	 .isEmpty = VECTOR_isEmpty,
																	 .isFull = VECTOR_isFull,
																	 .first = VECTOR_first,
																	 .last = VECTOR_last,
																	 .at = VECTOR_at,
																	 .insertFirst = VECTOR_insertFirst,
	                                 .insertLast = VECTOR_insertLast,
																	 .insertAt = VECTOR_insertAt,
																	 .extractFirst = VECTOR_extractFirst,
																	 .extractLast = VECTOR_extractLast,
																	 .extractAt = VECTOR_extractAt,
																	 .concat = VECTOR_concat,
																	 .traverse = VECTOR_traverse,
																	 .print = VECTOR_print,
};


//Vector Definitions
Vector* VECTOR_create(u16 capacity) {
	if (0 == capacity) {
		return NULL;
	}

	Vector *new_vec = MM->malloc(sizeof(Vector));
	if (NULL == new_vec) {
#ifdef VERBOSE_
		printf("Error: [%s] not enough memory available\n", __FUNCTION__);
#endif
		return NULL;
	}
	new_vec->head_ = 0;
	new_vec->tail_ = 0;
	new_vec->capacity_ = capacity;
	new_vec->ops_ = &vector_ops;
	new_vec->storage_ = MM->malloc(sizeof(MemoryNode) * capacity);
	if (NULL == new_vec->storage_) {
		MM->free(new_vec);
		return NULL;
	}
	for (s16 i = 0; i < capacity; i++) {
		MEMNODE_createLite(new_vec->storage_ + i);
	}

	return new_vec;
}
 
s16 VECTOR_destroy(Vector* vector) {
	if (NULL == vector) {
		return kErrorCode_VectorNull;
	}

	if (NULL == vector->storage_) {
		MM->free(vector);
		return kErrorCode_VectorStorageNull;
	}

	for (s16 i = 0; i < vector->tail_; i++) {
		vector->storage_->ops_->reset(vector->storage_ + i);
	}

	MM->free(vector->storage_);
	MM->free(vector);

	return kErrorCode_Ok;
}

s16 VECTOR_softReset(Vector* vector) {
	if (NULL == vector) {
		return kErrorCode_VectorNull;
	}

	if (0 == vector->tail_) {
		return kErrorCode_VectorTailZero;
	}

	if (NULL == vector->storage_) {
		return kErrorCode_VectorStorageNull;
	}
	
	for (s16 i = 0; i < vector->tail_; i++) {
		vector->storage_->ops_->softReset(vector->storage_ + i);
	}

	vector->tail_ = 0;

	return kErrorCode_Ok;
}

s16 VECTOR_reset(Vector* vector) {
	if (NULL == vector) {
		return kErrorCode_VectorNull;
	}

	if (NULL == vector->storage_) {
		return kErrorCode_VectorStorageNull;
	}

	for (u16 i = 0; i < vector->tail_; i++) {
		vector->storage_->ops_->reset(vector->storage_ + i);
	}

	vector->tail_ = 0;

	return kErrorCode_Ok;
}

s16 VECTOR_resize(Vector* vector, u16 new_size) {
	if (NULL == vector) {
		return kErrorCode_VectorNull;
	}

	if (0 == new_size) {
		return kErrorCode_Zerosize;
	}

	if (new_size == vector->capacity_) {
		return kErrorCode_EqualResize;
	}

	if (NULL == vector->storage_) {
		return kErrorCode_VectorStorageNull;
	}

	MemoryNode* new_storage = MM->malloc(sizeof(MemoryNode) * new_size);
	if (NULL == new_storage) {
		return kErrorCode_Memory;
	}

	for (s16 i = 0; i < new_size; i++) {
		MEMNODE_createLite(&new_storage[i]);
	}

	if (new_size > vector->capacity_) {
		for (s16 i = 0; i < vector->capacity_; i++) {
			new_storage->ops_->setData(&new_storage[i], vector->storage_[i].data_, vector->storage_[i].size_);
		}
		MM->free(vector->storage_);
		vector->storage_ = new_storage;
		vector->capacity_ = new_size;

		return kErrorCode_Ok;
	}

	//if new_size < vector->capacity_
	for (s16 i = 0; i < new_size; i++) {
		new_storage->ops_->setData(&new_storage[i], vector->storage_[i].data_, vector->storage_[i].size_);
	}
	for (s16 i = new_size; i < vector->tail_; i++) {
		vector->storage_->ops_->reset(vector->storage_ + i);
	}
	MM->free(vector->storage_);
	if (vector->tail_ > new_size) vector->tail_ = new_size;
	vector->storage_ = new_storage;
	vector->capacity_ = new_size;

	return kErrorCode_Ok;
}

u16 VECTOR_capacity(Vector *vector) {
	if (NULL == vector) {
		return 0;
	}

	return vector->capacity_;
}

u16 VECTOR_length(Vector* vector) {
	if (NULL == vector) {
		return 0;
	}

	return vector->tail_;
}

boolean VECTOR_isEmpty(Vector* vector) {
	if (NULL == vector) {
		return False;
	}

	return (0 == vector->tail_);
}

boolean VECTOR_isFull(Vector* vector) {
	if (NULL == vector) {
		return False;
	}

	return (vector->capacity_ == vector->tail_);
}

void* VECTOR_first(Vector* vector) {
	if (NULL == vector) {
		return NULL;
	}

	if (NULL == vector->storage_) {
		return NULL;
	}

	return vector->storage_->data_;
}

void* VECTOR_last(Vector* vector) {
	if (NULL == vector) {
		return NULL;
	}

	if (NULL == vector->storage_) {
		return NULL;
	}

	if (0 == vector->tail_) {
		return NULL;
	}

	return vector->storage_[vector->tail_ - 1].data_;
}

void* VECTOR_at(Vector* vector, u16 position) {
	if (NULL == vector) {
		return NULL;
	}

	if (NULL == vector->storage_) {
		return NULL;
	}

	if (0 == vector->tail_) {
		return NULL;
	}

	if (position >= vector->tail_) {
		return NULL;
	}

	return vector->storage_[position].data_;
}

s16 VECTOR_insertFirst(Vector* vector, void *data, u16 bytes) {
	if (NULL == vector) {
		return kErrorCode_VectorNull;
	}

	if (NULL == vector->storage_) {
		return kErrorCode_VectorStorageNull;
	}

	if (NULL == data) {
		return kErrorCode_DataNull;
	}

	if (0 == bytes) {
		return kErrorCode_Zerosize;
	}

	if (vector->tail_ == vector->capacity_) {
		return kErrorCode_VectorFull;
	}

	for (s16 i = vector->tail_; i > vector->head_; i--) {
		vector->storage_[i] = vector->storage_[i - 1];
	}

	vector->storage_[0].ops_->setData(&vector->storage_[0], data, bytes);

	vector->tail_++;

	return kErrorCode_Ok;
}

s16 VECTOR_insertLast(Vector* vector, void* data, u16 bytes) {
	if (NULL == vector) {
		return kErrorCode_VectorNull;
	}

	if (NULL == vector->storage_) {
		return kErrorCode_VectorStorageNull;
	}

	if (NULL == data) {
		return kErrorCode_DataNull;
	}

	if (0 == bytes) {
		return kErrorCode_Zerosize;
	}

	if (vector->tail_ == vector->capacity_) {
		return kErrorCode_VectorFull;
	}

	vector->storage_->ops_->setData(&vector->storage_[vector->tail_], data, bytes);

	vector->tail_++;

	return kErrorCode_Ok;
}

s16 VECTOR_insertAt(Vector* vector, void* data, u16 bytes, u16 position) {
	if (NULL == vector) {
		return kErrorCode_VectorNull;
	}

	if (NULL == vector->storage_) {
		return kErrorCode_VectorStorageNull;
	}

	if (NULL == data) {
		return kErrorCode_DataNull;
	}

	if (0 == bytes) {
		return kErrorCode_Zerosize;
	}

	if (vector->tail_ == vector->capacity_) {
		return kErrorCode_VectorFull;
	}

	if (position > vector->capacity_) {
		return kErrorCode_PositionNotAble;
	}

	if (position > vector->tail_) {
		position = vector->tail_;
	}

	for (s16 i = vector->tail_; i > position; i--) {
		vector->storage_[i] = vector->storage_[i - 1];
	}

	vector->storage_->ops_->setData(&vector->storage_[position], data, bytes);

	vector->tail_++;

	return kErrorCode_Ok;
}

void* VECTOR_extractFirst(Vector* vector) {
	if (NULL == vector) {
		return NULL;
	}

	if (0 == vector->capacity_) {
		return NULL;
	}

	if (0 == vector->tail_) {
		return NULL;
	}

	if (NULL == vector->storage_) {
		return NULL;
	}

	void* aux = vector->storage_->data_;

	for (s16 i = 0; i < vector->tail_; i++) {
		vector->storage_[i] = vector->storage_[i + 1];
	}

	vector->storage_->ops_->softReset(&vector->storage_[vector->tail_ - 1]);
	
	vector->tail_--;
	return aux;
}

void* VECTOR_extractLast(Vector* vector) {
	if (NULL == vector) {
		return NULL;
	}

	if (0 == vector->capacity_) {
		return NULL;
	}

	if (0 == vector->tail_) {
		return NULL;
	}

	if (NULL == vector->storage_) {
		return NULL;
	}

	void* aux = vector->storage_[vector->tail_ - 1].data_;

	vector->storage_->ops_->softReset(&vector->storage_[vector->tail_ - 1]);

	vector->tail_--;

	return aux;
}

void* VECTOR_extractAt(Vector* vector, u16 position) {
	if (NULL == vector) {
		return NULL;
	}

	if (0 == vector->capacity_) {
		return NULL;
	}

	if (0 == vector->tail_) {
		return NULL;
	}

	if (NULL == vector->storage_) {
		return NULL;
	}

	void* aux = vector->storage_[position].data_;

	for (s16 i = position; i < vector->tail_; i++) {
		vector->storage_[i] = vector->storage_[i + 1];
	}

	vector->storage_->ops_->softReset(&vector->storage_[vector->tail_ - 1]);

	vector->tail_--;

	return aux;
}

s16 VECTOR_concat(Vector* vector, Vector* vector_src) {
	if (NULL == vector) {
		return kErrorCode_VectorNull;
	}

	if (NULL == vector_src) {
		return kErrorCode_VectorNull;
	}

	if (NULL == vector->storage_) {
		return kErrorCode_VectorStorageNull;
	}

	if (NULL == vector_src->storage_) {
		return kErrorCode_VectorStorageNull;
	}

	MemoryNode* new_storage = MM->malloc(sizeof(MemoryNode) * (vector->capacity_ + vector_src->capacity_));
	if (NULL == new_storage) {
		return kErrorCode_Memory;
	}
	for (u16 i = 0; i < (vector->capacity_ + vector_src->capacity_); i++) {
		MEMNODE_createLite(&new_storage[i]);
	}

	for (u16 i = 0; i < vector->tail_; i++) {
		new_storage->ops_->memCopy(&new_storage[i], vector->storage_[i].data_, vector->storage_[i].size_);
	}

	for (u16 i = vector->tail_; i < (vector->tail_ + vector_src->tail_); i++) {
		new_storage->ops_->memCopy(&new_storage[i], vector_src->storage_[i - vector->tail_].data_, vector_src->storage_[i - vector->tail_].size_);
	}

	for (s16 i = 0; i < vector->tail_; i++) {
		vector->storage_->ops_->reset(vector->storage_ + i);
	}
	MM->free(vector->storage_);

	vector->storage_ = new_storage;
	vector->tail_ += vector_src->tail_;
	vector->capacity_ += vector_src->capacity_;
	return kErrorCode_Ok;
}

s16 VECTOR_traverse(Vector* vector, void (*callback)(MemoryNode*)) {
	if (NULL == vector) {
		return kErrorCode_VectorNull;
	}

	if (NULL == vector->storage_) {
		return kErrorCode_VectorStorageNull;
	}

	for (u16 i = 0; i < vector->tail_; i++) {
		(*callback)(&vector->storage_[i]);
	}

	return kErrorCode_Ok;
}

void VECTOR_print(Vector* vector) {
	if (NULL != vector) {
		printf("[Vector Info] Address: %p\n", &vector);
		printf("[Vector Info] Head: %zu\n", vector->head_);
		printf("[Vector Info] Tail: %zu\n", vector->tail_);
		printf("[Vector Info] Length: %zu\n", vector->tail_);
		printf("[Vector Info] Capacity: %zu\n", vector->capacity_);
		printf("[Vector Info] Storage Address: %p\n", &vector->storage_);
		for (s16 i = 0; i < vector->tail_; i++) {
			printf(" \t[Vector Info] Storage #  % d\n", i);
			printf(" \t");
			vector->storage_[0].ops_->print(vector->storage_ + i);
			printf("\n");
		}
	} else {
		printf("[Vector Info] Adress: NULL\n");
	}
}






