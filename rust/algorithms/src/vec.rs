pub fn can_visit_all_rooms(rooms: Vec<Vec<i32>>) -> bool {
    // 0: not key, 1: has key, 2: visited
    let mut keys: Vec<i32> = Vec::new();
    let mut nv = rooms.len();
    let mut notfound = true;
    keys.resize(rooms.len(), 0);
    let mut r = 0;
    loop {
        keys[r] = 2;
        nv -= 1;

        if nv == 0 {
            break;
        }

        for j in &rooms[r] {
            if keys[*j as usize] != 2 {
                keys[*j as usize] = 1;
            }
        }

        notfound = true;
        for k in 0..rooms.len() {
            if keys[k] == 1 {
                notfound = false;
                r = k;
                break;
            }
        }

        if notfound {
            return false;
        }

    }
    true
}
