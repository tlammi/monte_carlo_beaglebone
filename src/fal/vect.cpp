#include "buildcntrl.hpp"

#include "fal/vect.hpp"


#if defined(TARGET_DEV_LINUX_AMD64)

namespace fal{
namespace vect{
int32_t* allocate(size_t elems){
    return new int32_t [elems];
}

void deallocate(int32_t* ptr) {
    delete[] ptr;
}

int elemvise_add(int32_t* inbuf1, int32_t* inbuf2, int32_t* outbuf, size_t elem_count){
    for(size_t i=0; i < elem_count; i++){
        outbuf[i] = inbuf1[i] + inbuf2[i];
    }
    return 0;
}

int elemvise_sub(int32_t* inbuf1, int32_t* inbuf2, int32_t* outbuf, size_t elem_count){
    for(size_t i=0; i < elem_count; i++){
        outbuf[i] = inbuf1[i] - inbuf2[i];
    }
    return 0;
}

int elemvise_mul(int32_t* inbuf1, int32_t* inbuf2, int32_t* outbuf, size_t elem_count){
    for(size_t i=0; i < elem_count; i++){
        outbuf[i] = inbuf1[i] * inbuf2[i];
    }
    return 0;
}

int elemvise_div(int32_t* inbuf1, int32_t* inbuf2, int32_t* outbuf, size_t elem_count){
    for(size_t i=0; i < elem_count; i++){
        outbuf[i] = inbuf1[i] / inbuf2[i];
    }
    return 0;
}
}
}

#elif defined(TARGET_DEV_XENOMAI_ARMHF)


#else
#pragma error "Unsupported build target"

#endif