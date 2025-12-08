#include <iostream>
#include <fstream>
#include <vector>

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

int main() {
    part_one();
    return 0;
}
