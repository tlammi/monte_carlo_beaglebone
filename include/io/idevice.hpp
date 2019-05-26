/**
 * @file idevice.hpp
 * @author tlammi (tlammi@github.com)
 * @brief Interface definition for device
 * @version 0.1
 * @date 2019-05-26
 *
 * @copyright Copyright (c) 2019
 *
 */
#ifndef IO_IDEVICE_HPP_
#define IO_IDEVICE_HPP_

#include <cstdlib>

/**
 * @brief Input/Output namespace
 *
 * Contains entities considering input and output operations
 *
 */
namespace io {

/**
 * @brief Interface definition for a device class
 *
 */
class IDevice{
 public:

    /**
     * @brief Open the device
     *
     * This brings the device from non-operational to operational state.
     * Calling this method on an already opened object is an error.
     *
     * @param permissions Permissions used for the access. Should support
     *      the same permission settings as fopen()
     * @return 0 on success, <0 on error, >0 on warning
     */
    virtual int open(const char* permissions) = 0;

    /**
     * @brief Closes the device
     *
     * Frees the resources claimed by an object and moves the object
     * from operational to non-operational state. Calling this method
     * on a non-operational object does nothing.
     *
     */
    virtual void close() = 0;

    /**
     * @brief Write data to device
     *
     * Writes data to a previously opened device. Calling this method
     * on a non-operational device is an error.
     *
     * @param buffer Buffer from which the data is written
     * @param buf_len Lenght of data written as bytes
     * @param bytes_written Number of bytes actually written.
     * @return 0 on success, <0 on error, >0 on warning
     */
    virtual int write(const void* buffer, size_t buf_len, size_t* bytes_written) = 0;

    /**
     * @brief Read data from device
     *
     * @param buffer Buffer into which the data is stored
     * @param buf_len Max amount of bytes written to buffer
     * @param bytes_read Actual bytes read
     * @return 0 on success, <0 on error, >0 on warning
     */
    virtual int read(void* buffer, size_t buf_len, size_t* bytes_read) = 0;
};

}  // namespace io

#endif  // IO_IDEVICE_HPP_
