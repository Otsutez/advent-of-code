#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using ll = long long;

typedef struct {
    int x;
    int y;
    int z;
} Box;

typedef struct {
    double dist;
    size_t a;
    size_t b;
} Edge;

bool edge_sorter(const Edge &lhs, const Edge &rhs) {
    return lhs.dist < rhs.dist;
}

class UnionFind {
    std::vector<int> parent;
    std::vector<int> subtree;

public:
    UnionFind(int size) {
        for (int i = 0; i < size; i++) {
            parent.push_back(i);
            subtree.push_back(1);
        }
    }
    
    int find(int v) {
        if (parent[v] == v) {
            return v;
        }
        return find(parent[v]);
    }

    bool unite(int u, int v) {
        int repu = find(u);
        int repv = find(v);
        if (repu == repv) return false;
        if (subtree[u] >= subtree[v]) {
            parent[repv] = repu;
            subtree[repu] += subtree[repv];
        } else {
            parent[repu] = repv;
            subtree[repv] += subtree[repu];
        }
        return true;
    }

    ll product_of_three_largest_sets() {
        std::vector<int> root_size(parent.size(), 0);
        for (size_t i = 0; i < parent.size(); i++) {
            int p = find(i);
            root_size[p] = subtree[p];
        }
        std::sort(root_size.rbegin(), root_size.rend());
        return root_size[0] * root_size[1] * root_size[2];
    }
};

void part_one() {
    std::ifstream f("./puzzle_input/day8.txt");
    std::vector<Box> boxes;
    for (std::string line; getline(f, line);) {
        int first = line.find(',');
        int second = line.find(',', first + 1);
        Box b = {
            stoi(line.substr(0, first)),
            stoi(line.substr(first + 1, second - first - 1)),
            stoi(line.substr(second + 1))
        };
        boxes.push_back(b);
    }
    std::vector<Edge> edges;
    for (size_t i = 0; i < boxes.size(); i++) {
        for (size_t j = i + 1; j < boxes.size(); j++) {
            Box a = boxes[i];
            Box b = boxes[j];
            double dist = sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2));
            edges.push_back(Edge {dist, i , j});
        }
    }
    std::sort(edges.begin(), edges.end(), &edge_sorter);
    UnionFind u(boxes.size());
    for (int i = 0; i < 1000; i++) {
        u.unite(edges[i].a, edges[i].b);
    }
    std::cout << u.product_of_three_largest_sets() << '\n';
}

void part_two() {
    std::ifstream f("./puzzle_input/day8.txt");
    std::vector<Box> boxes;
    for (std::string line; getline(f, line);) {
        int first = line.find(',');
        int second = line.find(',', first + 1);
        Box b = {
            stoi(line.substr(0, first)),
            stoi(line.substr(first + 1, second - first - 1)),
            stoi(line.substr(second + 1))
        };
        boxes.push_back(b);
    }
    std::vector<Edge> edges;
    for (size_t i = 0; i < boxes.size(); i++) {
        for (size_t j = i + 1; j < boxes.size(); j++) {
            Box a = boxes[i];
            Box b = boxes[j];
            double dist = sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2));
            edges.push_back(Edge {dist, i , j});
        }
    }
    std::sort(edges.begin(), edges.end(), &edge_sorter);
    UnionFind u(boxes.size());
    size_t count = 0;
    int i = 0;
    while (count < boxes.size() - 1) {
        if (u.unite(edges[i].a, edges[i].b)) {
            count++;
        }
        i++;
    }
    i--;
    std::cout << (ll) boxes[edges[i].a].x * (ll) boxes[edges[i].b].x<< '\n';
}

int main() {
    part_two();
    return 0;
}
