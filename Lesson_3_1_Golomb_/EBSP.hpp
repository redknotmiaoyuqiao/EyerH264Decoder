#ifndef EYERH264DEOCDER_EBSP_HPP
#define EYERH264DEOCDER_EBSP_HPP

#include <stdint.h>

#include "RBSP.hpp"

class EBSP {
public:
    EBSP();
    ~EBSP();

    int GetRBSP(RBSP & rbsp);

public:
    uint8_t * buf = nullptr;
    int len = 0;
};

#endif //EYERH264DEOCDER_EBSP_HPP
