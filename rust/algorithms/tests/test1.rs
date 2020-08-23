#[cfg(test)]
mod tests {
    #[test]
    fn it_works() {
        assert_eq!(2 + 2, 4);
    }
    #[test]
    fn test_rand() {
        let mut arr: [i32;5] = [0, 0, 0, 0, 0];
        algorithms::util::fill_with_rand(&mut arr)
    }

    #[test]
    fn test_swap() {
        let mut i: i32 = 5;
        let mut j: i32 = 6;
        std::mem::swap(&mut i, &mut j);
        assert_eq!(i, 6);
        assert_eq!(j, 5);
    }

    #[test]
    fn test_ord() {
        // can't do that :(
        // assert_eq!(algorithms::sorting::is_first_one_larger(2, 3), false);
        let i = 1;
        let j = 2;
        assert_eq!(algorithms::sorting::is_first_one_larger(&i, &j), false);
        assert_eq!(algorithms::sorting::is_first_one_smaller(&j, &i), false);
    }

    use algorithms::sorting;
    use algorithms::util;
    #[test]
    fn test_bubble_sort() {
        let mut arr: [i32;10] = [0; 10];
        util::fill_with_rand(&mut arr);
        util::print_array(&arr);
        sorting::bubble_sort(&mut arr, sorting::ORDER::ASCENT);
        util::print_array(&arr);
    }
    #[test]
    fn test_bubble_sort2() {
        let mut arr: [i32;10] = [0; 10];
        util::fill_with_rand(&mut arr);
        util::print_array(&arr);
        sorting::bubble_sort(&mut arr, sorting::ORDER::DESCENT);
        util::print_array(&arr);
    }
}
