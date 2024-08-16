#include <iostream>
#include <vector>
#include <string>

using namespace std;

class LCSOptimizer {
public:
    int longestCommonSubsequence(const string& text1, const string& text2) {
        int m = text1.length();
        int n = text2.length();
        vector<int> prev(n + 1, 0), curr(n + 1, 0);

        for (int i = 1; i <= m; i++) {
            prev = curr;
            for (int j = 1; j <= n; j++) {
                if (text1[i - 1] == text2[j - 1]) curr[j] = 1 + prev[j - 1];
                else curr[j] = max(prev[j], curr[j - 1]);
            }
        }
        return curr[n];
    }
};

int main() {
    LCSOptimizer lcsOptimizer;

    // Test case 1
    string text1 = "ABCBDAB";
    string text2 = "BDCAB";
    cout << "Length of Longest Common Subsequence: " << lcsOptimizer.longestCommonSubsequence(text1, text2) << endl;

    // Test case 2
    string text1_2 = "AXYT";
    string text2_2 = "AYZX";
    cout << "Length of Longest Common Subsequence: " << lcsOptimizer.longestCommonSubsequence(text1_2, text2_2) << endl;

    // Test case 3
    string text1_3 = "AGGTAB";
    string text2_3 = "GXTXAYB";
    cout << "Length of Longest Common Subsequence: " << lcsOptimizer.longestCommonSubsequence(text1_3, text2_3) << endl;

    return 0;
}