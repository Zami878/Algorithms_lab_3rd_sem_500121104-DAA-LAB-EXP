#include <iostream>
#include <vector>
#include <algorithm> 

using namespace std;
using namespace chrono;


int greedyKnapsack(vector<int>& values, vector<int>& weights, int capacity) {
    int n = values.size();
    vector<pair<double, int>> ratio(n);  
    for (int i = 0; i < n; ++i) {
        ratio[i] = { (double)values[i] / weights[i], i }; 
    
    
    sort(ratio.rbegin(), ratio.rend());  
    
    int totalValue = 0;
    int remainingCapacity = capacity;
    for (auto& r : ratio) {
        int idx = r.second;
        if (weights[idx] <= remainingCapacity) {
            totalValue += values[idx];
            remainingCapacity -= weights[idx];
        }
    }
    return totalValue;
}


int dpKnapsack(vector<int>& values, vector<int>& weights, int capacity) {
    int n = values.size();
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));
    
    for (int i = 1; i <= n; ++i) {
        for (int w = 1; w <= capacity; ++w) {
            if (weights[i - 1] <= w) {
                dp[i][w] = max(dp[i - 1][w], values[i - 1] + dp[i - 1][w - weights[i - 1]]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }
    
    return dp[n][capacity];
}

int main() {
    
    vector<vector<int>> testCasesValues = {
        {60, 100, 120},
        {10, 20, 30, 50},
        {50, 100, 150, 200},
        {60, 40, 30, 10}
    };
    vector<vector<int>> testCasesWeights = {
        {10, 20, 30},
        {10, 20, 30, 40},
        {20, 30, 40, 50},
        {10, 20, 30, 40}
    };
    vector<int> testCasesCapacities = {50, 50, 100, 60};

    for (int i = 0; i < testCasesValues.size(); ++i) {
        vector<int>& values = testCasesValues[i];
        vector<int>& weights = testCasesWeights[i];
        int capacity = testCasesCapacities[i];
        
        
        auto startGreedy = high_resolution_clock::now();
        int greedyResult = greedyKnapsack(values, weights, capacity);
        auto endGreedy = high_resolution_clock::now();
        auto durationGreedy = duration_cast<microseconds>(endGreedy - startGreedy);

       
        auto startDP = high_resolution_clock::now();
        int dpResult = dpKnapsack(values, weights, capacity);
        auto endDP = high_resolution_clock::now();
        auto durationDP = duration_cast<microseconds>(endDP - startDP);

        
        cout << "Test Case " << i + 1 << ":\n";
        cout << "Greedy Result: " << greedyResult << "\n";
        cout << "Greedy Time: " << durationGreedy.count() << " microseconds\n";
        cout << "Dynamic Programming Result: " << dpResult << "\n";
        cout << "Dynamic Programming Time: " << durationDP.count() << " microseconds\n";
        cout << endl;
    }

    return 0;
}

