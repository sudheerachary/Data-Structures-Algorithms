#include <bits/stdc++.h>

using namespace std;

class Solution {
    private:
        // Gets the required number of operations to make all values in grid to target using factor
        int getOperationsRequired(vector<int>& gridNumbers, int target, int factor) {
            int operations = 0;
            for (int i = 0; i < gridNumbers.size(); i++) {
                int difference = abs(target-gridNumbers[i]);
                if (difference%factor != 0) {
                    return INT_MAX;
                }
                else {
                    operations += (difference/factor);
                }
            }

            return operations;
        }

    public:
        int minOperations(vector<vector<int>>& grid, int x) {
            vector<int> gridNumbers;
            for (int i = 0; i < grid.size(); i++) {
                for (int j = 0; j < grid[i].size(); j++) {
                    gridNumbers.push_back(grid[i][j]);
                }
            }

            sort(gridNumbers.begin(), gridNumbers.end());

            // Median is the best value to convert each grid value using x
            int median = gridNumbers.size()/2;
            int operations = getOperationsRequired(gridNumbers, gridNumbers[median], x);
            if (gridNumbers.size()%2 == 0) {
                operations = min(operations, getOperationsRequired(gridNumbers, gridNumbers[median-1], x));
            }

            return operations == INT_MAX ? -1 : operations;
        }
};

int main() {

    int x = 2;
    vector<vector<int>> grid = {{2, 4}, {6, 8}};

    Solution solution;
    cout << solution.minOperations(grid, x) << endl;
    return 0;
}