/**
 * @file vect.hpp
 * @author tlammi (tlammi@github.com)
 * @brief Concurrent computation utilities
 * @version 0.1
 * @date 2019-05-26
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef FAL_IFAL_HPP_
#define FAL_IFAL_HPP_

#include <cstdlib>
#include <cstdint>

namespace fal {
/**
 * @brief Namespace providing utilities for concurrent computation
 *
 */
namespace vect{

/**
 * @brief Allocate memory to be used via this interface.
 *
 * Allocates the given number of element in array and returns
 * a pointer to the newly allocated array. The buffers passed to this interface
 * should be allocated by using this function to enable fastest possible
 * memory access.
 *
 * @param elems Number of elements to be alloated
 * @return Pointer to the allocated memory
 */
int32_t* allocate(size_t elems);

/**
 * @brief Deallocate previously allocated memory
 *
 * Deallocate memory previously allocated using allocate().
 * Passing pointers not allocated with allocate() are errors.
 * Likewise, failing to deallocate memory allocated by allocate()
 * is considered an error.
 *
 * @param ptr Pointer to memory to be freed and previously allocated
 *      with allocate().
 */
void deallocate(int32_t* ptr);

/**
 * @brief Elementwise add operation for two arrays
 *
 * @param inbuf1 Left operand
 * @param inbuf2 Right operand
 * @param outbuf Buffer to which the results are placed
 *      Behavior is undefined if memory addresses are shared with other arguments
 * @param elem_count Number of elements operated on. The first operated elements
 *      are placed in all buffer's first indexes and the last elements in the
 *      index elem_count-1
 * @return 0 on success, <0 on error, >0 on warning
 */
int elemwise_add(const int32_t* inbuf1, const int32_t* inbuf2, int32_t* outbuf, size_t elem_count);

/**
 * @brief Elementwise subtraction of two arrays
 *
 * @param inbuf1 Left operand
 * @param inbuf2 Right operand
 * @param outbuf Result buffer
 *      Behavior is undefined if memory addresses are shared with other arguments
 * @param elem_count Number of elements operated on counting from the start of array.
 * @return 0 on success, <0 on error, >0 on warning
 */
int elemwise_sub(const int32_t* inbuf1, const int32_t* inbuf2, int32_t* outbuf, size_t elem_count);

/**
 * @brief Elementwise multiplication of two arrays
 *
 * @param inbuf1 Left operand
 * @param inbuf2 Right operand
 * @param outbuf Result buffer
 *      Behavior is undefined if memory addresses are shared with other arguments.
 * @param elem_count Number of elements operated on counting from the start of array
 * @return 0 on success, <0 on error, >0 warning
 */
int elemwise_mul(const int32_t* inbuf1, const int32_t* inbuf2, int32_t* outbuf, size_t elem_count);

/**
 * @brief Elementwise division of two arrays
 *
 * @param inbuf1 Left operand
 * @param inbuf2 Right operand
 * @param outbuf Result buffer
 *      Behavior is undefined if memory addresses are shared with other arguments
 * @param elem_count Number of elements operated on counting from the start of arrays
 * @return 0 on success, <0 on error, >0 on warning
 */
int elemwise_div(const int32_t* inbuf1, const int32_t* inbuf2, int32_t* outbuf, size_t elem_count);

}
}
#endif  // FAL_IFAL_HPP_