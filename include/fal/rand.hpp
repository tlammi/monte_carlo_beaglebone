/**
 * @file rand.hpp
 * @author tlammi (tlammi@github.com)
 * @brief Firmware access for random value generation
 * @version 0.1
 * @date 2019-05-26
 *
 * @copyright Copyright (c) 2019
 *
*/

#ifndef FAL_RAND_HPP_
#define FAL_RAND_HPP_

#include <cstdint>
#include <cstdlib>

/**
 * @brief Firmware Access Layer
 *
 * Abstracts the underlying implementation from the application
 *
 */
namespace fal{
/**
 * @brief Random value utilities
 *
 * Namespace used for working with random numbers on low level
 * of abstraction.
 *
 */
namespace rand{
/**
 * \brief Initialize the random interface
*/
int init();

/**
 * @brief Generate random values from uniform distribution
 *
 * Generates random samples from uniform distribution in range [start, end).
 * The function does not perform error checks so it's the user's responsibility
 * to verify that correct values are passed.
 *
 * @param Uniform distribution lower limit
 * @param Uniform distribution uppoer limit
 * @param Buffer into which the samples will be stored
 * @param Number of elements to generate
 *
 * @return 0 upon success, >0 on warning, <0 on error
 *
 */
int generate_uniform(const int32_t uniform_start, const int32_t uniform_end, int32_t* sample_buffer, const size_t buffer_elem_count);

/**
 * @brief Generates random values from cumulative pdf
 *
 * Generates random samples with profile described by the given CPDF.
 * The function does not perform error checks so it's the user's reponsibility
 * to verify that correct values are passed.
 *
 * @param CPDF values (x-axis). Should be in ascending order
 * @param CPDF weights (y-axis). Should be in ascending order.
 *      The weights correspond to CPDF values stored in the corresponding indexes.
 * @param Number of elements in the first two parameters
 * @param Buffer for storing the resulting values
 * @param Number of elements to generate
 *
 * @return 0 upon success, >0 on warning, <0 on error
 *
 */
int generate_from_cpdf(int32_t* cpdf_values, int32_t* cpdf_weights, size_t cpdf_elem_count, int32_t* sample_buffer, const size_t buffer_elem_count);

}
}

#endif  // FAL_RAND_HPP_