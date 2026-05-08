use std::collections::VecDeque;

fn parse_garden(path: &str) -> Vec<Vec<char>> {
    std::fs::read_to_string(path)
        .expect("path exists")
        .lines()
        .map(|line| line.chars().collect())
        .collect()
}

const R_DIFF: [isize; 4] = [-1, 0, 1, 0];
const C_DIFF: [isize; 4] = [0, 1, 0, -1];

fn get_area_perimeter(
    i: usize,
    j: usize,
    garden: &Vec<Vec<char>>,
    visited: &mut Vec<Vec<bool>>,
) -> (usize, usize) {
    let plant = garden[i][j];
    let mut deque = VecDeque::new();
    let mut area = 0;
    let mut perimeter = 0;
    let row_num = garden.len() as isize;
    let col_num = garden[0].len() as isize;
    deque.push_back((i as isize, j as isize));
    visited[i][j] = true;

    while let Some((r, c)) = deque.pop_front() {
        area += 1;
        for k in 0..4 {
            let new_r = r as isize + R_DIFF[k];
            let new_c = c as isize + C_DIFF[k];
            if 0 <= new_r
                && new_r < row_num
                && 0 <= new_c
                && new_c < col_num
                && garden[new_r as usize][new_c as usize] == plant
            {
                if !visited[new_r as usize][new_c as usize] {
                    deque.push_back((new_r, new_c));
                    visited[new_r as usize][new_c as usize] = true;
                }
            } else {
                perimeter += 1;
            }
        }
    }
    (area, perimeter)
}

fn part_one() {
    let garden = parse_garden("input/day12");
    let row_num = garden.len();
    let col_num = garden[0].len();
    let mut visited = vec![vec![false; col_num]; row_num];
    let mut price = 0;

    for i in 0..row_num {
        for j in 0..col_num {
            if !visited[i][j] {
                let (area, perimeter) = get_area_perimeter(i, j, &garden, &mut visited);
                // println!("{} {}", area, perimeter);
                price += area * perimeter;
            }
        }
    }
    println!("{}", price);
}

const R_8_DIFF: [isize; 8] = [0, -1, -1, -1, 0, 1, 1, 1];
const C_8_DIFF: [isize; 8] = [-1, -1, 0, 1, 1, 1, 0, -1];

fn get_area_side(
    i: usize,
    j: usize,
    garden: &Vec<Vec<char>>,
    visited: &mut Vec<Vec<bool>>,
) -> (usize, usize) {
    let plant = garden[i][j];
    let mut deque = VecDeque::new();
    let mut area = 0;
    let mut corners = 0;
    let row_num = garden.len() as isize;
    let col_num = garden[0].len() as isize;
    deque.push_back((i as isize, j as isize));
    visited[i][j] = true;

    while let Some((r, c)) = deque.pop_front() {
        let r = r as isize;
        let c = c as isize;
        area += 1;
        // Add neighbours to queue
        for k in 0..4 {
            let new_r = r + R_DIFF[k];
            let new_c = c + C_DIFF[k];
            if 0 <= new_r
                && new_r < row_num
                && 0 <= new_c
                && new_c < col_num
                && garden[new_r as usize][new_c as usize] == plant
                && !visited[new_r as usize][new_c as usize]
            {
                deque.push_back((new_r, new_c));
                visited[new_r as usize][new_c as usize] = true;
            }
        }

        // Count corners because # corners = # sides
        // Credit to RazarTuk https://www.reddit.com/r/adventofcode/comments/1hcpyic/2024_day_12_part_2_what_kind_of_algorithm_did_you/
        for k in (0..8).step_by(2) {
            let (curr_r, diag_r, per_r) = (
                r + R_8_DIFF[k],
                r + R_8_DIFF[k + 1],
                r + R_8_DIFF[(k + 2) % 8],
            );
            let (curr_c, diag_c, per_c) = (
                c + C_8_DIFF[k],
                c + C_8_DIFF[k + 1],
                c + C_8_DIFF[(k + 2) % 8],
            );
            let curr = if 0 <= curr_r && curr_r < row_num && 0 <= curr_c && curr_c < col_num {
                garden[curr_r as usize][curr_c as usize]
            } else {
                '.'
            };
            let diag = if 0 <= diag_r && diag_r < row_num && 0 <= diag_c && diag_c < col_num {
                garden[diag_r as usize][diag_c as usize]
            } else {
                '.'
            };
            let per = if 0 <= per_r && per_r < row_num && 0 <= per_c && per_c < col_num {
                garden[per_r as usize][per_c as usize]
            } else {
                '.'
            };
            // Check convex angle
            if curr != plant && per != plant {
                corners += 1;
            }
            // Check concave angle
            if curr == plant && per == plant && diag != plant {
                corners += 1;
            }
        }
    }
    (area, corners)
}

fn part_two() {
    let garden = parse_garden("input/day12");
    let row_num = garden.len();
    let col_num = garden[0].len();
    let mut visited = vec![vec![false; col_num]; row_num];
    let mut price = 0;

    for i in 0..row_num {
        for j in 0..col_num {
            if !visited[i][j] {
                let (area, sides) = get_area_side(i, j, &garden, &mut visited);
                price += area * sides;
            }
        }
    }
    println!("{}", price);
}

fn main() {
    // part_one();
    part_two();
}
