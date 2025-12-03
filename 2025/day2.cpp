/*
Part 1 notes:
Made a minor mistake and cast a long long to an int instead. That made my solution wrong and it was such a stupid mistake. Be careful next time.

Learned about C++ regex. Similar to python library.
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <regex>

using ll = long long;

int count_digits(ll n) {
    int dc = 0;
    while (n > 0) {
        dc++;
        n = n / 10;
    }
    return dc;
}

void part_one() {
    std::ifstream f("./puzzle_input/day2.txt");
    std::string s;
    f >> s;
    std::stringstream ss(s);
    ll sum = 0;
    for (std::string range; getline(ss, range, ',');) {
        std::string::size_type n = range.find("-");
        if (n == range.npos) continue;
        ll x = std::stoll(range.substr(0, n));
        ll y = std::stoll(range.substr(n + 1, range.size() - n - 1));
        for (ll i = x; i <= y; i++) {
            int dc = count_digits(i);
            if (dc % 2 == 1) continue;
            int l = 0;
            int r = dc / 2;
            bool same = true;
            while (r < dc && same) {
                int first = (ll)(i / pow(10, dc - l - 1)) % 10;
                int second = (ll)(i / pow(10, dc - r - 1)) % 10;
                same = first == second;
                l++;
                r++;
            }
            if (same) {
                sum += i;
            }
        }
    }
    std::cout << sum << '\n';
    
}

void part_one_regex() {
    std::ifstream f("./puzzle_input/day2.txt");
    std::string s;
    f >> s;
    std::stringstream ss(s);
    ll sum = 0;
    for (std::string range; getline(ss, range, ',');) {
        std::string::size_type n = range.find("-");
        if (n == range.npos) continue;
        ll x = std::stoll(range.substr(0, n));
        ll y = std::stoll(range.substr(n + 1, range.size() - n - 1));
        std::regex invalid("^(\\w+)\\1$");
        for (ll i = x; i <= y; i++) {
            if (std::regex_match(std::to_string(i), invalid)) {
                sum += i;
            }
        }
    }
    std::cout << sum << '\n';
}

void part_two_regex() {
    std::ifstream f("./puzzle_input/day2.txt");
    std::string s;
    f >> s;
    std::stringstream ss(s);
    ll sum = 0;
    for (std::string range; getline(ss, range, ',');) {
        std::string::size_type n = range.find("-");
        if (n == range.npos) continue;
        ll x = std::stoll(range.substr(0, n));
        ll y = std::stoll(range.substr(n + 1, range.size() - n - 1));
        std::regex invalid("^(\\w+)\\1+$");
        for (ll i = x; i <= y; i++) {
            if (std::regex_match(std::to_string(i), invalid)) {
                sum += i;
            }
        }
    }
    std::cout << sum << '\n';
    
}

int main() {
    part_one();
    part_two_regex();
    return 0;
}
