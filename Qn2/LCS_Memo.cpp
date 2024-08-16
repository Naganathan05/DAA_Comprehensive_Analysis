#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    int recursiveFunction(const string& text1, const string& text2, int i, int j, vector<vector<int>> &dp) {
        if (i < 0 || j < 0) return 0;

        if(dp[i][j] != -1) return dp[i][j];

        if(text1[i] == text2[j]) return dp[i][j] = 1 + recursiveFunction(text1, text2, i - 1, j - 1, dp);

        return dp[i][j] = max(recursiveFunction(text1, text2, i - 1, j, dp), recursiveFunction(text1, text2, i, j - 1, dp));
    }

    int longestCommonSubsequence(const string& text1, const string& text2) {
        vector<vector<int>> dp(text1.length(), vector<int>(text2.length(), -1));
        return recursiveFunction(text1, text2, text1.length() - 1, text2.length() - 1, dp);
    }
};

int main() {
    Solution sol;

    // Test case 1
    string text1 = "ABCBDAB";
    string text2 = "BDCAB";
    cout << "Length of Longest Common Subsequence: " << sol.longestCommonSubsequence(text1, text2) << endl;

    // Test case 2
    string text1_2 = "AXYT";
    string text2_2 = "AYZX";
    cout << "Length of Longest Common Subsequence: " << sol.longestCommonSubsequence(text1_2, text2_2) << endl;

    // Test case 3
    string text1_3 = "AGGTAB";
    string text2_3 = "GXTXAYB";
    cout << "Length of Longest Common Subsequence: " << sol.longestCommonSubsequence(text1_3, text2_3) << endl;

    return 0;
}