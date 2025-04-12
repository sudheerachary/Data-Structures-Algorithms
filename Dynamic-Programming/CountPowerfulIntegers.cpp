#include <bits/stdc++.h>

using namespace std;

class Solution {
private:
    int limit;
    string startString, finishString, suffix;
    vector<vector<vector<long long int>>> digitDP;

public:
    long long numberOfPowerfulInt(long long start, long long finish, int limit, string s) {
        this->suffix = s;
        this->limit = limit;
        this->startString = to_string(start);
        this->finishString = to_string(finish);

        this->startString = string(finishString.size() - startString.size(), '0') + startString;

        for (int i = 0; i <= finishString.size(); i++) {
            this->digitDP.push_back(vector<vector<long long int>>(2, vector<long long int>(2, -1)));
        }

        return countPowerfulIntegers(0, true, true);
    }

    long long int countPowerfulIntegers(int position, bool lowTight, bool highTight) {

        long long int powerfulIntegers = 0;

        if (position == this->finishString.size()) {
            powerfulIntegers = 1;
            this->digitDP[position][lowTight][highTight] = powerfulIntegers;
            return powerfulIntegers;
        }

        if (this->digitDP[position][lowTight][highTight] != -1) {
            powerfulIntegers = this->digitDP[position][lowTight][highTight];
            return powerfulIntegers;
        }
        
        int upperLimit = highTight ? this->finishString[position] - '0' : this->limit;
        int lowerLimit = lowTight ? this->startString[position] - '0' : 0;

        if (position < this->finishString.size()-this->suffix.size()) {
            for (int digit = lowerLimit; digit <= min(this->limit, upperLimit); digit++) {
                bool newLowTight = lowTight && (digit == lowerLimit);
                bool newHighTight = highTight && (digit == upperLimit);
                powerfulIntegers += countPowerfulIntegers(position+1, newLowTight, newHighTight);
            }
        }
        else {
            int suffixPosition = this->suffix.size()-this->finishString.size()+position;

            if ((highTight && this->suffix[suffixPosition]-'0' > upperLimit)
                || (lowTight && this->suffix[suffixPosition]-'0' < lowerLimit)) {
                powerfulIntegers = 0;
            }
            else {
                bool newLowTight = lowTight && (this->suffix[suffixPosition]-'0' == lowerLimit);
                bool newHighTight = highTight && (this->suffix[suffixPosition]-'0' == upperLimit);
                powerfulIntegers += countPowerfulIntegers(position+1, newLowTight, newHighTight);

            }
        }

        this->digitDP[position][lowTight][highTight] = powerfulIntegers;
        return powerfulIntegers;
    }
};

int main() {
    // Link - https://leetcode.com/problems/count-the-number-of-powerful-integers
    
    long long start = 1;
    long long finish = 6000;
    int limit = 4;
    string s = "124";
    
    Solution solution;
    cout << solution.numberOfPowerfulInt(start, finish, limit, s) << endl;
    return 0;
}