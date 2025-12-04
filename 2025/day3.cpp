#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>

using ll = long long;

void part_one() {
    std::ifstream f("./puzzle_input/day3.txt");
    int sum = 0;
    for (std::string line; getline(f, line);) {
        std::vector<int> digits;
        for (size_t i = 0; i < line.size(); i++) {
            digits.push_back(line[i] - '0');
        }
        int max = digits[0];
        int maxpos = 0;
        for (size_t i = 1; i < digits.size() - 1; i++) {
            if (digits[i] > max) {
                max = digits[i];
                maxpos = i;
            }
        }
        int max2 = digits[maxpos + 1];
        for (size_t i = maxpos + 1; i < digits.size(); i++) {
            if (digits[i] > max2) {
                max2 = digits[i];
            }
        }
        sum += max * 10 + max2;
    }
    std::cout << sum << '\n';
}

void part_two() {
    std::ifstream f("./puzzle_input/day3.txt");
    // std::ifstream f("./puzzle_input/test.txt");
    ll sum = 0;
    for (std::string line; getline(f, line);) {
        std::vector<int> digits;
        std::vector<int> maxv;
        for (size_t i = 0; i < line.size(); i++) {
            digits.push_back(line[i] - '0');
        }
        int pos = 0;
        for (int d = 0; d < 12; d++) {
            int start = pos;
            for (size_t i = start; i < digits.size() - (11 - d); i++) {
                if (digits[i] > digits[pos]) {
                    pos = i;
                }
            }
            maxv.push_back(digits[pos]);
            pos++;
        }
        ll num = 0;
        for (size_t i = 0; i < maxv.size(); i++) {
            num += maxv[i] * pow(10, 11 - i);
        }
        sum += num;
    }
    std::cout << sum << '\n';
}


int main() {
    part_one();
    part_two();
    return 0;
}
