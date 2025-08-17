// adt_memory_node.c
// Escuela Superior de Arte y Tecnologia
// Algoritmos & Inteligencia Artificial
// ESAT 2020-2021
//

#include <stdio.h>
#include <stdlib.h>

#include "common_def.h"
#include "adt_memory_node.h"

#include "EDK_MemoryManager/edk_memory_manager.h"


// Memory Node Declarations
static s16 MEMNODE_initWithoutCheck(MemoryNode *node);	// inits a MN with no checks
static void* MEMNODE_data(MemoryNode *node);	// returns a reference to data_
static u16 MEMNODE_size(MemoryNode *node);		// returns data size
static s16 MEMNODE_setData(MemoryNode* node, void* src, u16 bytes);
static s16 MEMNODE_reset(MemoryNode* node);
static s16 MEMNODE_softReset(MemoryNode* node);
static s16 MEMNODE_free(MemoryNode* node);
static s16 MEMNODE_softFree(MemoryNode* node);
static s16 MEMNODE_memSet(MemoryNode* node, u8 value);
static s16 MEMNODE_memCopy(MemoryNode* node, void* src, u16 bytes);
static s16 MEMNODE_memConcat(MemoryNode* node, void* src, u16 bytes);
static s16 MEMNODE_memMask(MemoryNode* node, u8 mask);
static void print(MemoryNode* node);

// Memory Node's API Definitions
struct memory_node_ops_s memory_node_ops = { .data = MEMNODE_data,
                                             .size = MEMNODE_size,
                                             .setData = MEMNODE_setData,
                                             .reset = MEMNODE_reset,
                                             .softReset = MEMNODE_softReset,
                                             .free = MEMNODE_free,
                                             .softFree = MEMNODE_softFree,
                                             .memSet = MEMNODE_memSet,
                                             .memCopy = MEMNODE_memCopy,
                                             .memConcat = MEMNODE_memConcat,
                                             .memMask = MEMNODE_memMask,
                                             .print = print,
};

// Memory Node Definitions
MemoryNode* MEMNODE_create() {
  MemoryNode *node = MM->malloc(sizeof(MemoryNode));
  if (NULL == node) {
#ifdef VERBOSE_
    printf("Error: [%s] not enough memory available\n", __FUNCTION__);
#endif
    return NULL;
  }
  MEMNODE_initWithoutCheck(node);
  return node;
}

s16 MEMNODE_createFromRef(MemoryNode **node) {
  if (NULL == node) {
    return kErrorCode_MemNodeNull;
  }
  *node = MEMNODE_create();
  if (NULL == *node) {
#ifdef VERBOSE_
    printf("Error: [%s] not enough memory available\n", __FUNCTION__);
#endif
    return kErrorCode_Memory;
  }
  return kErrorCode_Ok;
}

s16 MEMNODE_createLite(MemoryNode* node) {
  if (NULL == node) {
    return kErrorCode_MemNodeNull;
  }

  MEMNODE_initWithoutCheck(node);

  return kErrorCode_Ok;
}


s16 MEMNODE_initWithoutCheck(MemoryNode *node) {
  node->data_ = NULL;
  node->size_ = 0;
  node->ops_ = &memory_node_ops;
  return kErrorCode_Ok;
}

void* MEMNODE_data(MemoryNode *node) { // returns a reference to data_
  if (NULL == node) {
    return NULL;
  }

  return node->data_;
}

s16 MEMNODE_setData(MemoryNode* node, void* src, u16 bytes) { //esto es un setter
  if (NULL == node) {
    return kErrorCode_MemNodeNull;
  }

  if (NULL == src){
    return kErrorCode_DataNull;
  }

  if (0 == bytes) {
    return kErrorCode_Zerosize;
  }

  node->data_ = src;
  node->size_ = bytes;

  return kErrorCode_Ok;
}

u16	MEMNODE_size(MemoryNode *node) { // returns data size
  if (NULL == node) {
    return 0;
  }

  return node->size_;
}

s16 MEMNODE_reset(MemoryNode* node) {
  if (NULL == node) {
    return kErrorCode_MemNodeNull;
  }

  if (NULL != node->data_) {
    MM->free(node->data_);
    node->data_ = NULL;
  }

  node->size_ = 0;

  return kErrorCode_Ok;
}

s16 MEMNODE_softReset(MemoryNode* node) {
  if (NULL == node) {
    return kErrorCode_MemNodeNull;
  }

  node->data_ = NULL;

  node->size_ = 0;

  return kErrorCode_Ok;
}

s16 MEMNODE_free(MemoryNode *node) {
  if (NULL == node) {
    return kErrorCode_MemNodeNull;
  }

  if (NULL != node->data_) {
    MM->free(node->data_);
  }

  MM->free(node);
  node = NULL;

  return kErrorCode_Ok;
}

s16 MEMNODE_softFree(MemoryNode *node) {
  if (NULL == node) {
    return kErrorCode_MemNodeNull;
  }
  
  MM->free(node);
  node = NULL;

  return kErrorCode_Ok;
}

s16 MEMNODE_memSet(MemoryNode *node, u8 value) {
  if (NULL == node) {
    return kErrorCode_MemNodeNull;
  }

  if (0 == node->size_) {
    return kErrorCode_Zerosize;
  }

  if (NULL == node->data_) {
    return kErrorCode_DataNull;
  }

  for (u8 i = 0; i < node->size_; ++i) {
    *((u8*)node->data_ + i) = value;
  }

  return kErrorCode_Ok;
}

s16 MEMNODE_memCopy(MemoryNode* node, void* src, u16 bytes) {
  if (NULL == node) {
    return kErrorCode_MemNodeNull;
  }

  if (NULL == src) {
    return kErrorCode_DataNull;
  }

  if (0 == bytes) {
    return kErrorCode_Zerosize;
  }

  node->size_ = bytes;
  u8* tmp_data = (u8*) MM->malloc(sizeof(u8) * node->size_);

  if (NULL == tmp_data) {
    return kErrorCode_DataNull;
  }

  for (u8 i = 0; i < node->size_; ++i) {
    *(tmp_data + i) = *((u8*)src + i);
  }
  if (NULL != node->data_) {
    MM->free(node->data_);
  }
  node->data_ = tmp_data;
  
  return kErrorCode_Ok;
}

s16 MEMNODE_memConcat(MemoryNode* node, void* src, u16 bytes) {
  if (NULL == node) {
    return kErrorCode_MemNodeNull;
  }

  if (NULL == src) {
    return kErrorCode_DataNull;
  }

  if (NULL == node->data_) {
    return kErrorCode_DataNull;
  }

  u16 aux_size = node->size_;
  node->size_ += bytes;

  u8* tmp_data = (u8*) MM->malloc(sizeof(u8) * node->size_);
  if (NULL == tmp_data) {
    return kErrorCode_DataNull;
  }
  for (u8 i = 0; i < aux_size; ++i) {
    *(tmp_data + i) = *((u8*)node->data_ + i);
  }

  for (u8 i = 0; i < bytes; ++i) {
    *(tmp_data + i + aux_size) = *((u8*)src + i);
  }

  MM->free(node->data_);
  node->data_ = tmp_data;

  return kErrorCode_Ok;
}

s16 MEMNODE_memMask(MemoryNode* node, u8 mask) {
  if (NULL == node) {
    return kErrorCode_MemNodeNull;
  }

  if (NULL == node->data_) {
    return kErrorCode_DataNull;
  }

  for (u8 i = 0; i < node->size_; i++) {
    *((u8*)node->data_ + i) &= mask;
  }

  return kErrorCode_Ok;
}

void print(MemoryNode* node) {
  printf(" \t[Node Info] Node address = %p\n", node);
  if (NULL != node) {
    printf(" \t\t[Node Info] Node size: %zu\n", node->size_);
    printf(" \t\t[Node Info] Data address = %p\n", node->data_);
    printf(" \t\t[Node Info] Data content = ");
    for (u8 i = 0; i < node->size_; ++i) {
      printf("%c", *((u8*)node->data_ + i));
    }
    printf("\n");
  } else {
    printf(" \t\t[Node Info] Data address = NULL\n");
    printf(" \t\t[Node Info] Data content = NULL\n");
  }
}

