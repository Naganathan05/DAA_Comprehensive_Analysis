#include <iostream>
#include <fstream>
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

    LCSOptimizer lcs;

    int length = lcs.longestCommonSubsequence(A, B);

    cout << "Length of Longest Common Subsequence: " << length << endl;
    return 0;
}