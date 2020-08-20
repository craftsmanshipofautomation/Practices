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
    fn test_bubble_sort() {
        
    }
}
