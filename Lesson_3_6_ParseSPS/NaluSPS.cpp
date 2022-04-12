#include "NaluSPS.hpp"

#include "BitStream.hpp"

NaluSPS::NaluSPS(const Nalu & nalu)
    : Nalu(nalu)
{

}

int NaluSPS::Parse()
{
    uint8_t * buf   = rbsp.buf;
    int bufLen      = rbsp.len;

    BitStream bitStream(buf + 1, bufLen - 1);

    profile_idc = bitStream.ReadU(8);
    printf("profile_idc: %d\n", profile_idc);

    return 0;
}