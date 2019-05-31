/**
 * @file systemmodel.hpp
 * @author tlammi (you@domain.com)
 * @brief SystemModel class definition
 * @version 0.1
 * @date 2019-05-30
 *
 * @copyright Copyright (c) 2019
 *
 */


#ifndef FILT_SYSTEMMODEL_HPP_
#define FILT_SYSTEMMODEL_HPP_

#include <cstdlib>

/**
 * @brief Filtering namespace
 *
 * This namespace offers functionality of filtering a system state.
 *
 */
namespace filt{

/**
 * @brief Class representing a system
 *
 *
 * @tparam T Data type used for system states
 */
template<class T, size_t input_count, size_t output_count, size_t state_count>
class SystemModel{
 public:

    /**
     * @brief Function type used for describing system functionality
     *
     * The function type is used for both f() and g() in model:
     * x(t+1) = f(x, u, t) + v(t)
     * y(t) = g(x, u, t) + e(t)
     * where:
     *  x - system state
     *  y - system output
     *  u - system input
     *  t - time
     *  f - state propagation function
     *  g - state to output function
     *
     * Arguments:
     *  reference to current state (x(t))
     *  reference to current input (u(t))
     *  reference to buffer where the result is to be placed
     */
    typedef void (*system_func)(const T*, const T*, T*);

    /**
     * @brief SystemModel configuration
     *
     * Populated by the caller and passed to SystemModel object
     * to configure the object.
     *
     * All fields present in this struct should be allocated by the caller.
     * The fields should also not be modified outside of the object using
     * the config after it has been passed to constructor.
     *
     */
    struct Config {

        /**
         * @brief Construct a new Config object with default values
         *
         */
        Config();

        system_func x_to_x_func;  ///< Pointer to state propagation function
        system_func x_to_y_func;  ///< Pointer to state to output function

        /**
         * @brief Pointer to array of sys noise approx p.d.f.
         *
         * This field is used in system noise model.
         * Values stored in this array represent x-axis values of p.d.f.
         * The respective weights of all values are stored in psysnoise_weights
         *
         */
        int32_t* psysnoise_values;

        /**
         * @brief Pointer to array of sys noise approx histogram weights
         *
         * This field is used in system noise model.
         * Values stored in this array represent y-axis values of p.d.f.
         * The respective sample values are stored in psysnoise_values.
         */
        int32_t* psysnoise_weights;

        /**
         * @brief Number of samples in system noise model
         *
         * This many samples are expected from the sytem noise model arrays.
         *
         */
        size_t sysnoise_sample_count;

        /**
         * @brief Pointer to array of meas noise approx histogram values
         *
         * This field is used in measurement noise model.
         * The values stored here are x-axis values of numeric p.d.f.
         * The respective weights are stored in pmeasnoise_weights.
         */
        int32_t* pmeasnoise_values;

        /**
         * @brief Pointer to array of meas noise approx histogram weights
         *
         * This field is used for measurement noise model.
         * The values stored in here are y-axis values of numeric p.d.f.
         * The respective sample values are stored in pmeasnoise_values.
         */
        int32_t* pmeasnoise_weights;

        /**
         * @brief Number of samples in measurement noise model
         *
         * This many samples are expected from the system noise model arrays.
         */
        size_t measnoise_sample_count;

    };

    /**
     * @brief Construct a new System Model object
     *
     * @param pconfig Configuration of the system
     */
    SystemModel(Config config);
    ~SystemModel();

    void step(const T* output_meas, const T* input_meas);

    inline void get_state(T* state_buf);
    inline void set_state(T* state_buf);




 private:
    Config _config;

    T _state[state_count];
};

}

#include "filt/systemmodel.cxx"

#endif  // FILT_SYSTEMMODEL_HPP_
