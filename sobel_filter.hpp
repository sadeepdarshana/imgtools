//
// Created by sadeep on 4/6/19.
//

#ifndef GIL_SOBEL_FILTER_H
#define GIL_SOBEL_FILTER_H


#include <boost/gil/gil_all.hpp>
#include "convolute.hpp"

using namespace boost::gil;

namespace imgtools {


    const int sobel_filter_x[3][3] = {{-1, 0, +1},
                                      {-2, 0, +2},
                                      {-1, 0, +1}};

    const int sobel_filter_y[3][3] = {{-1, -2, -1},
                                      {0,  0,  0},
                                      {+1, +2, +1}};


    void apply_sobel_filter(const gray8c_view_t &src, const gray8_view_t &dst) {


        gray16s_image_t x_raw(src.dimensions());
        gray16s_view_t x_view = view(x_raw);
        convolute(sobel_filter_x, src, x_view);

        gray16s_image_t y_raw(src.dimensions());
        gray16s_view_t y_view = view(y_raw);
        convolute(sobel_filter_y, src, y_view);


        for (int y = 0; y < src.height(); y++) {
            for (int x = 0; x < src.width(); x++)
                dst(x, y) = sqrt(x_view(x, y) * x_view(x, y) + y_view(x, y) * y_view(x, y));
        }
    }


    void apply_sobel_filter(const rgb8c_view_t &src, const rgb8_view_t &dst) {



        //for (int i = 0; i < src.num_channels(); i++)           apply_sobel_filter_channel(kernel,ker_w,ker_h, nth_channel_view(src, i), nth_channel_view(dst, i));
    }


}
#endif //GIL_GAUSSIAN_BLUR_H
