#include <iostream>
#include <fstream>
#include <regex>
#include <unordered_set>
#include <vector>
#include <queue>

typedef struct {
    std::bitset<10> state;
    int depth;
} State;

typedef struct {
    std::bitset<10> target_lights;
        std::vector<std::bitset<10>> buttons;
} Machine;

int main() {
    std::ifstream f("./puzzle_input/day10.txt");
    // std::ifstream f("./puzzle_input/test.txt");
    std::vector<Machine> machines;
    for (std::string line; getline(f, line);) {
        std::smatch m;
        std::regex regex("^\\[([\\.|#]*)\\]\\s((?:\\((?:\\d+,?)+\\)\\s)+)\\{((?:\\d+,?)+)\\}");
        std::regex_match(line, m, regex);

        // Parse target lights configuration
        std::string lights = m.str(1);
        std::bitset<10> bitset{0};
        for (size_t i = 0; i < lights.size(); i++) {
            if (lights[i] == '#') {
                bitset.set(i, 1);
            }
        }

        // Parse buttons
        std::vector<std::bitset<10>> buttons;
        std::string button = m.str(2);
        button.erase(0, 1);
        button.erase(button.size() - 2, 2);
        std::vector<std::string> buttons_str;
        for (int i; (i = button.find(") (")) != button.npos;) {
            buttons_str.push_back(button.substr(0, i));
            button.erase(0, i + 3);
        }
        buttons_str.push_back(button);

        for (auto b : buttons_str) {
            std::bitset<10> bt{0};
            for (int i; (i = b.find(",")) != b.npos;) {
                int n = std::stoi(b.substr(0, i));
                bt |= (1 << n);
                b.erase(0, i + 1);
            }
            int n = std::stoi(b);
            bt |= (1 << n);
            buttons.push_back(bt);
        }
        machines.push_back({bitset, buttons});
    }

    // BFS to find shortest path to target configuration
    size_t total_press = 0;
    for (auto m : machines) {
        bool found = false;
        std::queue<State> q;
        std::unordered_set<std::bitset<10>> visited;
        for (auto b : m.buttons) {
            if (b == m.target_lights) {
                found = true;
                break;
            }
            q.push({b, 1});
        }
        if (found) {
            total_press += 1;
            continue;
        }

        found = false;
        while (!q.empty() && !found) {
            State s = q.front();
            q.pop();
            visited.insert(s.state);
            for (auto b : m.buttons) {
                std::bitset<10> new_state = s.state ^ b;
                if (new_state == m.target_lights) {
                    total_press += s.depth + 1;
                    found = true;
                    break;
                }
                if (!visited.count(new_state)) {
                    q.push({new_state, s.depth + 1});
                    
                }
            }
        }
    }
    std::cout << total_press << '\n';
}
