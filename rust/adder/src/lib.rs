mod front_of_house;

pub mod foo {
    use crate::front_of_house::hosting;
    pub fn eat_at_restaurant() -> i32 {
        hosting::add_to_waitlist();
        hosting::add_to_waitlist();
        hosting::add_to_waitlist();
        0
    }
}
