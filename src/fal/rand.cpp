#include "buildcntrl.hpp"
#include "fal/rand.hpp"

#ifndef max
#define max(a, b) ((a) > (b) ? (a) : (b))
#endif

#if defined(TARGET_DEV_LINUX_AMD64)
namespace fal{
namespace rand{

static uint32_t random_seed = 0;

static inline uint32_t _gen_random(){
    static uint32_t sample = random_seed;

    sample = (69069*sample + 1);
    return sample;
}

static int32_t* binary_search(int32_t searched_value, int32_t* buffer_start, int32_t* buffer_end){
#pragma message("TODO: Implement binary_search().")
    int32_t* ptr;
    for(ptr=buffer_start; ptr <= buffer_end-1; ptr++){
        if(*ptr == searched_value) return ptr;
        if(*ptr < searched_value && *(ptr+1) > searched_value) return ptr;
    }
    if(*buffer_start > searched_value) return buffer_start;
    if(*buffer_end == searched_value) return buffer_end;

    return nullptr;
}

int init(){
    random_seed = 0;
}
int generate_uniform(const int32_t uniform_start, const int32_t uniform_end, int32_t* sample_buffer, const size_t buffer_elem_count){
    for(size_t i=0; i < buffer_elem_count; i++){
        uint32_t sample = _gen_random();
        // Fit the sample to the wanted range
        sample = sample % (uniform_end - uniform_start);
        // Offset by start of the uniform distribution
        sample_buffer[i] = sample + uniform_start;

    }
    return 0;
}

int generate_from_cpdf(int32_t* cpdf_values, int32_t* cpdf_weights, const size_t cpdf_elem_count, int32_t* sample_buffer, const size_t buffer_elem_count){
    int res = generate_uniform(0, cpdf_weights[cpdf_elem_count-1], sample_buffer, buffer_elem_count);
    if(res != 0) return res;

    for(size_t i=0; i < buffer_elem_count; i++){
        int32_t* ptr = binary_search(sample_buffer[i], cpdf_weights, &cpdf_weights[cpdf_elem_count-1]);
        sample_buffer[i] = cpdf_values[ptr-cpdf_weights];
    }

    return 0;
}

int multiply_pdfs(const int32_t* x_values, int32_t* x_weights,
                  const int32_t* y_values, const int32_t* y_weights,
                  size_t x_elem_count, size_t y_elem_count){

    size_t y_low_index = 0;
    size_t y_high_index = 1;
    size_t x_index = 0;

    if(y_elem_count == 1){
        return -1;
    }

    for(; x_index < x_elem_count; x_index++){
        if(x_values[x_index] > y_values[y_high_index] &&
            y_high_index < y_elem_count-1){

            y_low_index++;
            y_high_index++;
        }

        x_weights[x_index] *= max(
            (y_weights[y_high_index] - y_weights[y_low_index])*
            (x_values[x_index]-y_values[y_low_index]) /
            (y_values[y_high_index]-y_values[y_low_index]) +
            y_weights[y_low_index],
            0
        );
    }

    return 0;

}
}
}
#elif defined(TARGET_DEV_XENOMAI_ARMHF)

#else
#pragma error "Invalid target"
#endif