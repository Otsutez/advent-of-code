#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

using ll = long long;

typedef struct {
    ll start;
    ll end;
} Range;

bool in_range(Range &r, ll n) {
    return r.start <= n && n <= r.end;
}

void part_one() {
    std::ifstream f("./puzzle_input/day5.txt");
    std::vector<Range> ranges;
    for (;;) {
        std::string range;
        getline(f, range);
        if (range.empty()) break;
        Range r;
        int i = range.find('-');
        r.start = stoll(range.substr(0, i));
        r.end = stoll(range.substr(i + 1));
        ranges.push_back(r);
    }
    ll count = 0;
    for (std::string line; getline(f, line);) {
        ll n = stoll(line);
        for (auto r : ranges) {
            if (in_range(r, n)) {
                count++;
                break;
            }
        }

    }
    std::cout << count << '\n';
}

bool comp_range(const Range &a, const Range &b) {
    if (a.start != b.start) {
        return a.start < b.start;
    }
    return a.end < b.end;
}

void part_two() {
    std::ifstream f("./puzzle_input/day5.txt");
    std::vector<Range> ranges;
    for (;;) {
        std::string range;
        getline(f, range);
        if (range.empty()) break;
        Range r;
        int i = range.find('-');
        r.start = stoll(range.substr(0, i));
        r.end = stoll(range.substr(i + 1));
        ranges.push_back(r);
    }
    std::sort(ranges.begin(), ranges.end(), &comp_range);
    // Greedy algorithm to merge ranges
    ll count = 0;
    size_t i = 0;
    while (i < ranges.size()) {
        Range r = ranges[i];
        while (i + 1 < ranges.size() && ranges[i + 1].start <= r.end) {
            r.end = std::max(ranges[i + 1].end, r.end);
            i++;
        }
        count += r.end - r.start + 1;
        i++;
    }
    std::cout << count << '\n';
}

int main() {
    part_one();
    part_two();
    return 0;
}
