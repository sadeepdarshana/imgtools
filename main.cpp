#define png_infopp_NULL (png_infopp)NULL
#define int_p_NULL (int*)NULL



#include <boost/gil/gil_all.hpp>
#include <boost/gil/extension/io/png_dynamic_io.hpp>
#include "tools_all.hpp"




using namespace boost::gil;
using namespace std;
using namespace imgtools;




int main()
{




    rgb8_image_t raw_img;
    png_read_image("in.png",raw_img);

    rgb8_image_t dst_raw(raw_img.dimensions());
    rgb8_view_t  dst_view = view(dst_raw);

    rgb8c_view_t src_view = const_view(raw_img);

    double kernel[11][11];
/*
    int kernel[3][3] = {
            {0,0,0},
            {0,1,0},
            {0,0,0},
    };
*/
    gaussian_kernel(kernel,7);

    convolute(kernel,src_view,dst_view);

    png_write_view("out.png",const_view(dst_raw));

    //cout<<"done"<<endl;

}
