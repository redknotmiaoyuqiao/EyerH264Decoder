#include "BitStream.hpp"

BitStream::BitStream(uint8_t * _buf, int _size)
{
    start = _buf;
    p = _buf;
    size = _size;
    bits_left = 8;
}

BitStream::~BitStream()
{

}

int BitStream::ReadU1()
{
    int r = 0;
    bits_left--;
    r = ((*(p)) >> bits_left) & 0x01;
    if (bits_left == 0) {
        p++;
        bits_left = 8;
    }
    return r;
}

int BitStream::ReadU(int n)
{
    int r = 0;
    int i;
    for (i = 0; i < n; i++) {
        r |= ( ReadU1() << ( n - i - 1 ) );
    }
    return r;
}

int BitStream::ReadUE()
{
    int r = 0;
    int i = 0;
    while((ReadU1() == 0) && (i < 32)){
        i++;
    }
    r = ReadU(i);
    r += (1 << i) - 1;
    return r;
}

int BitStream::ReadSE()
{
    int r = ReadUE();
    if (r & 0x01) {
        r = (r+1)/2;
    }
    else {
        r = -(r/2);
    }
    return r;
}