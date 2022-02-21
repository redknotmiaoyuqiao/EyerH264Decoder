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
        Nalu nalu;
        ret = reader.ReadNalu(nalu);
        if(ret){
            break;
        }

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
        if(ebsp.len != rbsp.len) {
            printf("=====================\n");
            printf("EBSP Len: %d\n", ebsp.len);
            printf("RBSP Len: %d\n", rbsp.len);
        }
    }

    reader.Close();

    return 0;
}