#include <cstring>
#include <errno.h>

#include "io/virtdevice.hpp"

namespace io {
    VirtDevice::VirtDevice(const char* file_name):
    _file_name({0}) {

        strncpy(this->_file_name, file_name, VirtDevice::FILE_NAME_MAX_LEN);
        this->_file_name[VirtDevice::FILE_NAME_MAX_LEN-1] = '\0';

    }

    VirtDevice::~VirtDevice(){

    }

    int VirtDevice::open(const char* permissions){
        int retval = 0;
        this->_handle = fopen(this->_file_name, permissions);
        if(this->_handle == nullptr){
            retval = -errno;
        }
        return retval;
    }

    void VirtDevice::close(){
        fclose(this->_handle);
    }

    int VirtDevice::write(const void* buffer, size_t buf_len, size_t* bytes_written){
        *bytes_written = fwrite(buffer, 1, buf_len, this->_handle);

        if(*bytes_written != buf_len){
            return -errno;
        }
        return 0;
    }

    int VirtDevice::read(void* buffer, size_t buf_len, size_t* bytes_read){
        *bytes_read = fread(buffer, 1, buf_len, this->_handle);
        if(*bytes_read != buf_len){
            if(feof(this->_handle)){
                return 1;
            }

            return -ferror(this->_handle);
        }

        return 0;
    }
}