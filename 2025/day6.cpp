#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using ll = long long;

bool is_number(const std::string& s) {
    for (auto x : s) {
        if (!std::isdigit(x)) return false;
    }
    return true;
}

int main() {
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
    for (int i = 0; i < ops.size(); i++) {
        ll sumtotal = nums[0][i];
        if (ops[i] == '+') {
            for (int j = 1; j < nums.size(); j++) {
                sumtotal += nums[j][i];
            }
        } else {
            for (int j = 1; j < nums.size(); j++) {
                sumtotal *= nums[j][i];
            }
            
        }
        sum += sumtotal;
    }
    std::cout << sum << '\n';


    return 0;
}
