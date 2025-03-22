#include <bits/stdc++.h>

using namespace std;

class Solution {
   public:
       int countCompleteComponents(int n, vector<vector<int>>& edges) {
           vector<vector<int>> graph(n, vector<int>());
           for (int i = 0; i < edges.size(); i++) {
               graph[edges[i][0]].push_back(edges[i][1]);
               graph[edges[i][1]].push_back(edges[i][0]);
           }

           int completeComponents = 0;
           vector<bool> visited(n, false);
           for (int i = 0; i < n; i++) {
               if (!visited[i]) {
                   visited[i] = true;
                   pair<int, int> nodeEdgeCount = depthFirstSearch(graph, visited, i);
                   if ((nodeEdgeCount.first*(nodeEdgeCount.first-1)/2) == (nodeEdgeCount.second/2)) {
                       completeComponents++;
                   }
               }
           }

           return completeComponents;
       }

   private:
       pair<int, int> depthFirstSearch(vector<vector<int>>& graph, vector<bool>& visited, int node) {
           pair<int, int> nodeEdgeCount = {1, 0};
           for (int neighbour : graph[node]) {
               if (!visited[neighbour]) {
                   visited[neighbour] = true;
                   pair<int, int> neighbourNodeEdgeCount = depthFirstSearch(graph, visited, neighbour);
                   nodeEdgeCount.first += neighbourNodeEdgeCount.first;
                   nodeEdgeCount.second += neighbourNodeEdgeCount.second;
               }

               nodeEdgeCount.second += 1;
           }

           return nodeEdgeCount;
       }
};

int main()
{     
   // Link - https://leetcode.com/problems/count-the-number-of-complete-components/description/
   
   int n = 6;
   vector<vector<int>> edges = {{0, 1}, {0, 2}, {1, 2}, {3, 4}};
   
   Solution solution;
   cout << solution.countCompleteComponents(n, edges) << endl;

   return 0;
}