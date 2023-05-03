
#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <tuple>
#include <map>

namespace search_traversal {
    // Function declarations
    std::vector<std::vector<int>> createGrid(int width, int height);

    void updateGrid(std::vector<std::vector<int>> &grid,  std::vector<std::vector<int>> obstacles, const int value );

    void updateGrid(std::vector<std::vector<int>> &grid, const int x , const int y, const int value);

    std::vector<std::pair<int, int>> reconstruct_path(std::map<std::pair<int, int>, std::pair<int, int>> &parent, std::pair<int, int> start, std::pair<int, int> current);

    std::pair<std::vector<std::pair<int, int>>, int> recursive_bfs(std::vector<std::vector<int>> &grid, std::pair<int, int> start, std::pair<int, int> destination,
                 std::queue<std::tuple<int, int, int>> &queue, std::set<std::pair<int, int>> &visited, std::map<std::pair<int, int>, std::pair<int, int>> &parent);

std::pair<std::vector<std::pair<int, int>>, int> iterative_bfs(const std::vector<std::vector<int>>& grid,
        const std::pair<int, int>& start, const std::pair<int, int>& destination);
}





// Executable snnipet for testing the algorithm: 


// int main() {
//     std::vector<std::vector<int>> grid = {
//         {0, 0, 0},
//         {0, 1, 0},
//         {0, 1, 0},
//         {0, 1, 0},
//         {0, 1, 0}
//     };
//     std::pair<int, int> start = {0, 0};
//     std::pair<int, int> destination = {4, 2};

//     std::queue<std::tuple<int, int, int>> queue;
//     queue.push({start.first, start.second, 0});
//     std::set<std::pair<int, int>> visited = {start};
//     std::map<std::pair<int, int>, std::pair<int, int>> parent = {{start, {}}};

//     auto [path, steps] = recursive_bfs(grid, start, destination, queue, visited, parent);

//     std::cout << "Shortest path: ";
//     for (const auto &[row, col] : path) {
//         std::cout << "(" << row << ", " << col << ") ";
//     }
//     std::cout << std::endl;
//     std::cout << "Number of steps" << steps <<std::endl;
//     return 0;
// }