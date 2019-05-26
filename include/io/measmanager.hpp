/**
    \brief Class for accessing measurements from the application

    Copyright 2019 tlammi
*/

#ifndef MEASMANAGER_HPP_
#define MEASMANAGER_HPP_

#include <cstdint>

#include "io/idevice.hpp"

namespace io {

class MeasManager {
 public:
    static const size_t BUFFER_BYTES = 4;

    MeasManager(IDevice* pdev);
    ~MeasManager();

    int start();
    void stop();

    int get_measurement(int32_t* pmeas);

 private:
    IDevice* _pdev;
    uint8_t _buffer[BUFFER_BYTES];

};

}

#endif  // MEASMANAGER_HPP_
