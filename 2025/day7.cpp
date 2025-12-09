#include <iostream>
#include <fstream>
#include <vector>

using ll = long long;

void part_one() {
    std::ifstream f("./puzzle_input/day7.txt");
    std::vector<std::string> grid;
    for (std::string line; getline(f, line);) {
        grid.push_back(line);
    }
    for (size_t i = 0; i < grid[0].size(); i++) {
        if (grid[0][i] == 'S') grid[0][i] = '|';
    }
    int count = 0;
    for (size_t i = 1; i < grid.size(); i++) {
        for (size_t j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] == '^') {
                if (grid[i - 1][j] == '|') {
                    count++;
                    if (j - 1 >= 0) grid[i][j - 1] = '|';
                    if (j + 1 < grid[i].size()) grid[i][j + 1] = '|';
                }
            } else if (grid[i][j] == '.'){
                if (grid[i - 1][j] == '|') grid[i][j] = '|';
            }
        }
    }
    std::cout << count << '\n';
}

// Used memoization here!!! It insanely increased speed
ll count_timeline(std::vector<std::string> &grid, std::vector<std::vector<ll>> &memo, size_t level, size_t beam) {
    if (level == grid.size() - 1) {
        return 1;
    }
    if (memo[level][beam] != -1) {
        return memo[level][beam];
    }
    ll count = 0;
    if (grid[level][beam] == '^') {
        count += count_timeline(grid, memo, level + 1, beam - 1);
        count += count_timeline(grid, memo, level + 1, beam + 1);
    } else {
        count += count_timeline(grid, memo, level + 1, beam);
    }

    memo[level][beam] = count;
    return count;
}

void part_two() {
    std::ifstream f("./puzzle_input/day7.txt");
    std::vector<std::string> grid;
    for (std::string line; getline(f, line);) {
        grid.push_back(line);
    }
    int beam = grid[0].find_first_of('S');
    std::vector<std::vector<ll>> memo(grid.size(), std::vector<ll>(grid[0].size(), -1));
    std::cout <<  count_timeline(grid, memo, 1, beam) << '\n';
    
}

int main() {
    part_one();
    part_two();
    return 0;
}
