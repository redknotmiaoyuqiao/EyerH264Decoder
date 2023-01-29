#include "NaluSPS.hpp"

#include "BitStream.hpp"

NaluSPS::NaluSPS(const Nalu & nalu)
    : Nalu(nalu)
{

}

int NaluSPS::Parse()
{
    BitStream bs(rbsp.buf, rbsp.len);

    bs.ReadU(8);

    profile_idc = bs.ReadU(8);
    constraint_set0_flag = bs.ReadU1();
    constraint_set1_flag = bs.ReadU1();
    constraint_set2_flag = bs.ReadU1();
    constraint_set3_flag = bs.ReadU1();
    constraint_set4_flag = bs.ReadU1();
    constraint_set5_flag = bs.ReadU1();
    bs.ReadU(2);
    level_idc = bs.ReadU(8);
    seq_parameter_set_id = bs.ReadUE();

    bool isHigh = (profile_idc == 100      || profile_idc == 110       ||
                   profile_idc == 122      || profile_idc == 244       || profile_idc == 44     ||
                   profile_idc == 83       || profile_idc == 86        || profile_idc == 118    ||
                   profile_idc == 128      || profile_idc == 138       || profile_idc == 139    ||
                   profile_idc == 134      || profile_idc == 135);
    if(isHigh)
    {
        chroma_format_idc = bs.ReadUE();

        if(chroma_format_idc == 3) {
            separate_colour_plance_flag = bs.ReadU1();
        }
        bit_depth_luma_minus8                   = bs.ReadUE();
        bit_depth_chroma_minus8                 = bs.ReadUE();
        qpprime_y_zero_transform_bypass_flag    = bs.ReadU1();
        seq_scaling_matrix_present_flag         = bs.ReadU1();

        if(seq_scaling_matrix_present_flag) {
            for(int i=0; i<((chroma_format_idc != 3) ? 8 : 12); i++ ){
                seq_scaling_list_present_flag[i] = bs.ReadU1();
                if(seq_scaling_list_present_flag[i]){
                    if(i<6) {
                        ReadScalingList(bs, ScalingList4x4[i], 16, &(UseDefaultScalingMatrix4x4Flag[i]));
                    }
                    else {
                        ReadScalingList(bs, ScalingList8x8[i-6], 64, &(UseDefaultScalingMatrix8x8Flag[i-6]));
                    }
                }
            }
        }
    }


    if (separate_colour_plance_flag == 0){
        ChromaArrayType = chroma_format_idc;
    }
    else{
        ChromaArrayType = 0;
    }

    if (chroma_format_idc == 1) {
        SubWidthC = 2;
        SubHeightC = 2;
    }
    if (chroma_format_idc == 2) {
        SubWidthC = 2;
        SubHeightC = 1;
    }
    if (chroma_format_idc == 3) {
        SubWidthC = 1;
        SubHeightC = 1;
    }




    log2_max_frame_num_minus4               = bs.ReadUE();
    pic_order_cnt_type                      = bs.ReadUE();


    if(pic_order_cnt_type == 0) {
        log2_max_pic_order_cnt_lsb_minus4 = bs.ReadUE();
    }
    else if(pic_order_cnt_type == 1){
        delta_pic_order_always_zero_flag                = bs.ReadU1();
        offset_for_non_ref_pic                          = bs.ReadSE();
        offset_for_top_to_bottom_field                  = bs.ReadSE();
        num_ref_frames_in_pic_order_cnt_cycle           = bs.ReadUE();

        for(int i=0; i<num_ref_frames_in_pic_order_cnt_cycle; i++) {
            offset_for_ref_frame[i] = bs.ReadSE();
        }
    }


    num_ref_frames                              = bs.ReadUE();
    gaps_in_frame_num_value_allowed_flag        = bs.ReadU1();
    pic_width_in_mbs_minus1                     = bs.ReadUE();
    pic_height_in_map_units_minus1              = bs.ReadUE();
    frame_mbs_only_flag                         = bs.ReadU1();


    if(!frame_mbs_only_flag) {
        mb_adaptive_frame_field_flag = bs.ReadU1();
    }


    direct_8x8_inference_flag       = bs.ReadU1();
    frame_cropping_flag             = bs.ReadU1();
    if(frame_cropping_flag) {
        frame_crop_left_offset          = bs.ReadUE();
        frame_crop_right_offset         = bs.ReadUE();
        frame_crop_top_offset           = bs.ReadUE();
        frame_crop_bottom_offset        = bs.ReadUE();
    }

    vui_parameters_present_flag         = bs.ReadU1();

    if(vui_parameters_present_flag){
        ReadVuiParameters(bs);
    }

    return 0;
}

int NaluSPS::ReadScalingList(BitStream & bs, int * scalingList, int sizeOfScalingList, int * useDefaultScalingMatrixFlag)
{
    int lastScale = 8;
    int nextScale = 8;
    int delta_scale;
    for( int j = 0; j < sizeOfScalingList; j++ ) {
        if( nextScale != 0 ) {
            if(0) {
                nextScale = scalingList[ j ];
                if (useDefaultScalingMatrixFlag[0]) { nextScale = 0; }
                delta_scale = (nextScale - lastScale) % 256 ;
            }

            delta_scale = bs.ReadSE();

            if(1) {
                nextScale = ( lastScale + delta_scale + 256 ) % 256;
                useDefaultScalingMatrixFlag[0] = ( j == 0 && nextScale == 0 );
            }
        }
        if(1) {
            scalingList[j] = ( nextScale == 0 ) ? lastScale : nextScale;
        }
        lastScale = scalingList[j];
    }
    return 0;
}

int NaluSPS::ReadVuiParameters(BitStream & bs)
{
    int vuilevel = 1;

    int SAR_Extended = 255;
    vui.aspect_ratio_info_present_flag = bs.ReadU1();
    if(vui.aspect_ratio_info_present_flag) {
        vui.aspect_ratio_idc = bs.ReadU(8);
        if(vui.aspect_ratio_idc == SAR_Extended){
            vui.sar_width      = bs.ReadU(16);
            vui.sar_height     = bs.ReadU(16);
        }
    }

    vui.overscan_info_present_flag = bs.ReadU1();
    if(vui.overscan_info_present_flag) {
        vui.overscan_appropriate_flag = bs.ReadU1();
    }

    vui.video_signal_type_present_flag = bs.ReadU1();
    if(vui.video_signal_type_present_flag) {
        vui.video_format                            = bs.ReadU(3);
        vui.video_full_range_flag                   = bs.ReadU1();
        vui.colour_description_present_flag         = bs.ReadU1();
        if(vui.colour_description_present_flag) {
            vui.colour_primaries                    = bs.ReadU(8);
            vui.transfer_characteristics            = bs.ReadU(8);
            vui.matrix_coefficients                 = bs.ReadU(8);
        }
    }

    vui.chroma_loc_info_present_flag                = bs.ReadU1();
    if(vui.chroma_loc_info_present_flag) {
        vui.chroma_sample_loc_type_top_field        = bs.ReadUE();
        vui.chroma_sample_loc_type_bottom_field     = bs.ReadUE();
    }

    vui.timing_info_present_flag = bs.ReadU1();
    if(vui.timing_info_present_flag) {
        vui.num_units_in_tick                       = bs.ReadU(32);
        vui.time_scale                              = bs.ReadU(32);
        vui.fixed_frame_rate_flag                   = bs.ReadU1();
    }

    vui.nal_hrd_parameters_present_flag = bs.ReadU1();
    if(vui.nal_hrd_parameters_present_flag) {
        ReadHrdParameters(vui.hrd_nal, bs);
    }

    vui.vcl_hrd_parameters_present_flag = bs.ReadU1();
    if(vui.vcl_hrd_parameters_present_flag) {
        ReadHrdParameters(vui.hrd_vcl, bs);
    }

    if(vui.nal_hrd_parameters_present_flag || vui.vcl_hrd_parameters_present_flag) {
        vui.low_delay_hrd_flag = bs.ReadU1();
    }

    vui.pic_struct_present_flag         = bs.ReadU1();
    vui.bitstream_restriction_flag      = bs.ReadU1();

    if(vui.bitstream_restriction_flag) {
        vui.motion_vectors_over_pic_boundaries_flag     = bs.ReadU1();
        vui.max_bytes_per_pic_denom                     = bs.ReadUE();
        vui.max_bits_per_mb_denom                       = bs.ReadUE();
        vui.log2_max_mv_length_horizontal               = bs.ReadUE();
        vui.log2_max_mv_length_vertical                 = bs.ReadUE();
        vui.num_reorder_frames                          = bs.ReadUE();
        vui.max_dec_frame_buffering                     = bs.ReadUE();
    }

    return 0;
}

int NaluSPS::ReadHrdParameters(HRD & hrd, BitStream & bs)
{
    hrd.cpb_cnt_minus1 = bs.ReadUE();
    hrd.bit_rate_scale = bs.ReadU(4);
    hrd.cpb_size_scale = bs.ReadU(4);

    for(int SchedSelIdx = 0; SchedSelIdx <= hrd.cpb_cnt_minus1; SchedSelIdx++) {
        hrd.bit_rate_value_minus1[SchedSelIdx]        = bs.ReadUE();
        hrd.cpb_size_value_minus1[SchedSelIdx]        = bs.ReadUE();
        hrd.cbr_flag[SchedSelIdx]                     = bs.ReadU1();
    }
    hrd.initial_cpb_removal_delay_length_minus1     = bs.ReadU(5);
    hrd.cpb_removal_delay_length_minus1             = bs.ReadU(5);
    hrd.dpb_output_delay_length_minus1              = bs.ReadU(5);
    hrd.time_offset_length                          = bs.ReadU(5);

    return 0;
}