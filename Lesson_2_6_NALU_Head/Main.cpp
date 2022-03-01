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

        uint8_t naluHead = rbsp.buf[0];

        int forbidden_bit   = (naluHead >> 7) & 1;
        int nal_ref_idc     = (naluHead >> 5) & 3;
        int nal_unit_type   = (naluHead >> 0) & 0x1f;

        printf("=================================\n");
        printf("forbidden_bit: %d\n", forbidden_bit);
        printf("nal_ref_idc: %d\n", nal_ref_idc);
        printf("nal_unit_type: %d\n", nal_unit_type);
    }

    reader.Close();

    return 0;
}