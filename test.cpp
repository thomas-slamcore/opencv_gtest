#include <gtest/gtest.h>
#include <opencv2/core.hpp>

void sobelFilter(const cv::Mat& src, cv::Mat& dst)
{
  static const float kernelData[] =
  {
    +1, 0, -1,
    +2, 0, -2,
    +1, 0, -1,
  };
  static const cv::Mat kernel(3, 3, CV_32FC1, const_cast<float*>(kernelData));

  // TODO implement this
}

TEST(Sobel, dummy)
{
  cv::Mat image(1024, 1024, CV_32FC1);
  cv::Mat edges;

  sobelFilter(image, edges);
  EXPECT_FALSE(edges.empty());
}
