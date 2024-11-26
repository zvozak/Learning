//
// Created by vozak on 2024. 11. 07..
//


#include <bits/stdc++.h>
#include "counting_inversions.h"

using namespace std;

long long merge(vector<int>& arr, long long left,
                     long long mid, long long right)
{
    long long n1 = mid - left + 1;
    long long n2 = right - mid;
    long long count = 0;

    // Create temp vectors
    vector<int> L(n1), R(n2);

    // Copy data to temp vectors L[] and R[]
    for (long long i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (long long j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    long long i = 0, j = 0;
    long long k = left;

    // Merge the temp vectors back
    // longo arr[left..right]
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            count += n1 - i;
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[],
    // if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[],
    // if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    return count;
}

// begin is for left index and end is right index
// of the sub-array of arr to be sorted
long long mergeSort(vector<int>& arr, long long left, long long right)
{
    if (left >= right)
        return 0;

    long long mid = left + (right - left) / 2;
    long long count = mergeSort(arr, left, mid);
    count += mergeSort(arr, mid + 1, right);
    count += merge(arr, left, mid, right);
    return count;
}


/*
 * Complete the 'countInversions' function below.
 *
 * The function is expected to return a long.
 * The function accepts INTEGER_ARRAY arr as parameter.
 */
long long countInversions(vector<int> arr) {
    if (arr.size() < 2) {
        return 0;
    }

    return mergeSort(arr, 0, arr.size()-1);
}