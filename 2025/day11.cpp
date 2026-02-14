#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <stack>
#include <stack>

using namespace std;

typedef unordered_map<string, vector<string>> Graph;

Graph parse_graph() {
    Graph g;
    ifstream f("./puzzle_input/day11.txt");
    // ifstream f("./puzzle_input/test.txt");
    for (string l; getline(f, l);) {
        int i = l.find(':');
        string u = l.substr(0, i);
        stringstream neighbours(l.substr(i + 1));
        string v;
        vector<string> n;
        while (neighbours >> v) {
            n.push_back(v);
        }
        g.insert({u, n});

    }
    return g;
}

void print_graph(Graph &g) {
    for (auto p : g) {
        std::cout << p.first << ": ";
        for (auto v : p.second) {
            std::cout << v << ' ';
        }
        std::cout << endl;
    }
}

void part_one() {
    // Perform DFS that counts total number of paths to reach out
    Graph g = parse_graph();
    int count = 0;
    stack<string> s;
    s.push("you");
    while (!s.empty()) {
        string u = s.top();
        s.pop();
        if (u == "out") {
            count += 1;
        } else {
            for (auto n : g[u]) {
                s.push(n);
            }
        }
    }
    std::cout << count << '\n';
}

int main() {
    part_one();
}
