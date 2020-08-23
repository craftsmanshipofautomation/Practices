#include "def.h"

TEST_BEGIN

TEST(SRC, packet_provider)
{
   try
      {
         VideoState play("/home/root_/Pictures/DARKSOUL.mp4");
         play.Init();
      }
   catch (AVException &e)
      {
         LOGF("exception caught: %s", e.what());
      }
   // container.Demux();
}

TEST_END