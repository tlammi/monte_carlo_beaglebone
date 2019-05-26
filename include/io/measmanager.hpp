/**
 * @file measmanager.hpp
 * @author tlammi (tlammi@github.com)
 * @brief Contains a class for accessing measurements
 * @version 0.1
 * @date 2019-05-26
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef MEASMANAGER_HPP_
#define MEASMANAGER_HPP_

#include <cstdint>

#include "io/idevice.hpp"

namespace io {

/**
 * @brief Manager class for reading measurements from a device
 *
 */
class MeasManager {
 public:

    /// Number of bytes used for reading data from device (sizeof(int))
    static const size_t BUFFER_BYTES = 4;

    /**
     * @brief Construct a new Meas Manager object
     *
     * @param pdev Reference to IDevice object
     *      The ownership of the object stays on the caller.
     */
    MeasManager(IDevice* pdev);

    /**
     * @brief Destroy the Meas Manager object
     *
     */
    ~MeasManager();

    /**
     * @brief Start manager operation and claim resources needed for the operation
     *
     * Calling this method on a previously opened object counts as an error.
     *
     * @return 0 on success, <0 on error, >0 on warning
     */
    int start();

    /**
     * @brief Stop manager operation and free it's resources
     *
     * Calling this method for
     */
    void stop();

    /**
     * @brief Get measurement from a device
     *
     * start() method should have been called prior to this
     * method call. Likewise stop() call disables this method
     *
     * @param pmeas Reference to variable for storing measurement
     * @return 0 on success, <0 on error, >0 on warning
     */
    int get_measurement(int32_t* pmeas);

 private:

    IDevice* _pdev;
    uint8_t _buffer[BUFFER_BYTES];

};

}

#endif  // MEASMANAGER_HPP_
