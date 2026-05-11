use std::cmp;
use std::fs;

use itertools::Itertools;

#[derive(Debug)]
struct Machine {
    a: (i128, i128),
    b: (i128, i128),
    prize: (i128, i128),
}

fn parse_x_y(mut line: &str) -> (i128, i128) {
    let mut start = line.find("+").or_else(|| line.find("=")).unwrap() + 1;
    let end = line.find(",").unwrap();
    let x = line[start..end].parse().unwrap();
    line = &line[end..];
    start = line.find("+").or_else(|| line.find("=")).unwrap() + 1;
    let y = line[start..].parse().unwrap();
    (x, y)
}

fn parse_machines(path: &str) -> Vec<Machine> {
    fs::read_to_string(path)
        .expect("file exists")
        .lines()
        .filter(|line| !line.is_empty())
        .chunks(3)
        .into_iter()
        .map(|mut chunk| Machine {
            a: parse_x_y(chunk.next().unwrap()),
            b: parse_x_y(chunk.next().unwrap()),
            prize: parse_x_y(chunk.next().unwrap()),
        })
        .collect()
}

fn calc_fewest_tokens(machine: &Machine) -> Option<i128> {
    // Using the hint that each button is pressed at most 100 times,
    // we bruteforce for the prize locations
    let mut tokens = None;
    for a_presses in 0..101 {
        for b_presses in 0..101 {
            let x = a_presses * machine.a.0 + b_presses * machine.b.0;
            let y = a_presses * machine.a.1 + b_presses * machine.b.1;
            if x == machine.prize.0 && y == machine.prize.1 {
                let cost = 3 * a_presses + b_presses;
                tokens = tokens.map_or(Some(cost), |t| Some(cmp::min(cost, t)));
            }
        }
    }
    tokens
}

// Solve two linear equations with 2 unknowns
fn calc_fewest_tokens_part_2(machine: &Machine) -> Option<i128> {
    let prize = (
        machine.prize.0 + 10000000000000,
        machine.prize.1 + 10000000000000,
    );
    let (ax, ay, bx, by, px, py) = (
        machine.a.0,
        machine.a.1,
        machine.b.0,
        machine.b.1,
        prize.0,
        prize.1,
    );

    let px_by_py_bx = px * by - py * bx;
    let ax_by_ay_bx = ax * by - ay * bx;
    if px_by_py_bx % ax_by_ay_bx != 0 {
        return None;
    }
    let a = px_by_py_bx / ax_by_ay_bx;
    if (px - a * ax) % bx != 0 {
        return None;
    }
    let b = (px - a * ax) / bx;
    Some(3 * a + b)
}

fn part_one() {
    let machines = parse_machines("input/day13");
    let total: i128 = machines
        .iter()
        .map(|machine| calc_fewest_tokens(machine))
        .filter_map(|tokens| tokens)
        .sum();
    println!("{}", total);
}

fn part_two() {
    let machines = parse_machines("input/day13");
    let total: i128 = machines
        .iter()
        .map(|machine| calc_fewest_tokens_part_2(machine))
        .filter_map(|tokens| tokens)
        .sum();
    println!("{}", total);
}

fn main() {
    // part_one();
    part_two();
}
