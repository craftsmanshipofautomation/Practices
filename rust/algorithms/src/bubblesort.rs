
use crate::defs::*;


pub fn bubble_sort<T: PartialOrd + Clone>(arr: &mut [T], order: ORDER) {
    //type CMP<T> = fn (i: &T, j : &T) -> bool;
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
                swap(arr, j, j+1);
            }
        }
    }
}
