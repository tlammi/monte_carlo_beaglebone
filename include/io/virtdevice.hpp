/**
 *
 * Copyright 2019 tlammi
*/

#ifndef IO_VIRTDEVICE_HPP_
#define IO_VIRTDEVICE_HPP_

#include <cstdlib>
#include <cstdio>

#include "idevice.hpp"

namespace io {
class VirtDevice:  public IDevice{
 public:
    static const size_t FILE_NAME_MAX_LEN = 1024;

    explicit VirtDevice(const char* file_name);
    ~VirtDevice();

    int open(const char* permissions);
    void close();

    int write(const void* buffer, size_t buf_len, size_t* bytes_written);
    int read(void* buffer, size_t buf_len, size_t* bytes_read);
 private:
    char _file_name[FILE_NAME_MAX_LEN];
    FILE* _handle;
};

}  // namespace io


#endif  // IO_VIRTDEVICE_HPP_
