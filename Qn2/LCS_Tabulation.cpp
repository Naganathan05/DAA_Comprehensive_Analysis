#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class LongestCommonSubsequenceSolver {
public:
    // Function to compute LCS of given two strings.
    int computeLCSLength(const string& text1, const string& text2) {
        int m = text1.length();
        int n = text2.length();

        // DP array to store the results of the sub problems.
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (text1[i - 1] == text2[j - 1]) dp[i][j] = 1 + dp[i - 1][j - 1]; // Match
                else dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]); // no Match
            }
        }
        return dp[m][n];
    }
};

// Driver Code
int main() {
    string A, B;

    ifstream inputFile("testCase1.txt");
    if (inputFile.is_open()) {
        getline(inputFile, A);
        getline(inputFile, B);
        inputFile.close();
    } else {
        cout << "Unable to open file" << endl;
        return 1;
    }

    LongestCommonSubsequenceSolver lcs;

    int length = lcs.computeLCSLength(A, B);

    cout << "Length of Longest Common Subsequence: " << length << endl;
    return 0;
}