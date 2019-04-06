#define png_infopp_NULL (png_infopp)NULL
#define int_p_NULL (int*)NULL



#include <boost/gil/gil_all.hpp>
#include <boost/gil/extension/io/png_dynamic_io.hpp>
#include "tools_all.hpp"
#include "sobel_filter.hpp"




using namespace boost::gil;
using namespace imgtools;




int main()
{




    gray8_image_t raw_img;
    png_read_and_convert_image("in1.png",raw_img);
    gray8c_view_t src_view = const_view(raw_img);

    gray8_image_t dst_raw(raw_img.dimensions());
    gray8_view_t  dst_view = view(dst_raw);




    apply_sobel_filter(src_view,dst_view);

    png_write_view("out.png",const_view(dst_raw));



}
