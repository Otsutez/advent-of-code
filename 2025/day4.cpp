#include <fstream>
#include <iostream>
#include <vector>

void part_one() {
    std::ifstream f("./puzzle_input/day4.txt");
    std::vector<std::string> grid;
    for (std::string line; getline(f, line);) {
        grid.push_back(line);
    }
    int accessible = 0;
    for (int i = 0; i < grid.size(); i++) {
        std::string line = grid[i];
        for (int j = 0; j < line.size(); j++) {
            if (grid[i][j] != '@') continue;
            int count = 0;
            for (int x = -1; x < 2; x++) {
                for (int y = -1; y < 2; y++) {
                    if (i + x < 0 || i + x >= grid.size()) continue;
                    if (j + y < 0 || j + y >= line.size()) continue;
                    if (grid[i + x][j + y] == '@') count++; 
                }
            }
            if (count <= 4) {
                accessible++;
            }
        }
    }
    std::cout << accessible << '\n';
}

void part_two() {
    std::ifstream f("./puzzle_input/day4.txt");
    std::vector<std::string> grid;
    for (std::string line; getline(f, line);) {
        grid.push_back(line);
    }
    int accessible = 0;

    bool removed = true;
    while (removed) {
        removed = false;
        for (int i = 0; i < grid.size(); i++) {
            std::string line = grid[i];
            for (int j = 0; j < line.size(); j++) {
                if (grid[i][j] != '@') continue;
                int count = 0;
                for (int x = -1; x < 2; x++) {
                    for (int y = -1; y < 2; y++) {
                        if (i + x < 0 || i + x >= grid.size()) continue;
                        if (j + y < 0 || j + y >= line.size()) continue;
                        if (grid[i + x][j + y] == '@') count++; 
                    }
                }
                if (count <= 4) {
                    accessible++;
                    grid[i][j] = '.';
                    removed = true;
                }
            }
        }
    }
    std::cout << accessible << '\n';
}

int main() {
    part_one();
    part_two();
    return 0;
}
