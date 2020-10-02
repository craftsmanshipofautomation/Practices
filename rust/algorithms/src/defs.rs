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

pub fn swap<T: PartialOrd + Clone>(arr: &mut[T], i: usize, j: usize) {
    let temp: T = arr[i].clone();
    arr[i] = arr[j].clone();
    arr[j] = temp;
}

pub type CMP<T> = fn (i: &T, j : &T) -> bool;
