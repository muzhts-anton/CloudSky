#include "gtest/gtest.h"
#include "../include/VideoStreamDecoder.h"
#include "../include/AudioStreamDecoder.h"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  
  return RUN_ALL_TESTS();
}