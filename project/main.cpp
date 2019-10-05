/*************************************************************************
	> File Name: main.cpp
	> Author: 
	> Mail: 
	> Created Time: 2019年09月24日 星期二 18时50分00秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <gtest/gtest.h>

int add(int a, int b) {
    return a + b;
}

TEST(testFunc, add) {
    EXPECT_EQ(add(5, 3), 8);
    EXPECT_EQ(add(5, 3), 9);
    EXPECT_EQ(add(6, 7), 9);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
