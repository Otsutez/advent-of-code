#include <fstream>
#include <iostream>
#include <vector>
using ll = long long;

typedef struct {
    int x;
    int y;
} Coord;

ll get_area(Coord &a, Coord &b) {
    return (ll)(abs(a.x - b.x) + 1) * (ll)(abs(a.y - b.y) + 1);
}

void part_one() {
    std::ifstream f("./puzzle_input/day9.txt");
    std::vector<Coord> tiles;
    for (std::string line; getline(f, line);) {
        int i = line.find(',');
        Coord c = {
            stoi(line.substr(i + 1)),
            stoi(line.substr(0, i))
        };
        tiles.push_back(c);
    }
    ll max_area = 0;
    for (size_t i = 0; i < tiles.size(); i++) {
        for (size_t j = i + 1; j < tiles.size(); j++) {
            ll a = get_area(tiles[i], tiles[j]);
            if (a > max_area) max_area = a;
        }
    }
    std::cout << max_area << '\n';
}

void part_two() {
    // std::ifstream f("./puzzle_input/day9.txt");
    std::ifstream f("./puzzle_input/test.txt");
    std::vector<Coord> tiles;
    for (std::string line; getline(f, line);) {
        int i = line.find(',');
        Coord c = {
            stoi(line.substr(i + 1)),
            stoi(line.substr(0, i))
        };
        tiles.push_back(c);
    }
    ll max_area = 0;
    for (size_t i = 0; i < tiles.size(); i++) {
        for (size_t j = i + 1; j < tiles.size(); j++) {
            Coord a = tiles[i];
            Coord b = tiles[j];
            if (a.x == b.x || a.y == b.y) {
                max_area = std::max(max_area, get_area(a, b));
            }
            if (a.x < b.x) {
                if (a.y > b.y) {
                    int temp = a.y;
                    a.y = b.y;
                    b.y = temp;
                }
            } else {
                if (a.y > b.y) {
                    // Might not work here
                    Coord temp = a;
                    a = b;
                    b = temp;
                } else {
                    int temp = a.x;
                    a.x = b.x;
                    b.x = temp;
                }
            }
            bool found = false;
            for (auto c : tiles) {
                if (a.x < c.x && a.y > c.y && b.x > c.x && b.y < c.y) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                max_area = std::max(max_area, get_area(a, b));
            }
        }
    }
    std::cout << max_area << '\n';
}
 
int main() {
    // part_one();
    part_two();
    return 0;
}
