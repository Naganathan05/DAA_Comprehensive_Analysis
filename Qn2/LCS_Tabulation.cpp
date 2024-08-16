#include <iostream>
#include <vector>
#include <string>

using namespace std;

class LongestCommonSubsequenceSolver {
public:
    int computeLCSLength(const string& text1, const string& text2) {
        int m = text1.length();
        int n = text2.length();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (text1[i - 1] == text2[j - 1]) dp[i][j] = 1 + dp[i - 1][j - 1];
                else dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
        return dp[m][n];
    }
};

int main() {
    LongestCommonSubsequenceSolver lcsSolver;

    // Test case 1
    string text1 = "ABCBDAB";
    string text2 = "BDCAB";
    cout << "Length of Longest Common Subsequence: " << lcsSolver.computeLCSLength(text1, text2) << endl;

    // Test case 2
    string text1_2 = "AXYT";
    string text2_2 = "AYZX";
    cout << "Length of Longest Common Subsequence: " << lcsSolver.computeLCSLength(text1_2, text2_2) << endl;

    // Test case 3
    string text1_3 = "AGGTAB";
    string text2_3 = "GXTXAYB";
    cout << "Length of Longest Common Subsequence: " << lcsSolver.computeLCSLength(text1_3, text2_3) << endl;

    return 0;
}