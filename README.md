# imgtools 

## Usage
### Setting Up
Copy the lib folder into your project and #include "lib/tools_all.hpp"

### Applying 

    apply_gaussian_blur(11,3, const_view(raw_img1),view(dst_raw1));
    apply_sobel_filter(const_view(raw_img2),view(dst_raw2));
    apply_mean_filter(const_view(raw_img3),view(dst_raw3));
    apply_median_filter(const_view(raw_img4),view(dst_raw4));

## Features


### 1 Gaussian Blur

![Input](in1.png)
![Output](out1.png)



### 2 Sabel Filter

![Input](in2.png)
![Output](out2.png)


### 3 Mean Filter

![Input](in3.png)
![Output](out3.png)


### 4 Median Filter

![Input](in4.png)
![Output](out4.png)
