#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;

typedef unordered_map<string, vector<string>> Graph;
typedef long long ll;

Graph parse_graph(string path) {
    Graph g;
    // ifstream f("./puzzle_input/day11.txt");
    ifstream f(path);
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

ll count_path(Graph g, string in, string out) {
    unordered_map<string, ll> count;
    unordered_map<string, bool> visited;
    for (auto p : g) {
        count.insert({p.first, 0});
        visited.insert({p.first, false});
    }
    count[in] = 1;
    visited[in] = true;

    queue<string> q;
    q.push(in);
    while (!q.empty()) {
        string u = q.front();
        q.pop();
        for (auto v : g[u]) {
            count[v] += count[u];
            if (!visited[v]) {
                q.push(v);
            }
            visited[v] = true;
        }
    }
    return count[out];
}

void part_one() {
    // Perform BFS that counts total number of paths to reach out
    Graph g = parse_graph("./puzzle_input/day11.txt");
    std::cout << count_path(g, "you", "out") << '\n';
}

void print_path(vector<string> path) {
    for (auto e : path) {
        std::cout << e << " ";
    }
    std::cout << "\n";
}

// Holy Maccaroni optimization right here
// Credit: vss2sn (https://github.com/vss2sn/advent_of_code/blob/master/2025/cpp/day_11b.cpp)
// I basically have the same algorithm as him
unordered_map<string, ll> history;

ll recursive_count_path(Graph g, string curr, bool found_dac, bool found_fft, vector<string> path) {
    path.push_back(curr);
    // print_path(path);
    
    // Base case
    if (curr == "out") {
        if (found_dac && found_fft) {
            return 1;
        } else {
            return 0;
        }
    }

    string key = curr + (found_dac ? "1" : "0") + (found_fft ? "1" : "0");
    if (history.count(key) > 0) {
        return history[key];
    }

    ll count = 0;
    for (auto v : g[curr]) {
        count += recursive_count_path(g, v, found_dac || v == "dac", found_fft || v == "fft", path);
    }

    history[key] = count;

    path.pop_back();
    return count;
}

void part_two() {
    // Count number of paths that pass through fft and dac with DFS
    Graph g = parse_graph("./puzzle_input/day11.txt");
    vector<string> path;
    ll path_count = recursive_count_path(g, "svr", false, false, path);
    cout << path_count << '\n';
}



int main() {
    // part_one();
    part_two();
}
