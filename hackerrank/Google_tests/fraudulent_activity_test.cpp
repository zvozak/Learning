//
// Created by vozak on 2024. 11. 26..
//
#include "utils.h"
#include "../hackerrank_lib/fradulent_activity.h"
#include <fstream>
#include <iostream>
#include <gtest/gtest.h>

TEST(FraudulentActivityTestSuite, HackerrankCase_3) {
    const vector<int> expenditure = {1, 2, 3, 4, 8, 4, 16};
    const int d = 4;
    const int res = activityNotifications(expenditure, d);

    ASSERT_EQ(res, 2);
}

TEST(FraudulentActivityTestSuite, HackerrankCase_1) {
    const vector<int> expenditure = {2, 3, 4, 2, 3, 6, 8, 4, 5};
    const int d = 5;
    const int res = activityNotifications(expenditure, d);

    ASSERT_EQ(res, 2);
}

TEST(FraudulentActivityTestSuite, HackerrankCase_2) {
    const vector<int> expenditure = {10, 20, 30, 40, 50};
    const int d = 2;
    const int res = activityNotifications(expenditure, d);

    ASSERT_EQ(res, 1);
}


TEST(FraudulentActivityTestSuite, HackerrankCase_10) {

    ifstream input("../../Google_tests/resources/fraudulent_activity_notification_test_10.txt");

    string first_multiple_input_temp;
    getline(input, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int n = stoi(first_multiple_input[0]);

    int d = stoi(first_multiple_input[1]);

    string expenditure_temp_temp;
    getline(input, expenditure_temp_temp);

    vector<string> expenditure_temp = split(rtrim(expenditure_temp_temp));

    vector<int> expenditure(n);

    for (int i = 0; i < n; i++) {
        int expenditure_item = stoi(expenditure_temp[i]);

        expenditure[i] = expenditure_item;
    }

    const int result = activityNotifications(expenditure, d);

    ASSERT_EQ(result, 633);
}