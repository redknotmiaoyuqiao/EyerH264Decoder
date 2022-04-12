#ifndef EYERH264DEOCDER_NALUSPS_HPP
#define EYERH264DEOCDER_NALUSPS_HPP

#include "Nalu.hpp"

class NaluSPS : public Nalu
{
public:
    NaluSPS(const Nalu & nalu);
    virtual int Parse() override;

    int profile_idc = 0;
};

#endif //EYERH264DEOCDER_NALUSPS_HPP
