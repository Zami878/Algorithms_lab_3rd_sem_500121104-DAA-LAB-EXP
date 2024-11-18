#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <chrono>

using namespace std;
using namespace std::chrono;


void dijkstra(const vector<vector<pair<int, int>>>& graph, int src, vector<int>& dist) {
    int n = graph.size();
    dist.assign(n, INT_MAX);
    dist[src] = 0;
    
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, src});
    
    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();
        
        if (d > dist[u]) continue;
        
        for (auto& edge : graph[u]) {
            int v = edge.first;
            int weight = edge.second;
            
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }
}


void bellmanFord(const vector<vector<pair<int, int>>>& graph, int src, vector<int>& dist) {
    int n = graph.size();
    dist.assign(n, INT_MAX);
    dist[src] = 0;
    
    for (int i = 1; i < n; ++i) {
        bool updated = false;
        for (int u = 0; u < n; ++u) {
            for (auto& edge : graph[u]) {
                int v = edge.first;
                int weight = edge.second;
                
                if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    updated = true;
                }
            }
        }
        if (!updated) break;
    }
}

h
vector<vector<pair<int, int>>> generateRandomGraph(int n, double density) {
    vector<vector<pair<int, int>>> graph(n);
    
    for (int u = 0; u < n; ++u) {
        for (int v = u + 1; v < n; ++v) {
            if (rand() % 100 < density * 100) {
                int weight = rand() % 10 + 1;
                graph[u].push_back({v, weight});
                graph[v].push_back({u, weight});
            }
        }
    }
    return graph;
}

int main() {
    vector<int> test_sizes = {100, 200, 500, 1000}; 
    double density = 0.2; 
    
    for (int n : test_sizes) {
        
        
        auto graph = generateRandomGraph(n, density);
        vector<int> dist(n);
        
     
        auto start = high_resolution_clock::now();
        dijkstra(graph, 0, dist);
        auto end = high_resolution_clock::now();
        auto durationDijkstra = duration_cast<milliseconds>(end - start);
        cout << "Test Size: " << n << " | Dijkstra Time: " << durationDijkstra.count() << " milliseconds" << endl;

       
        start = high_resolution_clock::now();
        bellmanFord(graph, 0, dist);
        end = high_resolution_clock::now();
        auto durationBellmanFord = duration_cast<milliseconds>(end - start);
        cout << "Test Size: " << n << " | Bellman-Ford Time: " << durationBellmanFord.count() << " milliseconds" << endl;
    }

    return 0;
}

