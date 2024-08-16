#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>

using namespace std;

class LCSFinder {
public:
    void generateSubsequences(int index, const string& str, string &current, unordered_map<string, bool>& subseqMap) {
        if (index == str.size()) {
            if (!current.empty()) {
                subseqMap[current] = true;
            }
            return;
        }

        current += str[index];
        generateSubsequences(index + 1, str, current, subseqMap);
        current.pop_back();

        generateSubsequences(index + 1, str, current, subseqMap);
    }

    int longestCommonSubsequenceLength(string & A, string& B) {
        unordered_map<string, bool> subseqMapA;
        unordered_map<string, bool> subseqMapB;

        string currString = "";
        generateSubsequences(0, A, currString, subseqMapA);
        currString = "";
        generateSubsequences(0, B, currString, subseqMapB);

        int maxLength = 0;

        for (const auto& pair : subseqMapA) {
            const string& subseq = pair.first;
            if (subseqMapB.find(subseq) != subseqMapB.end()) {
                maxLength = max(maxLength, static_cast<int>(subseq.size()));
            }
        }
        return maxLength;
    }
};

int main() {
    string A = "ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc";
    string B = "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb";
    LCSFinder lcs = LCSFinder();

    int length = lcs.longestCommonSubsequenceLength(A, B);

    cout << "Length of Longest Common Subsequence: " << length << endl;
    return 0;
}
