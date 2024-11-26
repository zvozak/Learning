//
// Created by vozak on 2024. 11. 26..
//
#include "../hackerrank_lib/common_child.h"
#include <fstream>
#include <gtest/gtest.h>


TEST(CommonChildTestSuite, Hackerrank_TestCases){
    ifstream input1("../../Google_tests/resources/common_child_testcase_1_input.txt");
    string s1;
    getline(input1, s1);
    string s2;
    getline(input1, s2);
    const int result1 = commonChild(s1, s2);

    EXPECT_EQ(result1, 15);

    ifstream input2("../../Google_tests/resources/common_child_testcase_2_input.txt");
    getline(input2, s1);
    getline(input2, s2);
    const int result2 = commonChild(s1, s2);

    EXPECT_EQ(result2, 27);
}