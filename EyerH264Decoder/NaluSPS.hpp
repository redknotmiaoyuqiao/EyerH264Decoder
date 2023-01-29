#ifndef EYERH264DEOCDER_NALUSPS_HPP
#define EYERH264DEOCDER_NALUSPS_HPP

#include "Nalu.hpp"

class NaluSPS : public Nalu
{
public:
    NaluSPS(const Nalu & nalu);
    virtual int Parse() override;
};

#endif //EYERH264DEOCDER_NALUSPS_HPP
