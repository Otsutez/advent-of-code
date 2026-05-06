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

fn main() {
    part_one();
}
