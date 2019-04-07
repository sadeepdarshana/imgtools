#define png_infopp_NULL (png_infopp)NULL
#define int_p_NULL (int*)NULL



#include <boost/gil/gil_all.hpp>
#include <boost/gil/extension/io/png_dynamic_io.hpp>
#include "lib/tools_all.hpp"





using namespace boost::gil;
using namespace imgtools;




int main()
{




    rgb8_image_t raw_img1;
    png_read_and_convert_image("in1.png",raw_img1);

    gray8_image_t raw_img2;
    png_read_and_convert_image("in2.png",raw_img2);

    rgb8_image_t raw_img3;
    png_read_and_convert_image("in3.png",raw_img3);

    rgb8_image_t raw_img4;
    png_read_and_convert_image("in4.png",raw_img4);


    rgb8_image_t dst_raw1(raw_img1.dimensions());

    gray8_image_t dst_raw2(raw_img2.dimensions());

    rgb8_image_t dst_raw3(raw_img3.dimensions());

    rgb8_image_t dst_raw4(raw_img4.dimensions());





    apply_gaussian_blur(11,3, const_view(raw_img1),view(dst_raw1));
    apply_sobel_filter(const_view(raw_img2),view(dst_raw2));
    apply_mean_filter(const_view(raw_img3),view(dst_raw3));
    apply_median_filter(const_view(raw_img4),view(dst_raw4));



    png_write_view("out1.png",const_view(dst_raw1));
    png_write_view("out2.png",const_view(dst_raw2));
    png_write_view("out3.png",const_view(dst_raw3));
    png_write_view("out4.png",const_view(dst_raw4));



}
