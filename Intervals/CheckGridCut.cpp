#include <bits/stdc++.h>

using namespace std;

class Solution {

    private:
        bool overlap(vector<int>& x, vector<int>& y) {
            return x[1] > y[0];
        }

        vector<vector<int>> mergeIntervals(vector<vector<int>>& intervals) {
            int left = 0;
            vector<vector<int>> mergedIntervals = vector<vector<int>>();
            while (left < intervals.size()) {
                int right = left+1;
                vector<int> currentInterval = vector<int>{intervals[left][0], intervals[left][1]};
                while (right < intervals.size() && overlap(currentInterval, intervals[right])) {
                    currentInterval[1] = max(currentInterval[1], intervals[right][1]);
                    right++;
                }

                mergedIntervals.push_back(currentInterval);
                left = right;
            }

            return mergedIntervals;
        }

    public:
        bool checkValidCuts(int n, vector<vector<int>>& rectangles) {
            vector<vector<int>> xCoordinates = vector<vector<int>>();
            vector<vector<int>> yCoordinates = vector<vector<int>>();
            for (int i = 0; i < rectangles.size(); i++) {
                xCoordinates.push_back(vector<int>{rectangles[i][0], rectangles[i][2]});
                yCoordinates.push_back(vector<int>{rectangles[i][1], rectangles[i][3]});
            }

            sort(xCoordinates.begin(), xCoordinates.end(), [](vector<int>& x, vector<int>& y){
                return x[0] == y[0] ? x[1] < y[1] : x[0] < y[0];
            });

            sort(yCoordinates.begin(), yCoordinates.end(), [](vector<int>& x, vector<int>& y){
                return x[0] == y[0] ? x[1] < y[1] : x[0] < y[0];
            });

            vector<vector<int>> mergedXCoordinates = mergeIntervals(xCoordinates);
            vector<vector<int>> mergedYCoordinates = mergeIntervals(yCoordinates);

            return mergedXCoordinates.size() >= 3 || mergedYCoordinates.size() >= 3;
        }
};

int main() {

    // Link - https://leetcode.com/problems/check-if-grid-can-be-cut-into-sections/description

    int n = 5;
    vector<vector<int>> rectangles = {{1,0,5,2},{0,2,2,4},{3,2,5,3},{0,4,4,5}};

    Solution solution;
    cout << solution.checkValidCuts(n, rectangles) << endl;

    return 0;
}