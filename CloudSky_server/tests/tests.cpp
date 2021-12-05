#include "gtest/gtest.h"
#include "../include/SoundComponent.h"
#include "../include/VideoComponent.h"

TEST(video, incorrectInit){
  VideoComponent video;
  ASSERT_EQ(video.initVideoComponent(), false);
}

TEST(video, incorrectStartLoop){
  
}

TEST(video, incorrectStopLoop){
  
}

TEST(audio, incorrectInit){
  SoundComponent audio;
  ASSERT_EQ(audio.initSoundComponent(), false);
}

TEST(audio, incorrectStartLoop){

}

TEST(audio, incorrectStopLoop){
    
}


int main(int argc, char **argv) {

  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
