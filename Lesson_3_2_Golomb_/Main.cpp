#include "AnnexBReader.hpp"

int main(int argc, char const *argv[])
{
    std::string filePath = "./demo_video_176x144_baseline.h264";
    AnnexBReader reader(filePath);
    int ret = reader.Open();
    if(ret){
        printf("Read Fail");
        return -1;
    }

    while(1){
        uint8_t buffer[1024 * 1024];
        int bufferLen = 0;
        int startcodeLen = 0;
        ret = reader.ReadNalu(buffer, &bufferLen, &startcodeLen);
        if(ret){
            break;
        }
        printf("=====================\n");
        printf("Buffer Len: %d\n", bufferLen);
        printf("Start Code Len: %d\n", startcodeLen);
        printf("%d %d %d %d %d\n", buffer[0], buffer[1], buffer[2], buffer[3], buffer[4]);
    }

    reader.Close();

    return 0;
}