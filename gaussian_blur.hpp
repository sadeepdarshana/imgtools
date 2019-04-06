//
// Created by sadeep on 4/6/19.
//

#ifndef GIL_GAUSSIAN_BLUR_H
#define GIL_GAUSSIAN_BLUR_H


#include <boost/gil/gil_all.hpp>
#include "convolute.hpp"

namespace imgtools {


    double ** gaussian_kernel(int size, double sigma) {


        double **kernel;
        kernel = new double *[size];for(int i = 0; i <size; i++)kernel[i] = new double[size];

        double mean = size / 2.0;
        double sum = 0.0;
        for (int x = 0; x < size; ++x)
            for (int y = 0; y < size; ++y) {
                kernel[x][y] = exp(-0.5 * (pow((x - mean) / sigma, 2.0) + pow((y - mean) / sigma, 2.0))) /
                               (2 * M_PI * sigma * sigma);
                sum += kernel[x][y];
            }

        for (int x = 0; x < size; ++x) for (int y = 0; y < size; ++y) kernel[x][y] /= sum;

        return kernel;
    }


    template<typename S, typename D>
    void apply_gaussian_blur(const int kernel_size,int sigma,const S &src, const D &dst){


        auto kernel = gaussian_kernel(kernel_size,sigma);

        convolute(kernel,kernel_size,kernel_size,src,dst);
    }

}

#endif //GIL_GAUSSIAN_BLUR_H
