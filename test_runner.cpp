#include <gtest/gtest.h>
#include <gmock/gmock.h>

int main(int argc, char** argv)
{
  ::testing::InitGoogleMock(&argc, argv);
  int rc = RUN_ALL_TESTS();

  return rc;
}

