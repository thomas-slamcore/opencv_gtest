#include <gtest/gtest.h>
#include <opencv2/core.hpp>

static int clamp(int value, int min, int max)
{
  return std::min(std::max(value, min), max);
}

static void sobelFilter(const cv::Mat& src, cv::Mat& dst)
{
  // Create vertical Sobel 3x3 kernel
  static const float kernelData[] =
  {
    +1, 0, -1,
    +2, 0, -2,
    +1, 0, -1,
  };
  static const cv::Mat kernel(3, 3, CV_32FC1, const_cast<float*>(kernelData));

  // Allocate destination matrix
  if ((dst.rows != src.rows) ||
      (dst.cols != src.cols) ||
      (dst.type() != CV_32FC1))
  {
    dst.create(src.rows, src.cols, CV_32FC1);
  }

  // Perform 2D convolution
  for (int y = 0; y < src.rows; ++y)
  for (int x = 0; x < src.cols; ++x)
  {
    float value = 0;

    for (int yy = 0; yy < kernel.rows; ++yy)
    for (int xx = 0; xx < kernel.cols; ++xx)
    {
      const int xsrc = clamp(x + xx, 0, src.cols - 1);
      const int ysrc = clamp(y + yy, 0, src.rows - 1);

      const float element = src.at<float>(ysrc, xsrc);
      value += element * kernel.at<float>(yy, xx);
    }

    dst.at<float>(y, x) = value;
  }
}

TEST(Sobel, Solid)
{
  // Create uniform 3x3 image
  static const float srcData[] =
  {
    1, 1, 1,
    1, 1, 1,
    1, 1, 1,
  };
  static const cv::Mat src(3, 3, CV_32FC1, const_cast<float*>(srcData));

  // Run Sobel filter
  cv::Mat edges;
  sobelFilter(src, edges);

  // Check results
  ASSERT_EQ(edges.cols, src.cols);
  ASSERT_EQ(edges.rows, src.rows);

  for (int y = 0; y < src.rows; ++y)
  for (int x = 0; x < src.cols; ++x)
  {
    EXPECT_EQ(edges.at<float>(y, x), 0) << "[" << y << ", " << x << "]";
  }
}
