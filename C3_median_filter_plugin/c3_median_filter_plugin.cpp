#include "c3_median_filter_plugin.h"


C3_median_filter_plugin::C3_median_filter_plugin()
{
}

C3_median_filter_plugin::~C3_median_filter_plugin()
{

}


QString C3_median_filter_plugin::description()
{
    return "This plugin applies median blur filters to any image."
           " This plugin's goal is to make us more familiar with the"
           " concept of plugins in general.";
}

void C3_median_filter_plugin::processImage(const cv::Mat &inputImage, cv::Mat &outputImage)
{
    cv::medianBlur(inputImage, outputImage, 5);
}
