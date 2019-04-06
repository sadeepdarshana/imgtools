//
// Created by sadeep on 4/6/19.
//

#ifndef GIL_GAUSSIAN_BLUR_H
#define GIL_GAUSSIAN_BLUR_H


#include <boost/gil/gil_all.hpp>

namespace imgtools {

    template<size_t N>
    void gaussian_kernel(double kernel[N][N], double sigma) {

        double mean = N / 2;
        double sum = 0.0;
        for (int x = 0; x < N; ++x)
            for (int y = 0; y < N; ++y) {
                kernel[x][y] = exp(-0.5 * (pow((x - mean) / sigma, 2.0) + pow((y - mean) / sigma, 2.0))) /
                               (2 * M_PI * sigma * sigma);
                sum += kernel[x][y];
            }

        for (int x = 0; x < N; ++x) for (int y = 0; y < N; ++y) kernel[x][y] /= sum;
    }

}

#endif //GIL_GAUSSIAN_BLUR_H
