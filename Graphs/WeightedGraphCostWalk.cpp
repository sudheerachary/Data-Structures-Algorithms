#include <bits/stdc++.h>

using namespace std;

class DisjointSetUnion {

    private:
        int nodes;
        vector<int> parent;
        vector<bitset<32>> weight;
        
    public:
        DisjointSetUnion(int nodes) {
            this->nodes = nodes;
            
            this->parent = vector<int>(nodes, -1);
            for (int i = 0; i < this->nodes; i++) {
                this->parent[i] = i;
            }

            // Initialize the weight of each component to 111...111
            this->weight = vector<bitset<32>>(nodes, ~bitset<32>());
        }

        void setUnion(int u, int v, int w) {

            int uParent = this->findParent(u);
            int vParent = this->findParent(v);

            if (uParent != vParent) {
                this->parent[vParent] = uParent;
            }

            // Merge weights of the two u & v components along with the weight of the edge between them
            this->weight[uParent] = this->weight[uParent] & this->weight[vParent] & bitset<32>(w);      
        }

        int findParent(int u) {
            if (this->parent[u] == u) {
                return u;
            }
            else {
                this->parent[u] = this->findParent(this->parent[u]);
            }

            return this->parent[u];
        }

        int componentWeight(int u) {

            if (this->weight[u] == ~bitset<32>()) {
                return 0;
            }

            return this->weight[u].to_ulong();
        }
};

class Solution {

    public:
        vector<int> minimumCost(int n, vector<vector<int>>& edges, vector<vector<int>>& queries) {

            DisjointSetUnion disjointSetUnion = DisjointSetUnion(n);
            for (vector<int> edge : edges) {
                disjointSetUnion.setUnion(edge[0], edge[1], edge[2]);
            }

            vector<int> walkCost = vector<int>(queries.size(), -1);
            for (int i = 0; i < queries.size(); i++) {
                int uParent = disjointSetUnion.findParent(queries[i][0]);
                int vParent = disjointSetUnion.findParent(queries[i][1]);

                if (uParent == vParent) {
                    walkCost[i] = disjointSetUnion.componentWeight(uParent);
                }
            }

            return walkCost;
        }
};

int main()
{     
   // Link - https://leetcode.com/problems/minimum-cost-walk-in-weighted-graph/description/

    int n = 5;
    vector<vector<int>> edges = {{0, 1, 7}, {1, 3, 7}, {1, 2, 1}};
    vector<vector<int>> queries = {{0, 3}, {3, 4}};
    
    Solution solution;
    vector<int> result = solution.minimumCost(n, edges, queries);
    for (int i = 0; i < result.size(); i++) {
        cout << result[i] << " ";
    }
    cout << endl;

   return 0;
}