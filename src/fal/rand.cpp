#include "buildcntrl.hpp"
#include "fal/rand.hpp"


#if defined(TARGET_DEV_LINUX_AMD64)
namespace fal{
namespace rand{

static uint32_t random_seed = 0;

static inline uint32_t _gen_random(){
    static uint32_t sample = random_seed;

    sample = (69069*sample + 1);
    return sample;
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
int generate_from_pdf(int32_t* ppdf_values, int32_t* ppdf_weights, size_t pdf_elem_count, int32_t* sample_buffer, size_t buffer_elem_count){
    return 0;
}
int generate_from_cpdf(int32_t* cpdf_values, int32_t* cpdf_weights, size_t cpdf_elem_count, int32_t* sample_buffer, size_t buffer_elem_count){
    return 0;
}
}
}
#elif defined(TARGET_DEV_XENOMAI_ARMHF)

#else
#pragma error "Invalid target"
#endif