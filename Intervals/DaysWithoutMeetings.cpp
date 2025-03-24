#include <bits/stdc++.h>

using namespace std;

struct Compare {
    // Custom comparator to sort intervals by start time, and by end time if start times are equal
    bool operator()(const vector<int>& x, const vector<int>& y) {
        return x[0] == y[0] ? x[1] < y[1] : x[0] < y[0];
    }
};

class Solution {
    private:
        // Function to check if two intervals overlap
        bool overlap(vector<int> x, vector<int> y) {
            return x[1] >= y[0];
        }

    public:
        int countDays(int days, vector<vector<int>>& meetings) {
            sort(meetings.begin(), meetings.end(), Compare());

            // Merge overlapping meetings
            int left = 0;
            vector<vector<int>> mergedMeetings = vector<vector<int>>();
            while (left < meetings.size()) {
                int right = left+1;
                vector<int> currentMeeting = vector<int>{meetings[left][0], meetings[left][1]};
                while (right < meetings.size() && overlap(currentMeeting, meetings[right])) {
                    currentMeeting[1] = max(currentMeeting[1], meetings[right][1]);
                    right++;
                }

                mergedMeetings.push_back(currentMeeting);
                left = right;
            }

            // Calculate the number of available days
            int startTime = 0;
            int availableDays = 0;
            for (int i = 0; i < mergedMeetings.size(); i++) {
                availableDays += mergedMeetings[i][0]-startTime-1;
                startTime = mergedMeetings[i][1];
            }

            availableDays += days - startTime;

            return availableDays;
        }
};

int main() {

    // Link - https://leetcode.com/problems/count-days-without-meetings

    Solution solution;
    int days = 10;
    vector<vector<int>> meetings = {{5, 7}, {1, 3}, {9, 10}};
    cout << solution.countDays(days, meetings) << endl;
    return 0;
}