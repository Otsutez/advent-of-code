use std::{collections::HashMap, fs};

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
    for _ in 0..75 {
        blink(&mut stones);
    }
    println!("{}", stones.len());
}

fn count_digit(mut num: usize) -> usize {
    if num == 0 {
        return 1;
    }
    let mut count = 0;
    while num > 0 {
        num /= 10;
        count += 1;
    }
    count
}

fn is_even_digit(num: usize) -> bool {
    count_digit(num) % 2 == 0
}

fn get_left(num: usize) -> usize {
    let count = count_digit(num) as u32;
    num / (10usize.pow(count / 2))
}

fn get_right(num: usize) -> usize {
    let count = count_digit(num) as u32;
    num % (10usize.pow(count / 2))
}

fn count(stone: usize, map: &mut HashMap<(usize, usize), usize>, depth: usize) -> usize {
    // Base case
    if depth == 75 {
        return 1;
    }
    // If already computed return computed value
    if map.contains_key(&(stone, depth)) {
        return *map.get(&(stone, depth)).unwrap();
    }
    // Compute
    let c = if stone == 0 {
        count(1, map, depth + 1)
    } else if is_even_digit(stone) {
        count(get_left(stone), map, depth + 1) + count(get_right(stone), map, depth + 1)
    } else {
        count(stone * 2024, map, depth + 1)
    };
    map.insert((stone, depth), c);
    return c;
}

fn part_two() {
    let stones = get_initial_stones("input/day11"); // [125, 17]
    let mut total = 0;
    let mut map = HashMap::new();
    for stone in stones {
        total += count(stone, &mut map, 0);
    }
    println!("{}", total);
    // println!("{:?}", map);
}

fn main() {
    // part_one();
    part_two();
}
