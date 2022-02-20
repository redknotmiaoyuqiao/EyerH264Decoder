#include "EBSP.hpp"

#include <stdlib.h>

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

int EBSP::GetRBSP(RBSP & rbsp)
{
    rbsp.len = len;
    rbsp.buf = (uint8_t *)malloc(rbsp.len);

    int targetIndex = 0;
    for(int i=0;i<len;i++){
        if(buf[i] == 0x03){
            // 查看前两个是不是 0x00 0x00
            if(i < 2){
                // 不是，直接拷贝
                rbsp.buf[targetIndex] = buf[i];
                targetIndex++;
                continue;
            }
            else {
                if(buf[i - 1] == 0x00 && buf[i - 2] == 0x00){
                    // 判断 后一个是不是 0 1 2 3
                    if(buf[i + 1] == 0x00 || buf[i + 1] == 0x01 || buf[i + 1] == 0x02 || buf[i + 1] == 0x03){

                    }
                    else {
                        rbsp.buf[targetIndex] = buf[i];
                        targetIndex++;
                        continue;
                    }
                }
                else {
                    // 不是，直接拷贝
                    rbsp.buf[targetIndex] = buf[i];
                    targetIndex++;
                    continue;
                }
            }
        }
        else {
            rbsp.buf[targetIndex] = buf[i];
            targetIndex++;
            continue;
        }
    }
    return 0;
}