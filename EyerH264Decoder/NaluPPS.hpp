#ifndef EYERH264DEOCDER_NALUPPS_HPP
#define EYERH264DEOCDER_NALUPPS_HPP

#include "Nalu.hpp"

class NaluPPS : public Nalu
{
public:
    NaluPPS(const Nalu & nalu);
    virtual int Parse() override;
};

#endif //EYERH264DEOCDER_NALUPPS_HPP
