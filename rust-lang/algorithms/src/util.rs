use rand::prelude::*;
#[allow(dead_code)]
pub fn fill_with_rand(arr: &mut [i32]) {
    println!("size: {}", arr.len());
    let mut rng = thread_rng();
    for i in arr {
        *i = rng.gen_range(0, 100);
        println!("{}", i);
    }
}