#include "AnnexBReader.hpp"
#include "EBSP.hpp"
#include "RBSP.hpp"

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
        Nalu nalu;
        ret = reader.ReadNalu(nalu);
        if(ret){
            break;
        }
        printf("=====================\n");
        printf("Buffer Len: %d\n", nalu.len);
        printf("Start Code Len: %d\n", nalu.startCodeLen);
        printf("%d %d %d %d %d\n", nalu.buf[0], nalu.buf[1], nalu.buf[2], nalu.buf[3], nalu.buf[4]);

        EBSP ebsp;
        ret = nalu.GetEBSP(ebsp);
        if(ret){
            break;
        }

        RBSP rbsp;
        ret = ebsp.GetRBSP(rbsp);
        if(ret){
            break;
        }


    }

    reader.Close();

    return 0;
}