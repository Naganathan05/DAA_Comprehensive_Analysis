#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <utility>

using namespace std;

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator ()(const std::pair<T1, T2> &p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1 ^ h2;
    }
};

class SnakeLadder {
public:
    bool checkDuplicates(const unordered_map<pair<int, int>, pair<int, int>, pair_hash> &snakes, 
                         const unordered_map<pair<int, int>, pair<int, int>, pair_hash> &ladders) {
        unordered_set<pair<int, int>, pair_hash> positions;
        for (const auto& [start, end] : snakes) {
            if (!positions.insert(start).second || !positions.insert(end).second) return false;
        }
        for (const auto& [start, end] : ladders) {
            if (!positions.insert(start).second || !positions.insert(end).second) return false;
        }
        return true;
    }

    bool checkValidPath(unordered_map<pair<int, int>, pair<int, int>, pair_hash> &Snakes,
                        unordered_map<pair<int, int>, pair<int, int>, pair_hash> &Ladders,
                        int dimension, int i, int j, vector<vector<int>> &dp) {

        if (i == dimension - 1 && j == dimension - 1) return true;
        if (i < 0 || j < 0 || i >= dimension || j >= dimension) return false;

        if (dp[i][j] != -1) return dp[i][j];

        vector<int> diceRolls = {1, 2, 3, 4, 5, 6};
        bool reachEnd = false;
        
        for (int roll : diceRolls) {
            int newY = (j + roll) % dimension;
            int newX = i + (j + roll) / dimension;

            if (Snakes.find({newX, newY}) != Snakes.end()) {
                pair<int, int> snakeTail = Snakes[{newX, newY}];
                newX = snakeTail.first;
                newY = snakeTail.second;
            }
            else if (Ladders.find({newX, newY}) != Ladders.end()) {
                pair<int, int> ladderTop = Ladders[{newX, newY}];
                newX = ladderTop.first;
                newY = ladderTop.second;
            }

            reachEnd |= checkValidPath(Snakes, Ladders, dimension, newX, newY, dp);
            if (reachEnd) break;
        }
        return dp[i][j] = reachEnd;
    }

    bool viablePath(unordered_map<pair<int, int>, pair<int, int>, pair_hash> &Snakes,
                    unordered_map<pair<int, int>, pair<int, int>, pair_hash> &Ladders,
                    int dimension, int i, int j, int k, vector<vector<int>> &dp) {

        if (i == dimension - 1 && j == dimension - 1) return true;
        if (i < 0 || j < 0 || i >= dimension || j >= dimension) return false;

        if (dp[i][j] != -1) return dp[i][j];

        bool reachEnd = false;
        
        int newY = (j + k) % dimension;
        int newX = i + (j + k) / dimension;

        if (Snakes.find({newX, newY}) != Snakes.end()) {
            pair<int, int> snakeTail = Snakes[{newX, newY}];
            newX = snakeTail.first;
            newY = snakeTail.second;
        }
        else if (Ladders.find({newX, newY}) != Ladders.end()) {
            pair<int, int> ladderTop = Ladders[{newX, newY}];
            newX = ladderTop.first;
            newY = ladderTop.second;
        }

        reachEnd = viablePath(Snakes, Ladders, dimension, newX, newY, k, dp);
        return dp[i][j] = reachEnd;
    }

    bool DFS(unordered_map<pair<int, int>, pair<int, int>, pair_hash> &Snakes,
            unordered_map<pair<int, int>, pair<int, int>, pair_hash> &Ladders,
            int i, int j, int dimension, vector<vector<bool>> &visited, vector<vector<bool>> &recStack) {
        
        visited[i][j] = true;
        recStack[i][j] = true;

        if (Snakes.find({i, j}) != Snakes.end()) {
            pair<int, int> snakeTail = Snakes[{i, j}];
            if (!visited[snakeTail.first][snakeTail.second]) {
                if (DFS(Snakes, Ladders, snakeTail.first, snakeTail.second, dimension, visited, recStack)) {
                    return true;
                }
            } else if (recStack[snakeTail.first][snakeTail.second]) {
                return true;
            }
        }

        if (Ladders.find({i, j}) != Ladders.end()) {
            pair<int, int> ladderTop = Ladders[{i, j}];
            if (!visited[ladderTop.first][ladderTop.second]) {
                if (DFS(Snakes, Ladders, ladderTop.first, ladderTop.second, dimension, visited, recStack)) {
                    return true;
                }
            } else if (recStack[ladderTop.first][ladderTop.second]) {
                return true;
            }
        }

        for (int k = 1; k <= 6; k++) {
            int newY = (j + k) % dimension;
            int newX = i + (j + k) / dimension;

            if (newX < dimension && newY < dimension) {
                if (!visited[newX][newY]) {
                    if (DFS(Snakes, Ladders, newX, newY, dimension, visited, recStack)) {
                        return true;
                    }
                } else if (recStack[newX][newY]) {
                    return true;
                }
            }
        }

        // Backtrack
        recStack[i][j] = false;
        return false;
    }

    bool checkCycle(unordered_map<pair<int, int>, pair<int, int>, pair_hash> &Snakes,
                    unordered_map<pair<int, int>, pair<int, int>, pair_hash> &Ladders,
                    int dimension){
        
        vector<vector<bool>> visited(dimension, vector<bool> (dimension, false));
        vector<vector<bool>> recStack(dimension, vector<bool> (dimension, false));

        return DFS(Snakes, Ladders, 0, 0, dimension, visited, recStack);
    }

    void fillSnakeLadder(unordered_map<pair<int, int>, pair<int, int>, pair_hash> &adjList, int numInputs){
        for(int i = 0; i < numInputs; i++){
            int startX, startY, endX, endY;
            cout << "Enter The Starting X Coordinate: ";
            cin >> startX;
            cout << "Enter The Starting Y Coordinate: ";
            cin >> startY;
            cout << "Enter The Ending X Coordinate: ";
            cin >> endX;
            cout << "Enter The Ending Y Coordinate: ";
            cin >> endY;
            
            adjList[{startX, startY}] = {endX, endY};
        }
    }
};

int main() {
    SnakeLadder game;

    int dimension = 5;

    unordered_map<pair<int, int>, pair<int, int>, pair_hash> snakes;
    unordered_map<pair<int, int>, pair<int, int>, pair_hash> ladders;

    cout << "Test Case 1: Valid board without cycles" << endl;
    snakes = {
        {{1, 1}, {2, 2}},
        {{2, 0}, {3, 1}},
        {{0, 3}, {1, 4}}
    };
    ladders = {
        {{0, 1}, {2, 1}},
        {{1, 2}, {2, 3}},
        {{3, 0}, {4, 0}}
    };
    cout << "Checking for cycles: " << (game.checkCycle(snakes, ladders, dimension) ? "Cycle detected!" : "No cycles detected.") << endl;
    cout << "----------------------------------------------------------" << endl;

    cout << "Test Case 2: Board with a cycle" << endl;
    snakes = {
        {{1, 1}, {2, 2}},
        {{2, 0}, {3, 1}},
        {{3, 1}, {1, 1}}
    };
    ladders = {
        {{0, 1}, {2, 1}},
        {{1, 2}, {2, 3}},
        {{3, 0}, {4, 0}}
    };
    cout << "Checking for cycles: " << (game.checkCycle(snakes, ladders, dimension) ? "Cycle detected!" : "No cycles detected.") << endl;
    cout << "----------------------------------------------------------" << endl;

    cout << "Test Case 3: Duplicate snakes or ladders" << endl;
    snakes = {
        {{1, 1}, {2, 2}},
        {{2, 2}, {1, 1}}
    };
    ladders = {
        {{0, 1}, {2, 1}},
        {{1, 2}, {2, 3}},
        {{2, 1}, {0, 1}}
    };
    cout << "Checking for duplicates: " << (game.checkDuplicates(snakes, ladders) ? "No duplicates detected!" : "Duplicates detected!") << endl;
    cout << "----------------------------------------------------------" << endl;

    cout << "Test Case 4: Large board" << endl;
    dimension = 10;
    snakes = {
        {{1, 1}, {3, 3}},
        {{2, 2}, {4, 4}},
        {{5, 5}, {7, 7}},
        {{6, 6}, {8, 8}}
    };
    ladders = {
        {{0, 1}, {2, 2}},
        {{1, 2}, {3, 3}},
        {{2, 3}, {4, 4}},
        {{3, 4}, {5, 5}}
    };
    cout << "Checking for cycles: " << (game.checkCycle(snakes, ladders, dimension) ? "Cycle detected!" : "No cycles detected.") << endl;
    cout << "----------------------------------------------------------" << endl;

    return 0;
}