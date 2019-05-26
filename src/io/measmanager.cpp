/// Copyright 2019 tlammi

#include "io/measmanager.hpp"

namespace io {
MeasManager::MeasManager(IDevice* pdev):
    _pdev{pdev},
    _buffer{} {

}
MeasManager::~MeasManager(){

}

int MeasManager::start(){
    return this->_pdev->open("r");
}

void MeasManager::stop(){
    this->_pdev->close();
}

int MeasManager::get_measurement(int32_t* pmeas){
    size_t read_bytes = 0;
    this->_pdev->read(pmeas, sizeof(*pmeas), &read_bytes);
    if(read_bytes < sizeof(*pmeas)){
        return 1;
    }
    return 0;
}

}
