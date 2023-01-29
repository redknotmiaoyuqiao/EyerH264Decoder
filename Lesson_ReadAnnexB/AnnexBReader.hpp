#ifndef EYERLIB_EYER_AVC_BLOG_ANNEXBREADER_HPP
#define EYERLIB_EYER_AVC_BLOG_ANNEXBREADER_HPP

#include <stdint.h>
#include <string>

#include "Nalu.hpp"

class AnnexBReader
{
public:
    AnnexBReader(const std::string & _filePath);
    ~AnnexBReader();

    // 用来打开文件
    int Open();

    // 用来关闭文件
    int Close();

    // 用来读取一个 Nalu
    int ReadNalu(Nalu & nalu);

private:
    bool CheckStartCode(int & startCodeLen, uint8_t * bufPtr, int bufLen);
    int ReadFromFile();

    std::string filePath;
    FILE * f = nullptr;

    bool isEnd = false;
    uint8_t * buffer = nullptr;
    int bufferLen = 0;
};

#endif //EYERLIB_EYER_AVC_BLOG_ANNEXBREADER_HPP