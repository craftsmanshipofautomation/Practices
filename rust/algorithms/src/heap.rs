use crate::defs::*;


fn heapify<T: PartialOrd + Clone + std::fmt::Debug>(arr: &mut [T], size: usize, i: usize, cmpfunc: CMP<T>)
{
    let mut extreme = i;
    if 2*i < size && cmpfunc(&arr[i], &arr[2*i]) {
        extreme = 2 * i; 
    }
    if 2*i + 1 < size && cmpfunc(&arr[extreme], &arr[2*i + 1]) {
        extreme = 2 * i + 1; 
    }
    if extreme != i {
        swap(arr, i, extreme);
        heapify(arr, size, extreme, cmpfunc);
    }
}

fn build_heap<T: PartialOrd + Clone + std::fmt::Debug>(arr: &mut [T], cmpfunc: CMP<T>)
{
    let len = arr.len();
    for i in (1..len/2+1).rev() {
        heapify(arr, len, i, cmpfunc);
    }
}

fn heapsort_<T: PartialOrd + Clone + std::fmt::Debug>(arr: &mut [T], cmpfunc: CMP<T>)
{
    let mut len = arr.len();
    build_heap(arr, cmpfunc);
    for _ in 2..arr.len() {
        len -= 1;
        swap(arr, 1, len);
        heapify(arr, len, 1, cmpfunc);
    }
}

pub fn heapsort<T: PartialOrd + Clone + std::fmt::Debug>(arr: &mut [T], order: ORDER) {
    let cmpfunc :CMP<T>;
    match order {
        ORDER::ASCENT => {
            cmpfunc = is_first_one_smaller;
        }
        ORDER::DESCENT => {
            cmpfunc = is_first_one_larger;
        }
    }
    heapsort_(arr, cmpfunc);
}
