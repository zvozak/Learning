#include <map>
#include "triplets.h"

using namespace std;

template <typename K, typename V>
bool contains(const map<K,V>& map, K key) {
    return map.find(key) != map.end();
}

long long sumUntil(long long number) {
    long long result;
    if (number % 2 == 0) {
        result = number/2 * (number + 1);
    }
    else{ result =  ((number + 1) / 2) * number;}

    return result;
}

long long countTripletsOfSameNumber(const vector<long long>& arr) {
    map<long long, int> numberCount;

    for (auto const & number : arr) {
        if (contains(numberCount, number)) {
            numberCount[number]++;
        } else {
            numberCount[number] = 1;
        }
    }

    long long count = 0;
    for (auto c : numberCount) {
        if(c.second >= 3) {
            for (long long i = 1; i < c.second-2; i++) {
                count+= sumUntil(i);
            }
        }
    }
    return count;
}

long long countZeroedTriplets (const vector<long long> & arr) {
    long long count = 0;
    long long countZeros = 0;
    for (auto it = arr.rbegin(); it != arr.rend(); it++) {
        if (*it == 0) {
            countZeros++;
        } else {
            if (countZeros >= 2) {
                for (long long i = countZeros-1; i >= 1; i--) {
                    count+= sumUntil(countZeros-i);
                }
            }
        }
    }
    return count;
}

// Complete the countTriplets function below.
long long countTriplets(const vector<long long>& arr, long long r) {
    std::map<long long, long long> seconds, thirds;

    long long count = 0;
    for(long long i : arr) {
        if ( thirds.find(i) != thirds.end() ) {
            count += thirds[i];
        }
        if ( seconds.find(i) != seconds.end() ) {
            thirds[i * r] += seconds[i];
        }
        seconds[i * r]++;
    }

    return count;
}