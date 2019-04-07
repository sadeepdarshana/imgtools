//
// Created by sadeep on 4/6/19.
//

#ifndef GIL_CONVOLUTE_H
#define GIL_CONVOLUTE_H



#include <boost/gil/gil_all.hpp>



namespace imgtools {

    template<typename T, typename S, typename D>
    void convolute_channel(T **kernel,int ker_w,int ker_h , const S &src, const D &dst) {

        const int ker_size = ker_h * ker_w;

        //cached_location_t so that positions in array does not have to be recalculated
        typedef typename S::xy_locator::cached_location_t loc;

        typename S::xy_locator src_loc = src.xy_at(ker_w / 2, ker_h / 2);


        T ker_value[ker_size]; //here we convert the 2D kernel into a 1D array to speed up the calculations
        T *val_it = ker_value;
        loc ker_loc[ker_size];
        loc *loc_it = ker_loc;

        for (int y = 0; y < ker_h; y++)
            for (int x = 0; x < ker_w; x++) {
                *(loc_it++) = src_loc.cache_location(x - ker_w / 2, y - ker_h / 2);
                *(val_it++) = kernel[y][x];
            }


        if (typeid(T) == typeid(float) || typeid(T) == typeid(double)) {
            //this if block is for float and double valued kernals
            //less efficient than the code in the next block
            for (int y = ker_h / 2; y < src.height() - ker_h / 2; y++) {

                auto d_row_it = dst.row_begin(y);
                d_row_it += ker_w / 2;

                for (int x = ker_w / 2; x < src.width() - ker_w / 2; x++) {
                    T val = 0;
                    for (int c = 0; c < ker_size; c++) val += ker_value[c] * src_loc[ker_loc[c]];

                    *d_row_it = (int) round(val);
                    d_row_it++;
                    src_loc.x()++;
                }

                src_loc.x() -= src.width() - ker_w + 1;
                src_loc.y()++;
            }

        } else {
            //this if block is for integer valued kernels
            for (int y = ker_h / 2; y < src.height() - ker_h / 2; y++) {

                auto d_row_it = dst.row_begin(y);

                for (int x = ker_w / 2; x < src.width() - ker_w / 2; x++) {
                    *d_row_it = 0;
                        for (int c = 0; c < ker_size; c++) *d_row_it = *d_row_it + ker_value[c] * src_loc[ker_loc[c]];

                    d_row_it++;
                    src_loc.x()++;
                }

                src_loc.x() -= src.width() - ker_w + 1;
                src_loc.y()++;
            }
        }

    }

    //An easier method to use when kernel size is know at the compile time
    // (you can pass a 2D array instead of a pointer to a pointer)
    template<std::size_t W, std::size_t H, typename T, typename S, typename D>
    void convolute_channel(const T (&kernel)[H][W], const S &src, const D &dst) {
        T **kern;
        kern = new T *[H];for(int i = 0; i <H; i++)kern[i] = new T[W];
        for(int x=0;x<W;x++)for(int y=0;y<W;y++)kern[x][y]=kernel[x][y];

        convolute_channel(kern,W,H,src,dst);
    }




    template<typename T, typename S, typename D>
    void convolute( T **kernel,int ker_w,int ker_h, const S &src, const D &dst) {

        for (int i = 0; i < src.num_channels(); i++)
            convolute_channel(kernel,ker_w,ker_h, nth_channel_view(src, i), nth_channel_view(dst, i));
    }


    //An easier method to use when kernel size is know at the compile time
    // (you can pass a 2D array instead of a pointer to a pointer)
    template<std::size_t W, std::size_t H, typename T, typename S, typename D>
    void convolute(const T (&kernel)[H][W], const S &src, const D &dst) {

        for (int i = 0; i < src.num_channels(); i++)
            convolute_channel(kernel, nth_channel_view(src, i), nth_channel_view(dst, i));
    }

}

#endif //GIL_CONVOLUTE_H
