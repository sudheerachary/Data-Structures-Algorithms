#include <bits/stdc++.h>

using namespace std;

class Solution {
    
    private:

        const int MOD = 1e9+7;

        // Function to find the number of ways to reach the destination using Dijkstra's algorithm
        int dijkstra(int nodes, vector<vector<pair<int, int>>>& graph, int source, int destination) {
            vector<int> waysToReach(nodes, 0);
            vector<long long int> distance(nodes, LLONG_MAX);
            priority_queue<pair<long long int, int>, vector<pair<long long int, int>>, greater<pair<long long int, int>>> traversalQueue;

            distance[source] = 0;
            waysToReach[source] = 1;
            traversalQueue.push({distance[source], source});

            while (!traversalQueue.empty()) {
                pair<long long int, int> node = traversalQueue.top();
                traversalQueue.pop();
                if (node.first > distance[node.second]) {
                    continue;
                }

                for (pair<long long int, int> neighbour : graph[node.second]) {
                    if (node.first + neighbour.first < distance[neighbour.second]) {
                        distance[neighbour.second] = node.first + neighbour.first;
                        
                        // Number of ways to reach the neighbour with shortest distance
                        waysToReach[neighbour.second] = waysToReach[node.second];

                        traversalQueue.push({distance[neighbour.second], neighbour.second});
                    }
                    else if (node.first + neighbour.first == distance[neighbour.second]) {

                        // If the distance is same, then add the number of ways to reach the neighbour
                        waysToReach[neighbour.second] = (waysToReach[neighbour.second] + waysToReach[node.second])%MOD;
                    }                    
                }
            }

            return waysToReach[destination];
        }

    public:

        int countPaths(int n, vector<vector<int>>& roads) {
            vector<vector<pair<int, int>>> graph(n, vector<pair<int, int>>());
            for (vector<int> road : roads) {
                graph[road[0]].push_back({road[2], road[1]});
                graph[road[1]].push_back({road[2], road[0]});
            }

            return dijkstra(n, graph, 0, n-1);
        }
};

int main() {

    // Link - https://leetcode.com/problems/number-of-ways-to-arrive-at-destination/description/

    int n = 7;
    vector<vector<int>> roads = {{0,6,7},{0,1,2},{1,2,3},{1,3,3},{6,3,3},{3,5,1},{6,5,1},{2,5,1},{0,4,5},{4,6,2}};

    Solution solution;
    cout << solution.countPaths(n, roads) << endl;

    return 0;
}