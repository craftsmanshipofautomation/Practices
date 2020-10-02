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
        assert_eq!(algorithms::defs::is_first_one_larger(&i, &j), false);
        assert_eq!(algorithms::defs::is_first_one_smaller(&j, &i), false);
    }

    use algorithms::bubblesort;
    use algorithms::util;
    //use algorithms::strop;
    //use algorithms::vec;
    use algorithms::defs;
    use algorithms::heap;
    
    #[test]
    fn test_bubble_sort() {
        let mut arr: [i32;10] = [0; 10];
        util::fill_with_rand(&mut arr);
        //util::print_array(&arr);
        bubblesort::bubble_sort(&mut arr, defs::ORDER::ASCENT);
        //util::print_array(&arr);
    }
    #[test]
    fn test_bubble_sort2() {
        let mut arr: [i32;10] = [0; 10];
        util::fill_with_rand(&mut arr);
        //util::print_array(&arr);
        bubblesort::bubble_sort(&mut arr, defs::ORDER::DESCENT);
        //util::print_array(&arr);
    }
    
    #[test]
    fn test_heapsort()
    {

        let mut arr: [i32; 11] = [0, 10, 9 ,8, 7, 6, 5, 4, 3, 2, 1];
        heap::heapsort(&mut arr, defs::ORDER::ASCENT);
        assert_eq!(arr, [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10]);
        heap::heapsort(&mut arr, defs::ORDER::DESCENT);
        assert_eq!(arr, [0, 10, 9 ,8, 7, 6, 5, 4, 3, 2, 1]);


    }




}