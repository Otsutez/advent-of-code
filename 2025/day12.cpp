#include <bits/stdc++.h>
#include <cstddef>
#include <sstream>
#include <vector>
using namespace std;

typedef vector<string> Shape;
struct Region {
    size_t width;
    size_t length;
    vector<size_t> shape_quantities; 
};

void print_shape(Shape s) {
    for (auto line : s) {
        cout << line << "\n";
    }
}

void print_shapes(vector<Shape> shapes) {
    for (auto s : shapes) {
        print_shape(s);
        cout << "\n";
    }
}

void print_region(Region &r) {
    cout << r.width << 'x' << r.length << "\n";
    for (auto x : r.shape_quantities) {
        cout << x << " ";
    }
    cout << "\n";
}

void print_regions(vector<Region> &regions) {
    for (auto r : regions) {
        print_region(r);
    }
}

// Parse shapes
pair<vector<Shape>, vector<Region>> parse_shapes_and_region(string filename) {
    vector<Shape> shapes;
    vector<Region> regions;
    ifstream f(filename);
    string l;
    for (;getline(f, l);) { // Parse shapes
        if (l.empty()) continue;
        if (l.find('x') == std::string::npos) {
            Shape s;
            getline(f, l);
            for (;!l.empty(); getline(f, l)) {
                s.push_back(l);
            }
            shapes.push_back(s);
        } else {
            // Found beginning of region
            break;
        }
    }

    // Now l has the first region definition
    do { // Parse regions
        stringstream ss(l);
        Region r;
        char skip;
        ss >> r.width;
        ss >> skip; // x
        ss >> r.length;
        ss >> skip; // :
        for (size_t i = 0; i < shapes.size(); i++) {
            size_t quantity;
            ss >> quantity;
            r.shape_quantities.push_back(quantity);
        }
        regions.push_back(r);
    } while (getline(f, l));

    return {shapes, regions};
}

bool have_enough_space(Region &r, vector<size_t> &areas) {
    size_t total_area = r.width * r.length;

    size_t area_used = 0;
    for (size_t i = 0; i < r.shape_quantities.size(); i++) {
        size_t quantity = r.shape_quantities[i];
        area_used += quantity * areas[i];
    }
    return area_used <= total_area;
}

// Return a vector of area occupied by each shape
vector<size_t> calc_shapes_area(vector<Shape> &shapes) {
    vector<size_t> areas;
    for (auto shape : shapes) {
        size_t area = 0;
        for (auto line : shape) {
            for (auto c : line) {
                if (c == '#' ) area++;
            }
        }
        areas.push_back(area);
    }
    return areas;
}

bool can_place_consecutively(Region &r) {
    size_t sum_shape_count = 0;
    for (auto quantity : r.shape_quantities) {
        sum_shape_count += quantity;
    }
    size_t width = r.width / 3;
    size_t height = r.length/ 3;
    return width * height >= sum_shape_count;
}

void part_one() {
    pair<vector<Shape>, vector<Region>> pair = parse_shapes_and_region("./puzzle_input/day12.txt");
    vector<Shape> shapes = pair.first;
    vector<Region> regions = pair.second;
    vector<size_t> areas = calc_shapes_area(shapes);

    // Count number of region that can fit all presents
    size_t count = regions.size();
    for (Region &r : regions) {
        // Simple check if total area is enough
        if (!have_enough_space(r, areas)) {
            count--;
            continue;
        }
        // Check if can place right next to each other in 3x3 grid
        if (!can_place_consecutively(r)) {
            count--;
        }

    }
    cout << count << "\n";
}

int main() {
    part_one();
    return 0;
}
