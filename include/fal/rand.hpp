#ifndef FAL_RAND_HPP_
#define FAL_RAND_HPP_

#include <cstdint>
#include <cstdlib>

namespace fal{
namespace rand{
int init();

int generate_uniform(const int32_t uniform_start, const int32_t uniform_end, int32_t* sample_buffer, const size_t buffer_elem_count);
int generate_from_cpdf(int32_t* cpdf_values, int32_t* cpdf_weights, size_t cpdf_elem_count, int32_t* sample_buffer, const size_t buffer_elem_count);

}
}

#endif  // FAL_RAND_HPP_