#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <numeric>
#include <algorithm>
#include <queue>
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
                        int dimension, int i, int j, vector<vector<int>> &dp, vector<vector<bool>> &visited) {

        if (i == dimension - 1 && j == dimension - 1) return true;
        if (i < 0 || j < 0 || i >= dimension || j >= dimension || visited[i][j]) return false;

        if (dp[i][j] != -1) return dp[i][j];
        visited[i][j] = true;

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

            reachEnd |= checkValidPath(Snakes, Ladders, dimension, newX, newY, dp, visited);
            if (reachEnd) break;
        }
        visited[i][j] = false;
        return dp[i][j] = reachEnd;
    }

    int shortestPath(unordered_map<pair<int, int>, pair<int, int>, pair_hash> &Snakes,
                      unordered_map<pair<int, int>, pair<int, int>, pair_hash> &Ladders,
                      int n, vector<pair<int, int>> &cells, vector<vector<int>> &mapNumbers){
        vector<bool> visited(n * n + 1, false);
        queue<pair<int, int>> fifo;
        fifo.push({0, 1});
        visited[1] = true;
        while (!fifo.empty()) {
            int currSteps = fifo.front().first;
            int curr = fifo.front().second;
            fifo.pop();

            if(curr == n * n) return currSteps + 3;

            for (int next = curr + 1; next <= min(curr + 6, n * n); next++) {
                auto [row, column] = cells[next];
                int destination = next;
                if(Snakes.find({row, column}) != Snakes.end()) {
                    auto snakeTail = Snakes[{row, column}];
                    destination = mapNumbers[snakeTail.first][snakeTail.second];
                }
                if(Ladders.find({row, column}) != Ladders.end()) {
                    auto ladderTop = Ladders[{row, column}];
                    destination = mapNumbers[ladderTop.first][ladderTop.second];
                }
                if(!visited[destination]){
                    visited[destination] = true;
                    fifo.push({currSteps + 1, destination});
                }
            }
        }
        return -1;
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

    void fillSnakeLadder(unordered_map<pair<int, int>, pair<int, int>, pair_hash> &Snakes, unordered_map<pair<int, int>, pair<int, int>, pair_hash> &Ladders, vector<pair<int, int>> &cells){
        int numInputs;
        cin >> numInputs;

        for(int i = 0; i < numInputs; i++){
            int start, startY, end, endY;
            string item;
            cin >> item;
            cin >> start;
            cin >> end;
            
            if(item == "Snake") Snakes[cells[start]] = cells[end];
            else Ladders[cells[start]] = cells[end];
        }
        return;
    }
};

int main() {
    SnakeLadder game;

    int dimension = 10, lbl = 1;

    unordered_map<pair<int, int>, pair<int, int>, pair_hash> snakes;
    unordered_map<pair<int, int>, pair<int, int>, pair_hash> ladders;

    vector<pair<int, int>> cells(101);
    vector<vector<int>> mapNumbers(10, vector<int> (10, 0));
    vector<int> columns(10);
    iota(columns.begin(), columns.end(), 0);
    for (int row = 9; row >= 0; row--) {
        for (int column : columns) {
            cells[lbl] = {row, column};
            mapNumbers[row][column] = lbl;
            lbl += 1;
        }
        reverse(columns.begin(), columns.end());
    }
    game.fillSnakeLadder(snakes, ladders, cells);

    cout << "------------------------------------------------------------" << endl;
    cout << "Checking for cycles: " << (game.checkCycle(snakes, ladders, dimension) ? "Cycle detected!" : "No cycles detected.") << endl;
    cout << "----------------------------------------------------------" << endl;

    cout << "Checking for duplicates: " << (game.checkDuplicates(snakes, ladders) ? "No duplicates detected!" : "Duplicates detected!") << endl;
    cout << "----------------------------------------------------------" << endl;

    cout << "Shortest Path: " << game.shortestPath(snakes, ladders, dimension, cells, mapNumbers) << endl;
    cout << "----------------------------------------------------------" << endl;
    return 0;
}