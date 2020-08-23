#ifndef TEST277DC58A_7133_F0D5_9F07_DE95297B67A9
#define TEST277DC58A_7133_F0D5_9F07_DE95297B67A9

#include "utils.h"
#include "video_state.h"
#include "ffplay.h"
//#include "packet_provider.h"
//#include "producer.h"
#include "ftf.h"

#include <stdio.h>
#include <gtest/gtest.h>

#define TEST_BEGIN
#define TEST_END                                \
    int main(int argc, char **argv)             \
    {                                           \
        ::testing::InitGoogleTest(&argc, argv); \
        return RUN_ALL_TESTS();                 \
    }

#endif /* 277DC58A_7133_F0D5_9F07_DE95297B67A9 */
