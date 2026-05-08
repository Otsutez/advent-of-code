use std::cmp;
use std::fs;

use itertools::Itertools;

#[derive(Debug)]
struct Machine {
    button_a: (usize, usize),
    button_b: (usize, usize),
    prize: (usize, usize),
}

fn parse_x_y(mut line: &str) -> (usize, usize) {
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
            button_a: parse_x_y(chunk.next().unwrap()),
            button_b: parse_x_y(chunk.next().unwrap()),
            prize: parse_x_y(chunk.next().unwrap()),
        })
        .collect()
}

fn calc_fewest_tokens(machine: &Machine) -> Option<usize> {
    // Using the hint that each button is pressed at most 100 times,
    // we bruteforce for the prize locations
    let mut tokens = None;
    for a_presses in 0..101 {
        for b_presses in 0..101 {
            let x = a_presses * machine.button_a.0 + b_presses * machine.button_b.0;
            let y = a_presses * machine.button_a.1 + b_presses * machine.button_b.1;
            if x == machine.prize.0 && y == machine.prize.1 {
                let cost = 3 * a_presses + b_presses;
                tokens = tokens.map_or(Some(cost), |t| Some(cmp::min(cost, t)));
            }
        }
    }
    tokens
}

fn part_one() {
    let machines = parse_machines("input/day13");
    let total: usize = machines
        .iter()
        .map(|machine| calc_fewest_tokens(machine))
        .filter_map(|tokens| tokens)
        .sum();
    println!("{}", total);
}

fn main() {
    part_one();
}
