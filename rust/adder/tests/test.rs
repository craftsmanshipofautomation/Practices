
#[cfg(test)]
mod tests {
    pub use adder::foo;
    #[test]
    fn it_works() {
        assert_eq!(2 + 2, 4);
    }

    #[test]
    fn foo() {
        assert_eq!(foo::eat_at_restaurant(), 0);
    }

}