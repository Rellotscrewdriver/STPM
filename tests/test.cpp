#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../include/dog.h"

TEST(testsuite, testcase1){
    ASSERT_EQ(3, 3);
}

TEST(testsuite, testcase2){
    ASSERT_EQ(3, 4);
}