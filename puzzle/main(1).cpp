#include <iostream>
#include <vector>
#include <set>
#include <stack>
#include <queue>
#include <sstream>
#include <unistd.h>

using namespace std;

struct Position {
    int x, y;
    char color;
    Position(int x, int y, char color) : x(x), y(y), color(color) {}
};

struct Puzzle {
    int num_colors;
    int width;
    int height;
    vector<string> map_2d;
    Position start;
    Position end;
};

struct State {
    Position pos;
    // Stores the path taken to reach this state
    string path;
};

// to store all the solution paths
vector<string> solutions;
set<tuple<int, int, char>> visited;

Puzzle parseInput(){
    int num_colors, width, height;
    cin >> num_colors >> width >> height;
    if (num_colors < 0 || width <= 0 || height <= 0) {
        cerr << "Invalid input: Negative number of colors or non-positive dimensions.\n";
        exit(EXIT_FAILURE);
    }

    Puzzle puzzle = {num_colors, width, height, {}, {0, 0, '^'}, {0, 0, '^'}};

    string line;
    // To consume the newline character after height
    getline(cin, line); 
    for (int i = 0; i < height; ++i) {
        getline(cin, line);
        if (line.size() != width) {
            cerr << "Invalid input: Line width does not match the specified width.\n";
            exit(EXIT_FAILURE);
        }
        puzzle.map_2d.push_back(line);
        for (int j = 0; j < width; ++j) {
            if (line[j] == '@') {
                if (puzzle.start.x != -1) {
                    cerr << "Invalid input: Multiple start positions specified.\n";
                    exit(EXIT_FAILURE);
                }
                puzzle.start = {i, j, '^'};
            }
            if (line[j] == '?') {
                if (puzzle.end.x != -1) {
                    cerr << "Invalid input: Multiple end positions specified.\n";
                    exit(EXIT_FAILURE);
                }
                puzzle.end = {i, j, '^'};
            }
        }
    }

    if (puzzle.start.x == -1 || puzzle.end.x == -1) {
        cerr << "Invalid input: Start or end position not specified.\n";
        exit(EXIT_FAILURE);
    }

    return puzzle;
}

vector<State> getPossibleNextStates(const State& state, const Puzzle& puzzle) {
    vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    vector<State> nextStates;

    for (const auto& dir : directions) {
        int newX = state.pos.x + dir.first;
        int newY = state.pos.y + dir.second;

        if (newX >= 0 && newX < puzzle.height && newY >= 0 && newY < puzzle.width) {
            char newColor = state.pos.color;
            if (isalpha(puzzle.map_2d[newX][newY]) && puzzle.map_2d[newX][newY] != '@' && puzzle.map_2d[newX][newY] != '?') {
                newColor = puzzle.map_2d[newX][newY];
            }

            if (puzzle.map_2d[newX][newY] != '#' && (puzzle.map_2d[newX][newY] == '.' || puzzle.map_2d[newX][newY] == newColor || puzzle.map_2d[newX][newY] == '?')) {
                nextStates.push_back({{newX, newY, newColor}, state.path + to_string(newX) + "," + to_string(newY) + ";"});
            }
        }
    }

    return nextStates;
}

void dfs(const State& state, const Puzzle& puzzle) {
    if (state.pos.x == puzzle.end.x && state.pos.y == puzzle.end.y) {
        solutions.push_back(state.path); // Store the solution path
        return;
    }

    visited.insert({state.pos.x, state.pos.y, state.pos.color});

    vector<State> nextStates = getPossibleNextStates(state, puzzle);
    for (const auto& nextState : nextStates) {
        if (visited.find({nextState.pos.x, nextState.pos.y, nextState.pos.color}) == visited.end()) {
            dfs(nextState, puzzle);
        }
    }
}

void outputMap(const string& solutionPath, const Puzzle& puzzle) {
    // Copy of the original map
    vector<string> map = puzzle.map_2d; 

    stringstream ss(solutionPath);
    string step;
    while (getline(ss, step, ';')) {
        if (step.empty()) continue;
        stringstream stepStream(step);
        int x, y;
        char delim;
        stepStream >> x >> delim >> y;
        // Mark the path on the map
        map[x][y] = '*'; 
    }

    // Print the map with the path
    for (const auto& row : map) {
        cout << row << "\n";
    }
}

void outputList(const string& solutionPath) {
    stringstream ss(solutionPath);
    string step;
    while (getline(ss, step, ';')) {
        if (step.empty()) continue;
        // Print each step
        cout << step << "\n"; 
    }
}

void handleArguments(int argc, char* argv[], bool& listOutput, bool& mapOutput) {
    int opt;
    while ((opt = getopt(argc, argv, "lm")) != -1) {
        switch (opt) {
            case 'l':
                listOutput = true;
                break;
            case 'm':
                mapOutput = true;
                break;
            default:
                cerr << "Usage: " << argv[0] << " [-l] [-m]\n";
                exit(EXIT_FAILURE);
        }
    }
}

int main(int argc, char* argv[]) {
    bool listOutput = false;
    bool mapOutput = false;

    handleArguments(argc, argv, listOutput, mapOutput);

    Puzzle puzzle = parseInput();

    // Initialize the start state with an empty path
    State startState = {puzzle.start, ""};

    // Start the DFS search
    dfs(startState, puzzle);

    // Print all the solution paths
    for (const auto& solution : solutions) {
        cout << "Solution path: " << solution << "\n";
        if (mapOutput) {
            outputMap(solution, puzzle);
        }
        if (listOutput) {
            outputList(solution);
        }
    }

    return 0;
}
