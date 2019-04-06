#define png_infopp_NULL (png_infopp)NULL
#define int_p_NULL (int*)NULL
#include <boost/gil/gil_all.hpp>
#include <boost/gil/extension/io/png_dynamic_io.hpp>
#include <iostream>




using namespace boost::gil;
using namespace std;



void apply_sobel_filter(rgb8_view_t &src, rgb8_image_t &des){



}





template <typename T,typename D>
void convolute(T ** ker,const  int ker_w,const  int ker_h,const  gray8c_view_t & src, const D & dst){

    const int ker_size = ker_h * ker_w;

    typedef gray8c_view_t::xy_locator::cached_location_t loc;

    gray8c_view_t::xy_locator src_loc = src.xy_at(ker_w/2,ker_h/2);


    T ker_value[ker_size];
    T *val_it = ker_value;
    loc ker_loc[ker_size];
    loc *loc_it = ker_loc;


    for(int y=0;y<ker_h;y++)
        for(int x=0;x<ker_w;x++) {
            *(loc_it++) = src_loc.cache_location(x - ker_w / 2, y - ker_h / 2);
            *(val_it++) = ker[y][x];
        }


    for(int y=ker_h/2;y<src.height()-ker_h/2;y++) {

        gray8_view_t::x_iterator d_row_it = dst.row_begin(y);

        for (int x = ker_w/2; x < src.width()-ker_w/2; x++) {
            *d_row_it = 0;
            for(int c=0;c<ker_size;c++)(*d_row_it) = (*d_row_it) + ker_value[c]*src_loc[ker_loc[c]];
            d_row_it++;
            src_loc.x()++;
        }

        src_loc.x() -= src.width()-ker_w+1;
        src_loc.y()++;
    }

}

template <typename  T>
void print(T **ar,int w,int h){


    for(int i=0;i<h;i++){
        cout<<endl;
        for(int c=0;c<w;c++)cout<<ar[i][c]<<" ";
    }
}


int main()
{


#define W 15
#define double float

    double **kernel;
    kernel = new double *[W];for(int i = 0; i <W; i++)kernel[i] = new double[W];
    for(int x=0;x<W;x++)for(int y=0;y<W;y++)kernel[x][y]=0;
    double sigma = 7;
    double mean = W/2;
    double sum = 0.0; // For accumulating the kernel values
    for (int x = 0; x < W; ++x)
        for (int y = 0; y < W; ++y) {
            kernel[x][y] = exp( -0.5 * (pow((x-mean)/sigma, 2.0) + pow((y-mean)/sigma,2.0)) )
                           / (2 * M_PI * sigma * sigma);

            // Accumulate the kernel values
            sum += kernel[x][y];
        }

// Normalize the kernel
    for (int x = 0; x < W; ++x)
        for (int y = 0; y < W; ++y)
            kernel[x][y] /= sum;



        print(kernel,W,W);




        double bla=0;
    for (int x = 0; x < W; ++x) for (int y = 0; y < W; ++y)bla+=kernel[y][x];

    cout<<endl<<bla;








    gray8_image_t img;
    png_read_and_convert_image("in.png",img);

    gray8_image_t dst_raw(img.dimensions());
    gray8_view_t  dst = view(dst_raw);

    gray8c_view_t ssrc = const_view(img);

    convolute(kernel,W,W,ssrc,dst);

    png_write_view("out.png",const_view(dst_raw));


}
