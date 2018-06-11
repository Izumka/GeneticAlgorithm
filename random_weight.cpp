#include <iostream>
#include <random>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int findCeilVec(vector<int> arr, int r, int l, int h){
    int mid;
    while (l < h)
    {
        mid = l + ((h - l) >> 1);  // Same as mid = (l+h)/2
        (r > arr.at(mid)) ? (l = mid + 1) : (h = mid);
    }
    return (arr.at(l) >= r) ? l : -1;
}

int myRandVec(vector<int> arr, vector<int> freq, int n){
    vector<int> prefix;
    int j;

    prefix.push_back(arr.at(0));

    for (j = 1; j < n; ++j)
        prefix.push_back(prefix.at(j - 1) + arr.at(j));

    // prefix[n-1] is sum of all frequencies. Generate a random number
    // with value from 1 to this sum
    int r = (rand() % prefix.at(n - 1)) + 1;

    // Find index of ceiling of r in prefix arrat
    int indexc = findCeilVec(prefix, r, 0, n - 1);
    return arr.at(indexc);

}

int main()
{
    vector<int> arr  = {1, 2, 3, 4, 5, 6, 7};
    vector<int> freq = {10, 5, 20, 100, 1, 1, 10};
    int i;
    int n = arr.size();

    // Use a different seed value for every run.
    srand(time(NULL));

    // Let us generate 10 random numbers accroding to
    // given distribution
    string a1 = "";
    string a2 = "";

    for (int i = 0; i < 7; i++) {
        int a = myRandVec(arr, freq, n);
        a1 += to_string(a);
        int b = myRandVec(arr, freq, n);
        a2 += to_string(b);
    }
    cout << a1 << "\n" << a2 << "\n";

    return 0;
}
