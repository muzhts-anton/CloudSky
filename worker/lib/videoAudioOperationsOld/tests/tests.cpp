#include "gtest/gtest.h"
#include "../include/SoundComponent.h"
#include "../include/VideoComponent.h"

TEST(video, incorrectInit){
  VideoComponent video;
  ASSERT_EQ(video.initVideoComponent(), false);
}

TEST(audio, incorrectInit){
  SoundComponent audio;
  ASSERT_EQ(audio.initSoundComponent(), false);
}


int main(int argc, char **argv) {

  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}