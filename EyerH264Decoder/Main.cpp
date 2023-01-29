#include "AnnexBReader.hpp"
#include "EBSP.hpp"
#include "RBSP.hpp"
#include "BitStream.hpp"

#include "NaluSPS.hpp"
#include "NaluPPS.hpp"

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

        nalu.ParseRBSP();
        nalu.ParseHeader();

        printf("Nalu Type: %d\n", nalu.GetNaluType());

        if(nalu.GetNaluType() == 7){
            NaluSPS sps = nalu;
            sps.Parse();
        }
        if(nalu.GetNaluType() == 8){
            NaluPPS pps = nalu;
            pps.Parse();
        }
    }

    reader.Close();

    return 0;
}