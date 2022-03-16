#include "Nalu.hpp"

Nalu::Nalu()
{

}

Nalu::Nalu(const Nalu & nalu)
{
    *this = nalu;
}

Nalu & Nalu::operator = (const Nalu & nalu)
{
    if(buf != nullptr){
        free(buf);
        buf = nullptr;
    }

    startCodeLen = nalu.startCodeLen;
    len = nalu.len;
    buf = (uint8_t *)malloc(len);
    memcpy(buf, nalu.buf, len);

    forbidden_bit   = nalu.forbidden_bit;
    nal_ref_idc     = nalu.nal_ref_idc;
    nal_unit_type   = nalu.nal_unit_type;

    rbsp = nalu.rbsp;

    return *this;
}

Nalu::~Nalu()
{
    if(buf != nullptr){
        free(buf);
        buf = nullptr;
    }
}

int Nalu::SetBuf(uint8_t * _buf, int _len)
{
    if(buf != nullptr){
        free(buf);
        buf = nullptr;
    }
    len = _len;

    buf = (uint8_t *)malloc(len);
    memcpy(buf, _buf, len);

    return 0;
}

int Nalu::GetEBSP(EBSP & ebsp)
{
    ebsp.len = len - startCodeLen;
    ebsp.buf = (uint8_t *)malloc(ebsp.len);

    memcpy(ebsp.buf, buf + startCodeLen, ebsp.len);

    return 0;
}

int Nalu::ParseRBSP()
{
    EBSP ebsp;
    int ret = GetEBSP(ebsp);
    if(ret){
        return -1;
    }

    // 此处的 rbsp 是成员变量
    return ebsp.GetRBSP(rbsp);
}

int Nalu::ParseHeader()
{
    uint8_t naluHead    = rbsp.buf[0];
    forbidden_bit       = (naluHead >> 7) & 1;
    nal_ref_idc         = (naluHead >> 5) & 3;
    nal_unit_type       = (naluHead >> 0) & 0x1f;
    return 0;
}

int Nalu::GetNaluType()
{
    return nal_unit_type;
}

int Nalu::Parse()
{
    return 0;
}
