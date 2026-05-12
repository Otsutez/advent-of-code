use regex::Regex;

#[derive(Debug)]
struct Robot((isize, isize), (isize, isize));

const WIDTH: isize = 101;
const HEIGHT: isize = 103;

fn parse_robots(path: &str) -> Vec<Robot> {
    let re = Regex::new(r"p=(\d+),(\d+)\sv=(-?\d+),(-?\d+)").unwrap();
    let hay = std::fs::read_to_string(path).expect("File exists");
    re.captures_iter(&hay)
        .map(|c| {
            Robot(
                (c[1].parse().unwrap(), c[2].parse().unwrap()),
                (c[3].parse().unwrap(), c[4].parse().unwrap()),
            )
        })
        .collect()
}

fn simulate(robots: &mut Vec<Robot>) {
    for Robot((x, y), (vx, vy)) in robots {
        *x = (*x + *vx).rem_euclid(WIDTH);
        *y = (*y + *vy).rem_euclid(HEIGHT);
    }
}

fn calc_safety_factor(robots: &Vec<Robot>) -> isize {
    let (mut first, mut second, mut third, mut fourth) = (0, 0, 0, 0);
    for Robot((x, y), (_, _)) in robots {
        if 0 <= *x && *x < WIDTH / 2 && 0 <= *y && *y < HEIGHT / 2 {
            first += 1;
        } else if 0 <= *x && *x < WIDTH / 2 && HEIGHT / 2 < *y && *y < HEIGHT {
            second += 1;
        } else if WIDTH / 2 < *x && *x < WIDTH && 0 <= *y && *y < HEIGHT / 2 {
            third += 1;
        } else if WIDTH / 2 < *x && *x < WIDTH && HEIGHT / 2 < *y && *y < HEIGHT {
            fourth += 1;
        }
    }

    first * second * third * fourth
}

fn is_lined_up(tiles: &Vec<Vec<usize>>) -> bool {
    for line in tiles {
        let mut count = 0;
        let mut max = 0;
        for x in line {
            if *x != 0 {
                count += 1;
                max = std::cmp::max(max, count);
            } else {
                count = 0;
            }
        }
        if max >= 10 {
            return true;
        }
    }

    return false;
}

fn print_tiles(robots: &Vec<Robot>, num: usize) {
    let mut tiles = vec![vec![0; HEIGHT as usize]; WIDTH as usize];
    for Robot((x, y), _) in robots {
        tiles[*x as usize][*y as usize] += 1;
    }

    if is_lined_up(&tiles) {
        println!("{}", num);
        for line in tiles {
            for x in line {
                if x == 0 {
                    print!(".");
                } else {
                    print!("{}", x);
                }
            }
            println!();
        }
        println!();
    }
}

fn part_one() {
    let mut robots = parse_robots("input/day14");
    for i in 0..6000 {
        simulate(&mut robots);
        print_tiles(&robots, i + 1);
    }
    let safety_factor = calc_safety_factor(&robots);
    println!("{}", safety_factor);
}

fn main() {
    part_one();
}
