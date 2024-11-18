#include <iostream>
#include <vector>
#include <cmath>  // For pow function

using namespace std;

// Function to calculate the sum of all subsequences
long long sumOfSubsequences(const vector<int>& arr) {
    long long sum = 0;
    int n = arr.size();
    
    // The number of subsequences is 2^n, and each element arr[i] appears in exactly half of them
    for (int i = 0; i < n; i++) {
        // Calculate the contribution of arr[i] to all subsequences it is part of
        sum += arr[i] * (1 << (n - 1)); // (1 << (n - 1)) is 2^(n-1)
    }
    
    return sum;
}

int main() {
    vector<int> arr = {1, 2, 3};  // Example array
    cout << "Sum of all subsequences: " << sumOfSubsequences(arr) << endl;
    return 0;
}

