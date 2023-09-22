#include <iostream>
#include <vector>
#include <set>

using namespace std;

struct Position {
    int x, y;
    char color;
    Position(int x, int y, char color) : x(x), y(y), color(color) {}
};

vector<Position> getNeighbors(const Position& pos, const vector<vector<char>>& grid) {
    vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    vector<Position> neighbors;

    for (const auto& dir : directions) {
        int newX = pos.x + dir.first;
        int newY = pos.y + dir.second;

        if (newX >= 0 && newX < grid.size() && newY >= 0 && newY < grid[0].size()) {
            char newColor = pos.color;
            if (grid[newX][newY] == 'R' || grid[newX][newY] == 'G' || grid[newX][newY] == 'B') {
                newColor = grid[newX][newY];
            }

            if (grid[newX][newY] == '.' || grid[newX][newY] == newColor || grid[newX][newY] == 'T') {
                neighbors.emplace_back(newX, newY, newColor);
            }
        }
    }

    return neighbors;
}

void dfs(const Position& pos, const vector<vector<char>>& grid, set<char>& currentColors, set<set<char>>& uniqueColorSets) {
    if (pos.x == grid.size() - 1 && pos.y == grid[0].size() - 1) {
        uniqueColorSets.insert(currentColors);
        return;
    }

    if (pos.color != 'S') {
        currentColors.insert(pos.color);
    }

    for (const auto& neighbor : getNeighbors(pos, grid)) {
        dfs(neighbor, grid, currentColors, uniqueColorSets);
    }

    if (pos.color != 'S') {
        currentColors.erase(pos.color);
    }
}

int main() {
    int N, M;
    cin >> N >> M;

    vector<vector<char>> grid(N, vector<char>(M));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> grid[i][j];
        }
    }

    set<set<char>> uniqueColorSets;
    set<char> currentColors;
    Position start(0, 0, 'S');
    dfs(start, grid, currentColors, uniqueColorSets);

    cout << uniqueColorSets.size() << endl;

    return 0;
}
