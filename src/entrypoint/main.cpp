#include <iostream>
#include <io/virtdevice.hpp>

int main() {

    io::VirtDevice dev("/hello/world");
    std::cout << "Hello C++ project!" << std::endl;
}