#ifndef EYERH264DEOCDER_BITSTREAM_HPP
#define EYERH264DEOCDER_BITSTREAM_HPP

#include <stdio.h>
#include <stdint.h>

class BitStream {
public:
    /**
      * 构造函数可以传入一个 buffer，这里可以直接把 nalu 的 buffer 传入
      */
    BitStream(uint8_t * buf, int size);
    ~BitStream();

    int ReadU1();
    int ReadU(int n);
    int ReadUE();
    int ReadSE();

private:
    // 指向 buffer 开始的位置
    uint8_t * start = nullptr;

    // buffer 的长度（单位 Byte）
    int size = 0;

    // 当前读取到了哪个字节
    uint8_t * p = nullptr;

    // 当前读取到了字节中的第几位
    int bits_left = 8;
};

#endif //EYERH264DEOCDER_BITSTREAM_HPP
