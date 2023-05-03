
#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <tuple>
#include <map>

class searchAlgorithm {
        public:
                std::vector<std::vector<int>> createGrid(int width, int height);
                void updateGrid(std::vector<std::vector<int>> &grid,  std::vector<std::vector<int>> obstacles, const int value );
                void updateGrid(std::vector<std::vector<int>> &grid, const int x , const int y, const int value);
                std::vector<std::pair<int, int>> reconstruct_path(std::map<std::pair<int, int>, std::pair<int, int>> &parent, std::pair<int, int> start, std::pair<int, int> current);
                std::pair<std::vector<std::pair<int, int>>, int> recursive_bfs(std::vector<std::vector<int>> &grid, std::pair<int, int> start, std::pair<int, int> destination, std::queue<std::tuple<int, int, int>> &queue, std::set<std::pair<int, int>> &visited, std::map<std::pair<int, int>, std::pair<int, int>> &parent);
                std::pair<std::vector<std::pair<int, int>>, int> iterative_bfs(const std::vector<std::vector<int>>& grid, const std::pair<int, int>& start, const std::pair<int, int>& destination);
};
