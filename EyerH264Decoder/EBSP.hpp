#ifndef EYERH264DEOCDER_EBSP_HPP
#define EYERH264DEOCDER_EBSP_HPP

#include <stdint.h>

#include "RBSP.hpp"

class EBSP {
public:
    EBSP();
    ~EBSP();

    EBSP(const EBSP & ebsp);
    EBSP & operator = (const EBSP & ebsp);

    int GetRBSP(RBSP & rbsp);

public:
    uint8_t * buf = nullptr;
    int len = 0;
};

#endif //EYERH264DEOCDER_EBSP_HPP
