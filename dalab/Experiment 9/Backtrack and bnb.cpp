#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>

using namespace std;


int backtrackKnapsack(const vector<int>& weights, const vector<int>& values, int W, int n) {
    if (n == 0 || W == 0)
        return 0;

    
    if (weights[n - 1] > W)
        return backtrackKnapsack(weights, values, W, n - 1);

    int include = values[n - 1] + backtrackKnapsack(weights, values, W - weights[n - 1], n - 1);
    int exclude = backtrackKnapsack(weights, values, W, n - 1);

    return max(include, exclude);
}


#include <queue>

struct Node {
    int level;
    int profit;
    int weight;
    double bound;
};

double bound(Node u, int n, int W, const vector<int>& weights, const vector<int>& values) {
    if (u.weight >= W) return 0;

    double profitBound = u.profit;
    int j = u.level + 1;
    int totalWeight = u.weight;

    while (j < n && totalWeight + weights[j] <= W) {
        totalWeight += weights[j];
        profitBound += values[j];
        j++;
    }

    if (j < n) {
        profitBound += (W - totalWeight) * values[j] / (double)weights[j];
    }

    return profitBound;
}

int branchBoundKnapsack(const vector<int>& weights, const vector<int>& values, int W, int n) {
    queue<Node> q;
    Node u, v;
    u.level = -1;
    u.profit = u.weight = 0;
    q.push(u);

    int maxProfit = 0;

    while (!q.empty()) {
        u = q.front();
        q.pop();

        if (u.level == n - 1) continue;

        v.level = u.level + 1;

      
        v.weight = u.weight + weights[v.level];
        v.profit = u.profit + values[v.level];

        if (v.weight <= W && v.profit > maxProfit)
            maxProfit = v.profit;

        v.bound = bound(v, n, W, weights, values);
        if (v.bound > maxProfit) q.push(v);

        
        v.weight = u.weight;
        v.profit = u.profit;
        v.bound = bound(v, n, W, weights, values);
        if (v.bound > maxProfit) q.push(v);
    }

    return maxProfit;
}



int dpKnapsack(const vector<int>& weights, const vector<int>& values, int W, int n) {
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= W; w++) {
            if (weights[i - 1] <= w) {
                dp[i][w] = max(dp[i - 1][w], values[i - 1] + dp[i - 1][w - weights[i - 1]]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    return dp[n][W];
}




int main() {
    vector<int> weights = {10, 20, 30};  
    vector<int> values = {60, 100, 120}; 
    int W = 50; 
    int n = weights.size();

  
    auto start = chrono::high_resolution_clock::now();
    int backtrackResult = backtrackKnapsack(weights, values, W, n);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> backtrackDuration = end - start;

    
    start = chrono::high_resolution_clock::now();
    int branchBoundResult = branchBoundKnapsack(weights, values, W, n);
    end = chrono::high_resolution_clock::now();
    chrono::duration<double> branchBoundDuration = end - start;


    start = chrono::high_resolution_clock::now();
    int dpResult = dpKnapsack(weights, values, W, n);
    end = chrono::high_resolution_clock::now();
    chrono::duration<double> dpDuration = end - start;

    cout << "Backtracking Result: " << backtrackResult << ", Time: " << backtrackDuration.count() << " seconds" << endl;
    cout << "Branch & Bound Result: " << branchBoundResult << ", Time: " << branchBoundDuration.count() << " seconds" << endl;
    cout << "Dynamic Programming Result: " << dpResult << ", Time: " << dpDuration.count() << " seconds" << endl;

    return 0;
}

