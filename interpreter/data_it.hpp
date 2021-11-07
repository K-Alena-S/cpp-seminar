#ifndef DATA_IT_H
#define DATA_IT_H

#include <cstdlib>
#include <array>
#include "interpreter_error.hpp"

class data_it {
 public:    
    uint8_t & operator*() {
        return *_it;
    }

    data_it & operator++() {
        if (_it == _data.end()) throw interpreter_error("out of bounds: cannot access element after last");
        ++_it;
        return *this; 
    }

    data_it & operator--() {
        if (_it == _data.begin()) throw interpreter_error("out of bounds: cannot access element before first");
        --_it;
        return *this;
    }
 private:
    std::array<uint8_t, 100> _data = {};
    std::array<uint8_t, 100>::iterator _it = _data.begin();
};

#endif