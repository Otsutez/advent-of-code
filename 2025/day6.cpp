#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <cstdlib>

using ll = long long;

bool is_number(const std::string& s) {
    for (auto x : s) {
        if (!std::isdigit(x)) return false;
    }
    return true;
}

void part_one() {
    std::vector<std::vector<ll>> nums;
    std::vector<char> ops;
    // std::ifstream f("./puzzle_input/test.txt");
    std::ifstream f("./puzzle_input/day6.txt");
    for (std::string line; getline(f, line);) {
        std::stringstream ss(line);
        std::string n;
        std::vector<ll> ns;
        bool op = false;
        while (ss >> n) {
            if (is_number(n)) {
                ns.push_back(stoll(n));
            } else {
                ops.push_back(n[0]);
                op = true;
            }
        }
        if (!op) nums.push_back(ns);
    }
    nums.pop_back();

    ll sum = 0;
    for (size_t i = 0; i < ops.size(); i++) {
        ll sumtotal = nums[0][i];
        if (ops[i] == '+') {
            for (size_t j = 1; j < nums.size(); j++) {
                sumtotal += nums[j][i];
            }
        } else {
            for (size_t j = 1; j < nums.size(); j++) {
                sumtotal *= nums[j][i];
            }
            
        }
        sum += sumtotal;
    }
    std::cout << sum << '\n';
}

void part_two() {
    std::ifstream f("./puzzle_input/day6.txt");
    std::vector<std::string> lines;
    std::vector<char> ops;
    for (std::string line; getline(f, line);) {
        if (line[0] == '+' || line[0] == '*') {
            std::stringstream ss(line);
            char op;
            while (ss >> op) ops.push_back(op);
        }
        lines.push_back(line);
    }
    size_t last = lines.size() - 1;
    size_t i = 0;
    std::vector<int> nums;
    while (i < lines[0].size()) {
        int n = 0;
        for (size_t j = 0; j < last; j++) {
            if (isdigit(lines[j][i])) {
                n += (lines[j][i] - '0') * pow(10, last - j - 1);
            } else {
                n = n / 10;
            }
        }
        nums.push_back(n);
        i++;
    }
    nums.push_back(0);

    int j = 0;
    char op = ops[j];
    ops.pop_back();
    ll sumproduct = (op == '+') ? 0 : 1;
    ll sum = 0;
    for (auto n : nums) {
        if (n == 0) {
            sum += sumproduct;
            j++;
            op = ops[j];
            sumproduct = (op == '+') ? 0 : 1;
        } else {
            if (op == '+') {
                sumproduct += n;
            } else {
                sumproduct *= n;
            }
        }
    }
    std::cout << sum << '\n';

}

int main() {
    part_one();
    part_two();
    return 0;
}
