
#include "buildcntrl.hpp"
#include "utils.hpp"
#include "fal/vect.hpp"



#if defined(TARGET_DEV_LINUX_AMD64)

namespace fal{
namespace vect{

static inline int32_t safe_div(int32_t left, int32_t right){
    if(unlikely(left == -2147483648 && right == -1)){
        return 2147483647;
    }
    return left / right;
}

template<class T>
T* allocate(size_t elems){
    return new T [elems];
}
template int32_t* allocate<int32_t>(size_t elems);
template int64_t* allocate<int64_t>(size_t elems);


template<class T>
void deallocate(T* ptr) {
    delete[] ptr;
}

template void deallocate<int32_t>(int32_t* ptr);
template void deallocate<int64_t>(int64_t* ptr);

int elemwise_add(const int32_t* inbuf1, const int32_t* inbuf2, int64_t* outbuf, size_t elem_count){
    for(size_t i=0; i < elem_count; i++){
        outbuf[i] = (int64_t)inbuf1[i] + inbuf2[i];
    }
    return 0;
}

int elemwise_add(int32_t scalar, const int32_t* inbuf, int64_t* outbuf, size_t elem_count){
    for(size_t i = 0; i < elem_count; i++){
        outbuf[i] = (int64_t)scalar + inbuf[i];
    }
    return 0;
}

int elemwise_sub(const int32_t* inbuf1, const int32_t* inbuf2, int64_t* outbuf, size_t elem_count){
    for(size_t i=0; i < elem_count; i++){
        outbuf[i] = (int64_t)inbuf1[i] - inbuf2[i];
    }
    return 0;
}

int elemwise_sub(int32_t scalar, const int32_t* inbuf, int64_t* outbuf, size_t elem_count){
    for(size_t i=0; i < elem_count; i++){
        outbuf[i] = (int64_t)scalar - inbuf[i];
    }
    return 0;
}
int elemwise_sub(const int32_t* inbuf, int32_t scalar, int64_t* outbuf, size_t elem_count){
    for(size_t i=0; i < elem_count; i++){
        outbuf[i] = (int64_t)inbuf[i] - scalar;
    }
    return 0;
}

int elemwise_mul(const int32_t* inbuf1, const int32_t* inbuf2, int64_t* outbuf, size_t elem_count){
    for(size_t i=0; i < elem_count; i++){
        outbuf[i] = (int64_t)inbuf1[i] * inbuf2[i];
    }
    return 0;
}

int elemwise_mul(int32_t scalar, const int32_t* inbuf, int64_t* outbuf, size_t elem_count){
    for(size_t i=0; i < elem_count; i++){
        outbuf[i] = (int64_t)scalar * inbuf[i];
    }
    return 0;
}

int elemwise_div(const int32_t* inbuf1, const int32_t* inbuf2, int32_t* outbuf, size_t elem_count){
    for(size_t i=0; i < elem_count; i++){
        outbuf[i] = safe_div(inbuf1[i], inbuf2[i]);
    }
    return 0;
}


int elemwise_div(int32_t scalar, const int32_t* inbuf, int32_t* outbuf, size_t elem_count){
    for(size_t i=0; i < elem_count; i++){
        outbuf[i] = safe_div(scalar, inbuf[i]);
    }
    return 0;
}

int elemwise_div(const int32_t* inbuf, int32_t scalar, int32_t* outbuf, size_t elem_count){
    for(size_t i=0; i<elem_count; i++){
        outbuf[i] = safe_div(inbuf[i], scalar);
    }
    return 0;
}

}
}

#elif defined(TARGET_DEV_XENOMAI_ARMHF)


#else
#pragma error "Unsupported build target"

#endif