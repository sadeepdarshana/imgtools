//
// Created by sadeep on 4/6/19.
//

#ifndef GIL_MEAN_FILTER_H
#define GIL_MEAN_FILTER_H


#include <boost/gil/gil_all.hpp>
#include "convolute.hpp"

namespace imgtools {


    const double mean_filter_x[3][3] = {{1.0/9, 1.0/9, 1.0/9},
                                        {1.0/9, 1.0/9, 1.0/9},
                                        {1.0/9, 1.0/9, 1.0/9}};



    template<typename S, typename D>
    void apply_mean_filter(const S &src, const D &dst){

        convolute(mean_filter_x,src,dst);
    }

}

#endif //GIL_MEAN_FILTER_H
