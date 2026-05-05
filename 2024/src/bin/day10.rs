use std::{
    collections::{HashSet, VecDeque},
    fs,
};

fn part_one() {
    // Get topography map
    let data = fs::read_to_string("input/day10").expect("input file exists");
    let map = data.lines().collect::<Vec<&str>>();

    // Find trailhead and count score
    let mut total = 0;
    map.iter().enumerate().for_each(|(i, line)| {
        for (j, c) in line.chars().enumerate() {
            if c == '0' {
                total += count_score(i, j, &map, true);
            };
        }
    });

    println!("{}", total);
}

fn part_two() {
    // Get topography map
    let data = fs::read_to_string("input/day10").expect("input file exists");
    let map = data.lines().collect::<Vec<&str>>();

    // Find trailhead and count score
    let mut total = 0;
    map.iter().enumerate().for_each(|(i, line)| {
        for (j, c) in line.chars().enumerate() {
            if c == '0' {
                total += count_score(i, j, &map, false);
            };
        }
    });

    println!("{}", total);
}

fn print_deque(deque: &VecDeque<(isize, isize)>) {
    for (i, j) in deque {
        print!("({}, {}) ", i, j);
    }
    println!();
}

const X_DIFF: [isize; 4] = [0, 1, 0, -1];
const Y_DIFF: [isize; 4] = [-1, 0, 1, 0];

fn count_score(i: usize, j: usize, map: &Vec<&str>, is_part_one: bool) -> usize {
    let mut deque: VecDeque<(isize, isize)> = VecDeque::new();
    let mut visited: HashSet<(isize, isize)> = HashSet::new();
    let mut count = 0;
    let row_size = map.len() as isize;
    let col_size = map[0].len() as isize;
    visited.insert((i as isize, j as isize));

    deque.push_back((i as isize, j as isize));
    while let Some((x, y)) = deque.pop_front() {
        let c = map[x as usize].chars().nth(y as usize).unwrap();
        if c == '9' {
            // Found peak
            count += 1;
            continue;
        }

        // Add valid neighbours to queue
        let curr_num = c.to_digit(10).unwrap();
        for k in 0..4 {
            let new_x = x + X_DIFF[k];
            let new_y = y + Y_DIFF[k];

            if 0 <= new_x && new_x < col_size && 0 <= new_y && new_y < row_size {
                let next_num = map[new_x as usize]
                    .chars()
                    .nth(new_y as usize)
                    .unwrap()
                    .to_digit(10)
                    .unwrap();
                if next_num == curr_num + 1 {
                    if is_part_one {
                        if !visited.contains(&(new_x, new_y)) {
                            deque.push_back((new_x, new_y));
                            visited.insert((new_x, new_y));
                        }
                    } else {
                        deque.push_back((new_x, new_y));
                    }
                }
            }
        }
    }

    return count;
}

fn main() {
    part_one();
    part_two();
}
