#include "NaluPPS.hpp"

#include "BitStream.hpp"

NaluPPS::NaluPPS(const Nalu & nalu)
    : Nalu(nalu)
{

}

int NaluPPS::Parse()
{
    BitStream bs(rbsp.buf, rbsp.len);

    bs.ReadU(8);


    pic_parameter_set_id        = bs.ReadUE();
    seq_parameter_set_id        = bs.ReadUE();
    entropy_coding_mode_flag    = bs.ReadU1();
    pic_order_present_flag      = bs.ReadU1();
    num_slice_groups_minus1     = bs.ReadUE();

    if(num_slice_groups_minus1 > 0) {
        slice_group_map_type = bs.ReadUE();
        if(slice_group_map_type == 0) {
            for(int i_group = 0; i_group <= num_slice_groups_minus1; i_group++){
                run_length_minus1[i_group] = bs.ReadUE();
            }
        }
        else if(slice_group_map_type == 2) {
            for(int i_group = 0; i_group < num_slice_groups_minus1; i_group++) {
                top_left[ i_group ]     = bs.ReadUE();
                bottom_right[ i_group ] = bs.ReadUE();
            }
        }
        else if( slice_group_map_type == 3 ||
                 slice_group_map_type == 4 ||
                 slice_group_map_type == 5 )
        {
            slice_group_change_direction_flag = bs.ReadU1();
            slice_group_change_rate_minus1 = bs.ReadUE();
        }
        else if(slice_group_map_type == 6) {
            pic_size_in_map_units_minus1 = bs.ReadUE();
            for( int i = 0; i <= pic_size_in_map_units_minus1; i++ ) {
                int v = intlog2( num_slice_groups_minus1 + 1 );
                slice_group_id[i] = bs.ReadU(v);
            }
        }
    }

    num_ref_idx_l0_active_minus1            = bs.ReadUE();
    num_ref_idx_l1_active_minus1            = bs.ReadUE();
    weighted_pred_flag                      = bs.ReadU1();
    weighted_bipred_idc                     = bs.ReadU(2);
    pic_init_qp_minus26                     = bs.ReadSE();
    pic_init_qs_minus26                     = bs.ReadSE();
    chroma_qp_index_offset                  = bs.ReadSE();
    deblocking_filter_control_present_flag  = bs.ReadU1();
    constrained_intra_pred_flag             = bs.ReadU1();
    redundant_pic_cnt_present_flag          = bs.ReadU1();

    // TODO more_rbsp_data
    /*
    if(bs.more_data()) {
        transform_8x8_mode_flag             = bs.bs_read_u1();
        pic_scaling_matrix_present_flag     = bs.bs_read_u1();
        if(pic_scaling_matrix_present_flag) {
            // TODO
        }
    }
    */

    return 0;
}

int NaluPPS::intlog2(int x)
{
    int log = 0;
    if (x < 0) { x = 0; }
    while ((x >> log) > 0) {
        log++;
    }
    if (log > 0 && x == 1 << (log-1)) {
        log--;
    }
    return log;
}