//
// Created by sadeep on 4/6/19.
//

#ifndef GIL_MEDIAN_FILTER_H
#define GIL_MEDIAN_FILTER_H


#include <boost/gil/gil_all.hpp>
#include "convolute.hpp"
#include<algorithm>

using namespace std;

namespace imgtools {



    template<typename S, typename D>
    void apply_median_filter_channel(const S &src, const D &dst){

        for (int y = 1; y < src.height()-1; y++) {
            for (int x = 1; x < src.width()-1; x++){
                int ar[9];
                ar[0]=src(x-1,y-1);
                ar[1]=src(x,y-1);
                ar[2]=src(x+1,y-1);
                ar[3]=src(x-1,y);
                ar[4]=src(x,y);
                ar[5]=src(x+1,y);
                ar[6]=src(x-1,y+1);
                ar[7]=src(x,y+1);
                ar[8]=src(x+1,y+1);

                sort(ar,ar+9);
                dst(x,y) = ar[4];
            }
        }
    }

    template<typename S, typename D>
    void apply_median_filter(const S &src, const D &dst){

        for (int i = 0; i < src.num_channels(); i++)
            apply_median_filter_channel(nth_channel_view(src, i), nth_channel_view(dst, i));
    }

}

#endif //GIL_MEDIAN_FILTER_H
