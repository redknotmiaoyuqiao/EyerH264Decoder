#ifndef EYERH264DEOCDER_NALU_HPP
#define EYERH264DEOCDER_NALU_HPP

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

class Nalu {
public:
    Nalu();
    ~Nalu();

    int SetBuf(uint8_t * _buf, int _len);

public:
    uint8_t * buf = nullptr;
    int len = 0;
    int startCodeLen = 0;
};

#endif //EYERH264DEOCDER_NALU_HPP
