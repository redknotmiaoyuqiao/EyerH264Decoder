#include "RBSP.hpp"

#include <stdlib.h>
#include <string.h>

RBSP::RBSP()
{

}

RBSP::~RBSP()
{
    if(buf != nullptr){
        free(buf);
        buf = nullptr;
    }
}

RBSP::RBSP(const RBSP & rbsp)
{
    *this = rbsp;
}

RBSP & RBSP::operator = (const RBSP & rbsp)
{
    if(buf != nullptr){
        free(buf);
        buf = nullptr;
    }

    len = rbsp.len;
    buf = (uint8_t *)malloc(len);
    memcpy(buf, rbsp.buf, len);

    return *this;
}