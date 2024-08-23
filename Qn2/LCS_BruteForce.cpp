#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>

using namespace std;

class LCSFinder {
public:
    // Function That Generates all the subsequences of a given string and records them in a hash map
    void generateSubsequences(int index, const string& str, string &current, unordered_map<string, bool>& subseqMap) {

        // Base Case indicating the end of string
        if (index == str.size()) {
            // If current String is not empty, add that to the hash map
            if (!current.empty()) {
                subseqMap[current] = true;
            }
            return;
        }

        // Add the current character to the current string
        current += str[index];
        generateSubsequences(index + 1, str, current, subseqMap);

        // Remove the added Character (Backtracking)
        current.pop_back();

        // Call the recursive function with next index without current character
        generateSubsequences(index + 1, str, current, subseqMap);
    }
    
    // Function that finds longest matching subsequence between two strings
    int longestCommonSubsequenceLength(string & A, string& B) {
        unordered_map<string, bool> subseqMapA;
        unordered_map<string, bool> subseqMapB;

        // Generate all the subsequences of given string using helper functions
        string currString = "";
        generateSubsequences(0, A, currString, subseqMapA);
        currString = "";
        generateSubsequences(0, B, currString, subseqMapB);

        int maxLength = 0;

        // Finding the maximum Length matcing subsequnce by iterating through all the subsequences present in a string.
        for (const auto& pair : subseqMapA) {
            const string& subseq = pair.first;
            if (subseqMapB.find(subseq) != subseqMapB.end()) {
                maxLength = max(maxLength, static_cast<int>(subseq.size()));
            }
        }
        return maxLength;
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

    LCSFinder lcs;

    int length = lcs.longestCommonSubsequenceLength(A, B);

    cout << "Length of Longest Common Subsequence: " << length << endl;
    return 0;
}