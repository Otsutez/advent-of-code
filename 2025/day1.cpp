#include <iostream>
#include <fstream>
#include <cmath>

int part_one() {
    std::ifstream f("./puzzle_input/day1.txt");

    int n = 50;
    int zc = 0;
    for (std::string l; getline(f, l);) {
        int m = std::stoi(l.substr(1));
        n = (l[0] == 'R') ? (n + m) % 100 : (n - m) % 100;
        if (n == 0) zc++;
    }
    return zc;
}

int part_two() {
    std::ifstream f("./puzzle_input/day1.txt");

    int n = 50;
    int zc = 0;
    for (std::string l; getline(f, l);) {
        int m = std::stoi(l.substr(1));
        m = l[0] == 'R' ? m : -m;
        int s = n + m;
        if (m >= 0) {
            zc += s / 100;
        } else {
            if (-m >= n) zc += (s / -100) + 1; 
            if (n == 0) zc--;
        }
        n = (s % 100 + 100) % 100;
    }
    return zc;
}


int main() {
    std::cout << part_one() << "\n";
    std::cout << part_two() << "\n";
    return 0;
}
