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

bool in_rect(Coord &a, Coord &b, Coord &c) {
    // Convert point a to upper left corner and point b to lower right corner
    if (a.x < b.x) {
        if (a.y > b.y) {
            int tmp = a.y;
            a.y = b.y;
            b.y = tmp;
        }
    } else {
        if (a.y < b.y) {
            int tmp = a.x;
            a.x = b.x;
            b.x = tmp;
        } else {
            Coord tmp = a;
            a = b;
            b = tmp;
        }
    }
    return c.x > a.x && c.x < b.x && c.y > a.y && c.y < b.y;
}

bool is_line_intersect(Coord &a, Coord &b, Coord &c, Coord &d) {
    if (a.x < b.x) {
        if (a.y > b.y) {
            int tmp = a.y;
            a.y = b.y;
            b.y = tmp;
        }
    } else {
        if (a.y < b.y) {
            int tmp = a.x;
            a.x = b.x;
            b.x = tmp;
        } else {
            Coord tmp = a;
            a = b;
            b = tmp;
        }
    }
    if (c.y == d.y) {
        if (a.y >= c.y || b.y <= c.y) return false;
        if (c.x > d.x) {
            int tmp = c.x;
            c.x = d.x;
            d.x = tmp;
        }
        return c.x <= a.x && d.x >= b.x;
    } else {
        if (a.x >= c.x || b.x <= c.x) return false;
        if (c.y > d.y) {
            int tmp = c.y;
            c.y = d.y;
            d.y = tmp;
        }
        return c.y <= a.y && d.y >= b.y;
    }
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
    // std::ifstream f("./puzzle_input/test.txt");
    std::ifstream f("./puzzle_input/day9.txt");
    std::vector<Coord> tiles;
    for (std::string line; getline(f, line);) {
        int i = line.find(',');
        Coord c = {
            stoi(line.substr(0, i)),
            stoi(line.substr(i + 1))
        };
        tiles.push_back(c);
    }
    ll max_area = 0;
    for (size_t i = 0; i < tiles.size(); i++) {
        for (size_t j = i + 1; j < tiles.size(); j++) {
            Coord a = tiles[i];
            Coord b = tiles[j];
            ll area = get_area(a, b);
            if (area > max_area) {
                // Check if red tile inside rectangle area or line intersect area
                bool valid = true;
                for (size_t k = 0; k < tiles.size(); k++) {
                    Coord c = tiles[k];
                    Coord d = tiles[(k + 1) % tiles.size()];
                    if (in_rect(a, b, c) || is_line_intersect(a, b, c, d)) {
                        valid = false;
                        break;
                    }
                }
                if (valid) max_area = area;
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
