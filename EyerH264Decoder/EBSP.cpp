#include "EBSP.hpp"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

EBSP::EBSP()
{

}

EBSP::~EBSP()
{
    if(buf != nullptr){
        free(buf);
        buf = nullptr;
    }
}

EBSP::EBSP(const EBSP & ebsp)
{
    *this = ebsp;
}

EBSP & EBSP::operator = (const EBSP & ebsp)
{
    if(buf != nullptr){
        free(buf);
        buf = nullptr;
    }
    len = ebsp.len;
    buf = (uint8_t *)malloc(len);
    memcpy(buf, ebsp.buf, len);
    return *this;
}

int EBSP::GetRBSP(RBSP & rbsp)
{
    rbsp.len = len;
    rbsp.buf = (uint8_t *)malloc(rbsp.len);

    int targetIndex = 0;
    for(int i=0; i<len; i++){
        if(buf[i] == 0x03){
            // 查看前两个是不是 0x00 0x00
            if(i > 2){
                if(buf[i - 1] == 0x00 && buf[i - 2] == 0x00){
                    // 判断 后一个是不是 0 1 2 3
                    if(i < len - 1){
                        if(buf[i + 1] == 0x00 || buf[i + 1] == 0x01 || buf[i + 1] == 0x02 || buf[i + 1] == 0x03){
                            // 满足条件，该位置不进行拷贝
                            rbsp.len--;
                            continue;
                        }
                    }
                }
            }
        }
        rbsp.buf[targetIndex] = buf[i];
        targetIndex++;
    }
    return 0;
}