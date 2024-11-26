//
// Created by vozak on 2024. 10. 29..
//

#include <bits/stdc++.h>
#include "frequency_queries.h"

using namespace std;

template<typename K, typename V>
bool contains(const map<K, V> & map, K key) {
    return map.end() != map.find(key);
}

// Complete the freqQuery function below.
vector<int> freqQuery(vector<vector<int> > queries) {
    map<int, int> frequencies;
    map<int, int> countFrequencies;
    vector<int> results;

    for (auto const &query: queries) {
        Operation operation = Operation(query[0]);
        int number = query[1];
        switch (operation) {
            case INSERT:
                countFrequencies[frequencies[number]]--;
                frequencies[number]++;
                countFrequencies[frequencies[number]]++;
                break;
            case DELETE:
                if (contains(frequencies, number) && frequencies[number] > 0) {
                    countFrequencies[frequencies[number]]--;
                    frequencies[number]--;
                    countFrequencies[frequencies[number]]++;
                }
                break;
            case FIND_SAME_FREQUENCY:
                if (countFrequencies[number] > 0) {
                    results.push_back(1);
                } else {
                    results.push_back(0);
                }
                break;
        }
    }
    return results;
}