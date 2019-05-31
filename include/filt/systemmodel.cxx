#include "filt/systemmodel.hpp"



namespace filt {

#define TEMPLATE_DEF template<class T, size_t input_count, size_t output_count, size_t state_count>

#define TEMPLATE_USE T, input_count, output_count, state_count

TEMPLATE_DEF
SystemModel<TEMPLATE_USE>::Config::Config():
    x_to_x_func{nullptr},
    x_to_y_func{nullptr},
    psysnoise_values{nullptr},
    psysnoise_weights{nullptr},
    pmeasnoise_values{nullptr},
    pmeasnoise_weights{nullptr}{

}

TEMPLATE_DEF
SystemModel<TEMPLATE_USE>::~SystemModel(){

}

TEMPLATE_DEF
SystemModel<TEMPLATE_USE>::SystemModel(Config config):
_config{config}, _state{} {

    for(size_t i=0; i<state_count; i++){
        this->_state[i] = 0;
    }

}

TEMPLATE_DEF
void SystemModel<TEMPLATE_USE>::step(const T* output_meas, const T* input_meas){
    (void) output_meas;

    for(size_t i=0; i<state_count; i++){
        for(size_t j=0; j<input_count; j++){
            this->_state[i] += input_meas[j];
        }
    }
}

TEMPLATE_DEF
void SystemModel<TEMPLATE_USE>::get_state(T* state_buf){
    for(size_t i=0; i<state_count; i++){
        state_buf[i] = this->_state[i];
    }
}

TEMPLATE_DEF
void SystemModel<TEMPLATE_USE>::set_state(T* state_buf){
    for(size_t i=0; i<state_count; i++){
        this->_state[i] = state_buf[i];
    }
}


#undef TEMPLATE_DEF
#undef TEMPLATE_USE

}