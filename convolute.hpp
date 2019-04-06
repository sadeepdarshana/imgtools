//
// Created by sadeep on 4/6/19.
//

#ifndef GIL_CONVOLUTE_H
#define GIL_CONVOLUTE_H



#include <boost/gil/gil_all.hpp>



namespace imgtools {

    template<std::size_t W, std::size_t H, typename T, typename S, typename D>
    void convolute_single_channel(const T (&kernel)[H][W], const S &src, const D &dst) {

        const int ker_size = H * W;

        //cached_location_t so that positions in array does not have to be recalculated
        typedef typename S::xy_locator::cached_location_t loc;

        typename S::xy_locator src_loc = src.xy_at(W / 2, H / 2);


        T ker_value[ker_size]; //here we convert the 2D kernel into a 1D array to speed up the calculations
        T *val_it = ker_value;
        loc ker_loc[ker_size];
        loc *loc_it = ker_loc;

        for (int y = 0; y < H; y++)
            for (int x = 0; x < W; x++) {
                *(loc_it++) = src_loc.cache_location(x - W / 2, y - H / 2);
                *(val_it++) = kernel[y][x];
            }


        if (typeid(T) == typeid(float) || typeid(T) == typeid(double)) {
            //this if block is for float and double valued kernals
            //less efficient than the code in the next block
            for (int y = H / 2; y < src.height() - H / 2; y++) {

                auto d_row_it = dst.row_begin(y);
                d_row_it += W / 2;

                for (int x = W / 2; x < src.width() - W / 2; x++) {
                    T val = 0;
                    for (int c = 0; c < ker_size; c++) val += ker_value[c] * src_loc[ker_loc[c]];

                    *d_row_it = (int) round(val);
                    d_row_it++;
                    src_loc.x()++;
                }

                src_loc.x() -= src.width() - W + 1;
                src_loc.y()++;
            }

        } else {
            //this if block is for integer valued kernels
            for (int y = H / 2; y < src.height() - H / 2; y++) {

                auto d_row_it = dst.row_begin(y);

                for (int x = W / 2; x < src.width() - W / 2; x++) {
                    *d_row_it = 0;
                    for (int c = 0; c < ker_size; c++) *d_row_it = *d_row_it + ker_value[c] * src_loc[ker_loc[c]];

                    d_row_it++;
                    src_loc.x()++;
                }

                src_loc.x() -= src.width() - W + 1;
                src_loc.y()++;
            }
        }

    }


    template<std::size_t W, std::size_t H, typename T, typename S, typename D>
    void convolute(const T (&kernel)[H][W], const S &src, const D &dst) {

        for (int i = 0; i < src.num_channels(); i++)
            convolute_single_channel(kernel, nth_channel_view(src, i), nth_channel_view(dst, i));


    }

}

#endif //GIL_CONVOLUTE_H
