use rand::prelude::*;

#[allow(dead_code)]
pub fn fill_with_rand(arr: &mut [i32]) {
    let mut rng = thread_rng();
    for i in arr {
        *i = rng.gen_range(0, 100);
    }
}

pub fn print_array(arr: &[i32]) {
    print!("\n[");
    for i in arr {
        print!("{}, ", i);
    }
    print!("]");
}
