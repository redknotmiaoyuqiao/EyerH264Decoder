#include "AnnexBReader.hpp"

AnnexBReader::AnnexBReader(const std::string & _filePath)
{
    filePath = _filePath;
}

AnnexBReader::~AnnexBReader()
{
    Close();
}

// 用来打开文件
int AnnexBReader::Open()
{
    f = fopen(filePath.c_str(), "rb");
    if(f == nullptr){
        return -1;
    }
    return 0;
}

// 用来关闭文件
int AnnexBReader::Close()
{
    if(f != nullptr){
        fclose(f);
        f = nullptr;
    }
    if(buffer != nullptr){
        free(buffer);
        buffer = nullptr;
    }
    return 0;
}

// 用来读取一个 Nalu 文件
int AnnexBReader::ReadNalu(Nalu & nalu)
{
    while(1){
        if(bufferLen <= 0){
            int readedLen = ReadFromFile();
            if(readedLen <= 0){
                isEnd = true;
            }
        }

        uint8_t * buf = buffer;

        int startCodeLen = 0;
        // Find Start Code
        bool isStartCode = CheckStartCode(startCodeLen, buf, bufferLen);
        if(!isStartCode){
            break;
        }

        nalu.startCodeLen = startCodeLen;

        // Find End Code
        int endPos = -1;
        for(int i=2;i<bufferLen;i++){
            int startCodeLen = 0;
            bool isStartCode = CheckStartCode(startCodeLen, buf + i, bufferLen - i);
            if(isStartCode){
                endPos = i;
                break;
            }
        }

        if(endPos > 0){
            nalu.SetBuf(buffer, endPos);
            uint8_t * _buffer = (uint8_t*)malloc(bufferLen - endPos);

            memcpy(_buffer, buffer + endPos, bufferLen - endPos);

            if(buffer != nullptr){
                free(buffer);
                buffer = nullptr;
            }
            buffer = _buffer;
            bufferLen = bufferLen - endPos;

            return 0;
        }
        else{
            if(isEnd == true){
                // 到达文件末尾，取所有 buffer 出来
                nalu.SetBuf(buffer, bufferLen);
                if(buffer != nullptr){
                    free(buffer);
                    buffer = nullptr;
                }
                buffer = nullptr;
                bufferLen = 0;

                return 0;
            }
            int readedLen = ReadFromFile();
            if(readedLen <= 0){
                isEnd = true;
            }
        }
    }

    return -1;
}

int AnnexBReader::ReadFromFile()
{
    int tempBufferLen = 1024;
    uint8_t * buf = (uint8_t *) malloc (tempBufferLen);
    int readedLen = fread(buf, 1, tempBufferLen, f);

    if(readedLen > 0){
        // 将新读取的 buf 添加到旧的 buffer 之后
        uint8_t * _buffer = (uint8_t *) malloc (bufferLen + readedLen);
        memcpy(_buffer,                 buffer, bufferLen);
        memcpy(_buffer + bufferLen,     buf,    readedLen);
        bufferLen = bufferLen + readedLen;

        if(buffer != nullptr){
            free(buffer);
            buffer = nullptr;
        }

        buffer = _buffer;
    }

    free(buf);

    return readedLen;
}

bool AnnexBReader::CheckStartCode(int & startCodeLen, uint8_t * bufPtr, int bufLen)
{
    if(bufLen <= 2){
        startCodeLen = 0;
        return false;
    }
    if(bufLen >= 4){
        if(bufPtr[0] == 0) {
            if (bufPtr[1] == 0) {
                if (bufPtr[2] == 0) {
                    if (bufPtr[3] == 1) {
                        startCodeLen = 4;
                        return true;
                    }
                }
                if(bufPtr[2] == 1){
                    startCodeLen = 3;
                    return true;
                }
            }
        }
    }
    if(bufLen <= 3){
        if(bufPtr[0] == 0) {
            if (bufPtr[1] == 0) {
                if(bufPtr[2] == 1){
                    startCodeLen = 3;
                    return true;
                }
            }
        }
    }

    startCodeLen = 0;
    return false;
}