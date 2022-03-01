#include "Nalu.hpp"

Nalu::Nalu()
{

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
