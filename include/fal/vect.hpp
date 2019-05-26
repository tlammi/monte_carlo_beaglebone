#ifndef FAL_IFAL_HPP_
#define FAL_IFAL_HPP_

#include <cstdlib>
#include <cstdint>

namespace fal {
namespace vect{
int32_t* allocate(size_t elems);
void deallocate(int32_t* ptr);

int elemvise_add(int32_t* inbuf1, int32_t* inbuf2, int32_t* outbuf, size_t elem_count);
int elemvise_sub(int32_t* inbuf1, int32_t* inbuf2, int32_t* outbuf, size_t elem_count);
int elemvise_mul(int32_t* inbuf1, int32_t* inbuf2, int32_t* outbuf, size_t elem_count);
int elemvise_div(int32_t* inbuf1, int32_t* inbuf2, int32_t* outbuf, size_t elem_count);
}
}
#endif  // FAL_IFAL_HPP_