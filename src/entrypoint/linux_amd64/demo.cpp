#include <iostream>
#include <filt/systemmodel.hpp>

void print_arr(const char* prefix, int32_t* arr, size_t elems){
    std::cout << prefix;
    std::cout << "[";

    for(size_t i=0; i < elems; i++){
        std::cout << arr[i];
        if(i == elems-1){
            std::cout << "]";
        }
        else {
            std::cout << ", ";
        }

    }

    std::cout << std::endl;
}

int main() {

    filt::SystemModel<int32_t, 2, 0, 3>::Config conf;

    filt::SystemModel<int32_t, 2, 0, 3> test(conf);

    int32_t buf[3];

    test.get_state(buf);
    print_arr("1: ", buf, 3);

    int32_t input_meas[] = {1, 2};
    test.step(nullptr, input_meas);

    test.get_state(buf);
    print_arr("2: ", buf, 3);

    test.step(nullptr, input_meas);
    test.get_state(buf);

    print_arr("3: ", buf, 3);

    std::cout << "Hello C++ project!" << std::endl;
}