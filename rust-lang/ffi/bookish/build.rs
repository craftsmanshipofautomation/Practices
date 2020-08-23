extern crate cc;

fn main() {
    cc::Build::new()
        .file("src/aug23.c")
        .shared_flag(true)
        .compile("aug23");
}