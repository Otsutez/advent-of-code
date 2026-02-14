#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <unordered_set>
#include <vector>
#include <queue>
#include <ranges>

typedef struct {
    std::bitset<10> state;
    int depth;
} State;

typedef struct {
    std::bitset<10> target_lights;
    std::vector<std::bitset<10>> buttons;
    std::vector<size_t> joltages;
} Machine;

typedef std::vector<std::vector<int>> Matrix;

std::vector<Machine> parse_machines() {
    // std::ifstream f("./puzzle_input/day10.txt");
    std::ifstream f("./puzzle_input/test.txt");
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

        // Parse joltage values
        std::string joltage_str = m.str(3);
        std::vector<size_t> joltages;
        for (int i; (i = joltage_str.find(",")) != joltage_str.npos;) {
            int n = std::stoul(joltage_str.substr(0, i));
            joltages.push_back(n);
            joltage_str.erase(0, i + 1);
        }
        joltages.push_back(std::stoul(joltage_str));
        machines.push_back({bitset, buttons, joltages});
    }
    return machines;
}

void part_1() {
    std::vector<Machine> machines = parse_machines();
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

Matrix get_matrix(Machine &m) {
    size_t joltage_num = m.joltages.size();
    size_t button_num = m.buttons.size();
    Matrix matrix(joltage_num, std::vector<int>(button_num + 1));

    // Initialize b
    for (size_t i = 0; i < joltage_num; i++) {
        matrix[i][button_num] = m.joltages[i];
    }

    // Initialize coefficients
    for (size_t i = 0; i < button_num; i++) {
        for (size_t j = 0; j < joltage_num; j++) {
            if (m.buttons[i].test(j)) {
                matrix[j][i] = 1;
            }
        }
    }

    return matrix;
}

void print_matrix(Matrix &m)  {
    for (auto r : m) {
        for (auto c : r) {
            std::cout << c << ' ';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

std::vector<int> gauss(Matrix &a) {
    size_t n = a.size();
    size_t m = a[0].size() - 1;

    std::vector<int> where (m, -1);
    for (int col = 0, row = 0; col<m && row<n; ++col) {
        int sel = row;
        for (int i = row; i < n; ++i)
            if (abs(a[i][col]) > abs (a[sel][col]))
                sel = i;
        if (a[sel][col] == 0)
            continue;
        for (int i = col; i <= m; ++i) {
            int tmp = a[sel][i];
            a[sel][i] = a[row][i];
            a[row][i] = tmp;
        }
        where[col] = row;

        for (int i = 0; i < n; ++i) {
            if (i != row) {
                double c = a[i][col] / a[row][col]; // Make it comply to integer division
                for (int j = col; j <= m; ++j)
                    a[i][j] -=  a[row][j] * c;
            }
        }
        ++row;

    }
    return where;
}

// Source - https://stackoverflow.com/a/63763630
// Posted by Ofer Strichman
// Retrieved 2026-02-10, License - CC BY-SA 4.0

void CartesianRecurse(std::vector<std::vector<int>> &accum, std::vector<int> stack,
    std::vector<std::vector<int>> sequences, int index)
{
    std::vector<int> sequence = sequences[index];
    for (int i : sequence)
    {       
        stack.push_back(i);
        if (index == 0)
            accum.push_back(stack);
        else
            CartesianRecurse(accum, stack, sequences, index - 1);
        stack.pop_back();
    }
}
std::vector<std::vector<int>> CartesianProduct(std::vector<std::vector<int>> sequences)
{
    std::vector<std::vector<int>> accum;
    std::vector<int> stack;
    if (sequences.size() > 0)
        CartesianRecurse(accum, stack, sequences, sequences.size() - 1);
    return accum;
}

void print_vec(std::vector<int> &v) {
    for (auto x : v) {
        std::cout << x << ' ';
    }
    std::cout << '\n';
}

int find_fewest_press(Matrix &m, Matrix &copy, std::vector<int> where) {
    // Identify column with no leading entry. Those column are free variables.
    std::vector<int> free_col;
    for (int i = 0; i < where.size(); i++) {
        if (where[i] == -1) {
            free_col.push_back(i);
        }
    }
    std::vector<int> col_max(free_col.size(), 1000000);
    for (size_t i = 0; i < free_col.size(); i++) {
        for (auto row : copy) {
            size_t j = row.size() - 1;
            if (row[free_col[i]] == 1 && row[j] < col_max[i]) {
                col_max[i] = row[j];
            }
        }
    }
    // for (auto x : col_max) {
    //     std::cout << x << ' ';
    // }
    // std::cout << '\n';

    // Iterate through possible free variable space and find minimum total presses.
    // for (auto x : where) {
    //     std::cout << x << ' ';
    // }
    // std::cout << '\n';
    // print_matrix(m);

    std::vector<std::vector<int>> sequences;
    for (auto max : col_max) {
        std::vector<int> s;
        for (int i = 0; i <= max; i++) {
            s.push_back(i);
        }
        sequences.push_back(s);
    }
    std::vector<std::vector<int>> combinations = CartesianProduct(sequences);
    // std::vector<std::vector<int>> combinations = {{3, 2}};

    int min_press = 1000000;
    for (auto free_var : combinations) {
        std::vector<int> ans(m[0].size() - 1, 0);
        for (int i = 0; i < free_col.size(); i++) {
            ans[free_col[i]] = free_var[i];
        }
        for (int i = 0; i < m.size(); i++) {
            std::vector<int> row = m[i];
            int sum = 0;
            for (int j = 0; j < free_col.size(); j++) {
                sum += row[free_col[j]] * free_var[j];
            }
            // Find column of leading entry
            int col = 0;
            for (int j = 0; j < where.size(); j++) {
                if (where[j] == i) {
                    col = j;
                }
            }
            ans[col] = row[row.size() - 1] - sum;
        }
        int total = 0;
        bool valid = true;
        for (auto a : ans) {
            if (a < 0) {
                valid = false;
                break;
            }
            total += a;
        }
        if (valid) {
            min_press = std::min(min_press, total);
        }
    }
    return min_press;
}

void part_2() {
    std::vector<Machine> machines = parse_machines();
    for (auto m : machines) {
        Matrix matrix = get_matrix(m);
        Matrix copy = matrix;
        // print_matrix(matrix);
        std::vector<int> where = gauss(matrix);
        // print_matrix(matrix);
        std::cout << find_fewest_press(matrix, copy, where) << '\n';
    }
}

int main() {
    // part_1();
    part_2();
}
