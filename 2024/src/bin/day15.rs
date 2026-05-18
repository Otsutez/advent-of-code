fn get_map_and_moves(path: &str) -> (Vec<Vec<char>>, Vec<char>) {
    let data = std::fs::read_to_string(path).expect("file exists");
    // Get map
    let mut lines = data.lines();
    let mut map = Vec::new();
    while let Some(line) = lines.next() {
        if line.is_empty() {
            break;
        }
        map.push(line.chars().collect());
    }

    let mut moves = Vec::new();
    while let Some(line) = lines.next() {
        line.chars().for_each(|c| moves.push(c));
    }
    return (map, moves);
}

fn get_robot_pos(map: &Vec<Vec<char>>) -> (isize, isize) {
    for i in 0..map.len() {
        for j in 0..map[i].len() {
            if map[i][j] == '@' {
                return (j as isize, i as isize);
            }
        }
    }
    !unreachable!()
}

fn print_map(map: &Vec<Vec<char>>) {
    for line in map {
        for char in line {
            print!("{}", char);
        }
        println!();
    }
    println!();
}

fn get_sum_gps(map: &Vec<Vec<char>>) -> usize {
    let mut sum = 0;
    for r in 0..map.len() {
        for c in 0..map[0].len() {
            if map[r][c] == 'O' {
                sum += 100 * r + c;
            }
        }
    }
    return sum;
}

fn part_one() {
    let (mut map, moves) = get_map_and_moves("input/day15");

    let (mut x, mut y) = get_robot_pos(&map);
    for c in moves {
        // The robot will never be at the edge of the map, there will always be spaces around him
        let (diff_x, diff_y) = match c {
            '<' => (-1, 0),
            'v' => (0, 1),
            '>' => (1, 0),
            _ => (0, -1),
        };
        let (mut curr_x, mut curr_y) = (x + diff_x, y + diff_y);
        while map[curr_y as usize][curr_x as usize] == 'O' {
            curr_x += diff_x;
            curr_y += diff_y;
        }
        if map[curr_y as usize][curr_x as usize] == '.' {
            // Empty space at the end, move robots and boxes
            let op_diff_x = -diff_x;
            let op_diff_y = -diff_y;
            while curr_x != x || curr_y != y {
                let (next_x, next_y) = (curr_x + op_diff_x, curr_y + op_diff_y);
                map[curr_y as usize][curr_x as usize] = map[next_y as usize][next_x as usize];
                curr_x = next_x;
                curr_y = next_y;
            }
            map[y as usize][x as usize] = '.';
            x += diff_x;
            y += diff_y;
        }
    }
    print_map(&map);
    println!("{}", get_sum_gps(&map));
}

fn main() {
    part_one();
}
