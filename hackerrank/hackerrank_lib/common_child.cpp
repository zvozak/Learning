//
// Created by vozak on 2024. 11. 08..
//

#include "common_child.h"
#include <vector>

using namespace std;


int commonChild(string s1, string s2){
    vector<int> currentCounts = vector<int>(s2.size() + 1, 0);

    for (int i = 1; i <= s1.size(); i++){
        vector<int> nextCounts = vector<int>(s2.size() + 1, 0);
        for(int j = 1; j <= s2.size(); j++){
            if (s1[i-1] == s2[j-1]){
                nextCounts[j] = currentCounts[j-1] + 1;
            }
            else{
                nextCounts[j] = max(nextCounts[j-1], currentCounts[j]);
            }
        }
        currentCounts = nextCounts;
    }

    return currentCounts[s2.size()];
}

