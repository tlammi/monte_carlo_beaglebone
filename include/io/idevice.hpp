/**
    \brief Abstract base class for devices
    Copyright 2019 tlammi
*/
#ifndef IO_IDEVICE_HPP_
#define IO_IDEVICE_HPP_

#include <cstdlib>

namespace io {
class IDevice{
 public:
    virtual int open(const char* permissions) = 0;
    virtual void close() = 0;

    virtual int write(const void* buffer, size_t buf_len, size_t* bytes_written) = 0;
    virtual int read(void* buffer, size_t buf_len, size_t* bytes_read) = 0;
};

}  // namespace io

#endif  // IO_IDEVICE_HPP_
