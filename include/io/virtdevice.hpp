/**
 * @file virtdevice.hpp
 * @author tlammi (tlammi@github.com)
 * @brief Contains "virtual" implementation for a device class
 * @version 0.1
 * @date 2019-05-26
 *
 * @copyright Copyright (c) 2019
 *
 */
#ifndef IO_VIRTDEVICE_HPP_
#define IO_VIRTDEVICE_HPP_

#include <cstdlib>
#include <cstdio>

#include "idevice.hpp"

namespace io {

/**
 * @brief Virtual device
 *
 */
class VirtDevice:  public IDevice{
 public:
   /// Max file name length
   static const size_t FILE_NAME_MAX_LEN = 1024;

   /**
    * @brief Construct a new Virt Device object
    *
    * @param file_name Path to file used to provide emulated
    *    device data.
    */
   explicit VirtDevice(const char* file_name);
   /**
    * @brief Destroy the Virt Device object
    *
    */
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
