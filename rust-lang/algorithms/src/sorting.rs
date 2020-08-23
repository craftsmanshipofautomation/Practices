#[allow(unused_imports)]
use std::mem;

pub enum ORDER {
    ASCENT,
    DESCENT,
}

pub fn is_first_one_larger<T: PartialOrd>(i: &T, j: &T) -> bool {
    return i > j;
}

pub fn is_first_one_smaller<T: PartialOrd>(i: &T, j: &T) -> bool {
    return i < j;
}
pub fn bubble_sort<T: PartialOrd + Clone>(arr: &mut [T], order: ORDER) {
    type CMP<T> = fn (i: &T, j : &T) -> bool;
    let cmp: CMP<T>;
    match order {
        ORDER::ASCENT => {
            cmp = is_first_one_larger;
        }
        ORDER::DESCENT => {
            cmp = is_first_one_smaller;
        }
    }
    for i in 0..arr.len() {
        for j in 0..(arr.len()-1-i) {
            if cmp(&arr[j], &arr[j+1]) {
                let temp: T = arr[j].clone();
                arr[j] = arr[j+1].clone();
                arr[j+1] = temp;
            }
        }
    }
}
