#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    // Recursive Function to compute the sub problem of matching two characters of two strings
    int recursiveFunction(const string& text1, const string& text2, int i, int j, vector<vector<int>> &dp) {
        // Base Case indicating the end of string.
        if (i < 0 || j < 0) return 0;

        // This indicates the current subproblem is already and computed and the stored result is returned.
        if(dp[i][j] != -1) return dp[i][j];

        // If match of character is found, pointers are moved accordingly and recursion function is called for next set of pointers.
        if(text1[i] == text2[j]) return dp[i][j] = 1 + recursiveFunction(text1, text2, i - 1, j - 1, dp);

        // If no match is found, then maximum of moving the pointer one and moving pointer 2 is took as the answer.
        // The result is also stored in the dp array avoiding redundant calculations.
        return dp[i][j] = max(recursiveFunction(text1, text2, i - 1, j, dp), recursiveFunction(text1, text2, i, j - 1, dp));
    }

    // Function that calls the recursive function for end of the strings.
    int longestCommonSubsequence(const string& text1, const string& text2) {
        vector<vector<int>> dp(text1.length(), vector<int>(text2.length(), -1));
        return recursiveFunction(text1, text2, text1.length() - 1, text2.length() - 1, dp);
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

    Solution sol;

    int length = sol.longestCommonSubsequence(A, B);

    cout << "Length of Longest Common Subsequence: " << length << endl;
    return 0;
}