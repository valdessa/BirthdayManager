// adt_memory_node.h
// Escuela Superior de Arte y Tecnologia
// Algoritmos & Inteligencia Artificial
// ESAT 2020-2021
//

#ifndef __ADT_MEMORY_NODE_H__
#define __ADT_MEMORY_NODE_H__

#include "EDK_MemoryManager/edk_platform_types.h"

// Memory Node type
typedef struct memory_node_s {
  void *data_;
  u16 size_;
  struct memory_node_ops_s *ops_;
} MemoryNode;

// Memory Node's API Declarations
struct memory_node_ops_s {
/**
 * @brief returns the data_ pointer from a memory node
 * @param *MemoryNode a pointer to the memnode whose data will be returned
 * @return NULL if the memnode from params is NULL
 * @return void* the data from the memnode from params
*/
  void*(*data) (MemoryNode *node);

/**
 * @brief sets the data of a memnode
 * @param *MemoryNode a pointer to the memnode whose data will be set
 * @param *void data to be set 
 * @param u16 bytes the size of the data to be set
 * @return s16 kErrorCode_MemNodeNull if the node pointer is NULL
 * @return s16 kErrorCode_DataNull if the pointer to the data to be set is NULL
 * @return s16 kErrorCode_Zerosize if the size from params is 0
 * @return s16 kErrorCode_Ok if the function does its job
*/  
  s16(*setData) (MemoryNode *node, void *src, u16 bytes);

/**
 * @brief returns data's size
 * @param *MemoryNode a pointer to the memnode whose size will be returned
 * @return u16 0 if the node pointer is NULL
 * @return u16 node->size_ the size of the requested node
*/  
  u16(*size) (MemoryNode *node);

/**
 * @brief release the content from the node
 * @param *MemoryNode the pointer to the memnode to reset
 * @return kErrorCode_MemNodeNull if the node pointer is NULL
 * @return kErrorCode_Ok if the function does its job
*/
  s16(*reset) (MemoryNode *node);		// reset content of memory node

/**
 * @brief empties the node without releasing memory
 * @param *MemoryNode the pointer to the memnode to soft-reset
 * @return s16 kErrorCode_MemNodeNull if the pointer to the node is NULL
 * @return s16 kErrorCode_Ok if the funtion does its job
*/
  s16(*softReset) (MemoryNode *node);		// reset content of memory node without freeing the data
  
/**
 * @brief releases the memory from the data and the node
 * @param *MemoryNode the pointer to the memnode to free
 * @return s16 kErrorCode_MemNodeNull if the pointer to the node is NULL
 * @return s16 kErrorCode_Ok if the function does its job
*/  
  s16(*free) (MemoryNode *node);		// free memory, both data and node
  
/**
 * @brief releases the node but not the data
 * @param *MemoryNode the pointer to the memnode to soft-free
 * @return s16 kErrorCode_MemNodeNull if the pointer to the node is NULL
 * @return s16 kErrorCode_Ok if the function does its job 
*/ 
  s16(*softFree) (MemoryNode *node);	// free only the node (its mmory, not its data)

/**
 * @brief sets all data to the value from param
 * @param *MemoryNode the pointer to the node to memSet
 * @param u8 value the value to be set in the entire data
 * @return s16 kErrorCode_MemNodeNull if the pointer to the memnode is NULL
 * @return s16 kErrorCode_Zerosize if the size of the memnode is 0
 * @return s16 kErrorCode_DataNull if the pointer to data from the memnode is NULL
 * @return s16 kErrorCode_Ok if the function does its job
*/
  s16(*memSet) (MemoryNode *node, u8 value);
  
/**
 * @brief copies the memory from one pointer to another
 * @param *MemoryNode the pointer to the node to copy to
 * @param *void the data to copy from
 * @param u16 bytes the size of the memory to be copied
 * @return s16 kErrorCode_MemNodeNull if the pointer to the node is NULL
 * @return s16 kErrorCode_DataNull if the data pointer is NULL
 * @return s16 kErrorCode_Zerosize if the size from params is NULL
 * @return s16 kErrorCode_DataNull if there is no size when allocating
 * @return s16 kErrorCode_Ok if the function does its job
*/
  s16(*memCopy) (MemoryNode *node, void *src, u16 bytes);

/**
 * @brief concatenates the data from two memnodes
 * @param *MemoryNode the pointer to the base node
 * @param *void the pointer to the data to concat to the base node
 * @param u16 bytes of the data to be concated
 * @return s16 kErrorCode_MemNodeNull if the pointer to the memnode is NULL
 * @return s16 kErrorCode_DataNull if the pointer to the data to concat is NULL
 * @return s16 kErrorCode_DataNull if the pointer to the data from the base node is NULL
 * @return s16 kErrorCode_DataNull if there is not enough memory to allocate a block
 * @return s16 kErrorCode_Ok if the function does its job
*/
  s16(*memConcat) (MemoryNode *node, void *src, u16 bytes);

/**
 * @brief applies a mask to the entire data from the node
 * @param *MemoryNode the pointer to the memnode
 * @param u8 the mask to apply
 * @return kErrorCode_MemNodeNull if the pointer to the node is NULL
 * @return kErrorCode_DataNull if the pointer to data from the node is NULL
 * @return kErrorCode_Ok if the function does its job
*/
  s16(*memMask) (MemoryNode *node, u8 mask);

/**
 * @brief print the information from the memnode
 * @param *MemoryNode the pointer to the node to be printed
*/
  void(*print) (MemoryNode *node);
};

/**
 * @brief Creates the memory node allocating memory
 * @return NULL if there is no memory available
 * @return *MemoryNode if there is available memory
*/
MemoryNode* MEMNODE_create();

/**
 * @brief Creates a new memory node from reference
 * @param **MemoryNode the node that will contain the memory allocated
 * @return s16 kErrorCode_Ok When the function has done its job
 * @return s16 kErrorCode_MemNodeNull when the function 
 * @return s16 kErrorCode_Memory when there is no memory available
*/
s16 MEMNODE_createFromRef(MemoryNode **node);

/**
 * @brief Inits a memory node without allocating memory
 * @param *MemoryNode a pointer to the memnode to init
 * @return s16 kErrorCode_MemNodeNull if the parameter node is NULL
 * @return s16 kErrorCode_Ok if the function
*/
s16 MEMNODE_createLite(MemoryNode *node); // Creates a memory node without memory allocation

#endif // __ADT_MEMORY_NODE_H__
