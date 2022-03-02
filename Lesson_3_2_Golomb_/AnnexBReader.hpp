#ifndef EYERLIB_EYER_AVC_BLOG_ANNEXBREADER_HPP
#define EYERLIB_EYER_AVC_BLOG_ANNEXBREADER_HPP

#include <stdint.h>
#include <string>

class AnnexBReader
{
public:
    AnnexBReader(std::string & _filePath);
    ~AnnexBReader();

    // 用来打开文件
    int Open();

    // 用来关闭文件
    int Close();

    // 用来读取一个 Nalu 文件
    int ReadNalu(uint8_t * data, int * dataLen, int * startcodeLen);

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