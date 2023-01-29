#ifndef EYERH264DEOCDER_NALU_HPP
#define EYERH264DEOCDER_NALU_HPP

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "EBSP.hpp"

class Nalu {
public:
    Nalu();
    Nalu(const Nalu & nalu);
    ~Nalu();

    Nalu & operator = (const Nalu & nalu);

    int SetBuf(uint8_t * _buf, int _len);

    int GetEBSP(EBSP & ebsp);

    int ParseRBSP();
    int ParseHeader();

    int GetNaluType();

    virtual int Parse();

public:
    uint8_t * buf = nullptr;
    int len = 0;
    int startCodeLen = 0;

    RBSP rbsp;

    int forbidden_bit = 0;
    int nal_ref_idc = 0;
    int nal_unit_type = 0;
};

#endif //EYERH264DEOCDER_NALU_HPP
