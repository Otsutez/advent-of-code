use std::fs;

fn get_initial_stones(path: &str) -> Vec<usize> {
    fs::read_to_string(path)
        .expect("path exists")
        .trim()
        .split(" ")
        .map(|n| n.parse().unwrap())
        .collect()
}

fn blink(stones: &mut Vec<usize>) {
    let mut i = 0;
    while i < stones.len() {
        let stone = stones[i];
        // First rule
        if stone == 0 {
            stones[i] = 1;
            i += 1;
            continue;
        }

        // Second rule
        let stone = stone.to_string();
        if stone.len() % 2 == 0 {
            let left = &stone[..stone.len() / 2];
            let right = &stone[stone.len() / 2..];
            stones[i] = right.parse().unwrap();
            stones.insert(i, left.parse().unwrap());
            i += 2;
            continue;
        }

        // Third rule
        stones[i] *= 2024;
        i += 1;
    }
}

fn part_one() {
    let mut stones = get_initial_stones("input/day11");
    for _ in 0..25 {
        blink(&mut stones);
    }
    println!("{}", stones.len());
}

fn main() {
    part_one();
}
