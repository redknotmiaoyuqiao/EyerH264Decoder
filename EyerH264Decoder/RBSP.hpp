#ifndef EYERH264DEOCDER_RBSP_HPP
#define EYERH264DEOCDER_RBSP_HPP

#include <stdint.h>

class RBSP {
public:
    RBSP();
    ~RBSP();

    RBSP(const RBSP & rbsp);
    RBSP & operator = (const RBSP & rbsp);

public:
    uint8_t * buf = nullptr;
    int len = 0;
};

#endif //EYERH264DEOCDER_RBSP_HPP
