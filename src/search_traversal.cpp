#include "search_traversal.h"



std::vector<std::pair<int, int>> searchAlgorithm::reconstruct_path(std::map<std::pair<int, int>, std::pair<int, int>> &parent, std::pair<int, int> start, std::pair<int, int> current) {
    if (current == start) {
        return {start};
    }
    auto path = reconstruct_path(parent, start, parent[current]);
    path.push_back(current);
    return path;
}

std::pair<std::vector<std::pair<int, int>>, int> searchAlgorithm::recursive_bfs(std::vector<std::vector<int>> &grid, std::pair<int, int> start, std::pair<int, int> destination, std::queue<std::tuple<int, int, int>> &queue, std::set<std::pair<int, int>> &visited, std::map<std::pair<int, int>, std::pair<int, int>> &parent) {
    if (queue.empty()) {
        return {{}, -1};
    }

    int current_row, current_col, steps;
    std::tie(current_row, current_col, steps) = queue.front();
    queue.pop();

    if (std::make_pair(current_row, current_col) == destination) {
        auto path = reconstruct_path(parent, start, {current_row, current_col});
        return {path, steps};
    }

    std::vector<std::pair<int, int>> moves = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int R = grid.size(), C = grid[0].size();

    for (const auto &[row_delta, col_delta] : moves) {
        int next_row = current_row + row_delta;
        int next_col = current_col + col_delta;

        if (0 <= next_row && next_row < R && 0 <= next_col && next_col < C && grid[next_row][next_col] == 0 && visited.find({next_row, next_col}) == visited.end()) {
            visited.insert({next_row, next_col});
            queue.push({next_row, next_col, steps + 1});
            parent[{next_row, next_col}] = {current_row, current_col};
        }
    }

    return recursive_bfs(grid, start, destination, queue, visited, parent);
}

std::pair<std::vector<std::pair<int, int>>, int> searchAlgorithm::iterative_bfs(const std::vector<std::vector<int>>& grid,
    const std::pair<int, int>& start, const std::pair<int, int>& destination) {
    std::queue<std::tuple<int, int, int>> queue;
    std::set<std::pair<int, int>> visited;
    std::map<std::pair<int, int>, std::pair<int, int>> parent;

    queue.push({start.first, start.second, 0});
    visited.insert(start);
    parent[start] = {-1, -1};

    std::vector<std::pair<int, int>> moves = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int R = grid.size();
    int C = grid[0].size();

    while (!queue.empty()) {
        int current_row, current_col, steps;
        std::tie(current_row, current_col, steps) = queue.front();
        queue.pop();

        if (std::pair<int, int>(current_row, current_col) == destination) {
            auto path = reconstruct_path(parent, start, {current_row, current_col});
            return {path, steps};
        }

        for (const auto& [row_delta, col_delta] : moves) {
            int next_row = current_row + row_delta;
            int next_col = current_col + col_delta;

            if (0 <= next_row && next_row < R && 0 <= next_col && next_col < C &&
                grid[next_row][next_col] == 0 &&
                visited.find({next_row, next_col}) == visited.end()) {
                visited.insert({next_row, next_col});
                queue.push({next_row, next_col, steps + 1});
                parent[{next_row, next_col}] = {current_row, current_col};
            }
        }
    }

    return {{}, -1};
}


std::vector<std::vector<int>> searchAlgorithm::createGrid(int width, int height){
    std::vector<std::vector<int>> grid;
    // Initialize grid with 0's
    for (int i = 0; i < height; i++){
        std::vector<int> row;
        for (int j = 0; j < width; j++){
            row.push_back(0);
        }
        grid.push_back(row);
    }
    return grid;
}

void searchAlgorithm::updateGrid(std::vector<std::vector<int>> &grid,  std::vector<std::vector<int>> obstacles, const int value ){
    // Set snake body to 1's
    // inverse x and y in obstacles

    for (int i = 0; i < obstacles.size(); i++){
        int temp = obstacles[i][0];
        obstacles[i][0] = obstacles[i][1];
        obstacles[i][1] = temp;
    }
    

    for (int i = 0; i < obstacles.size(); i++){
        // check if items is out of bounds of grid
        if (obstacles[i][0] < 0 || obstacles[i][0] >= grid.size() || obstacles[i][1] < 0 || obstacles[i][1] >= grid[0].size()){
            continue;
        }

        grid[obstacles[i][0]][obstacles[i][1]] = value;
    }
}

void searchAlgorithm::updateGrid(std::vector<std::vector<int>> &grid, const int x, const int y, const int value){
    // Set snake body to 1's

        if (x < 0 || x >= grid.size() || y < 0 || y >= grid[0].size()){
            return;
        }
        grid[x][y] = value;
}





