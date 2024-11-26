//
// Created by vozak on 2024. 11. 26..
//
#include "utils.h"
#include "../hackerrank_lib/counting_inversions.h"
#include <iostream>
#include <fstream>
#include <gtest/gtest.h>

vector<int> extractArrayFromFile(const string &filePath)
{
    ifstream input(filePath);

    string n_temp;
    getline(input, n_temp);

    long long n = stoi(ltrim(rtrim(n_temp)));

    string arr_temp_temp;
    getline(input, arr_temp_temp);

    vector<string> arr_temp = split(rtrim(arr_temp_temp));

    vector<int> arr(n);

    for (int i = 0; i < n; i++) {
        int arr_item = stoi(arr_temp[i]);

        arr[i] = arr_item;
    }

    return move(arr);
}

TEST(CountInversionsTestSuite, SmallDescendingList){
    const vector<int> arr = extractArrayFromFile("../../Google_tests/resources/counting_inversions_small_descending_input.txt");
    const long long result = countInversions(arr);

    ASSERT_EQ(result, 105);
}

TEST(CountInversionsTestSuite, LargeDescendingList){
    const vector<int> arr = extractArrayFromFile("../../Google_tests/resources/counting_inversions_large_descending_input.txt");
    const long long result = countInversions(arr);

    ASSERT_EQ(result, 4999950000);
}