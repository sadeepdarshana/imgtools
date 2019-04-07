//
// Created by sadeep on 4/6/19.
//

#ifndef GIL_SHARPENING_FILTER_H
#define GIL_SHARPENING_FILTER_H


#include <boost/gil/gil_all.hpp>
#include "convolute.hpp"

namespace imgtools {


    const double sharpening_filter[3][3] = {{-1.0/9, -1.0/9, -1.0/9},
                                            {-1.0/9, 1, -1.0/9},
                                            {-1.0/9, -1.0/9, -1.0/9}};



    template<typename S, typename D>
    void apply_sharpening_filter(const S &src, const D &dst){

/*
 * NOT IMPLEMENTED YET
 *
        rgb32f_image_t dst_raw(src.dimensions());
        rgb32f_view_t  dst_view = view(dst_raw);
        convolute(sharpening_filter,src,dst_view);
*/
    }

}

#endif //GIL_SHARPENING_FILTER_H
