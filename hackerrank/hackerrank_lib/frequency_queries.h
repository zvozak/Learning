//
// Created by vozak on 2024. 11. 26..
//

#ifndef FREQUENCY_QUERIES_H
#define FREQUENCY_QUERIES_H

#include <vector>

using namespace std;

enum Operation {
    INSERT = 1,
    DELETE = 2,
    FIND_SAME_FREQUENCY = 3
};

// Complete the freqQuery function below.
vector<int> freqQuery(vector<vector<int> > queries);

#endif //FREQUENCY_QUERIES_H
