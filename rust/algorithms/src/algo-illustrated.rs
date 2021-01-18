use crate::defs::*;

const decimal_base : i32 = 10;

pub fn karatsuba(a: i32, b: i32, n: i32) -> i32 {
    if a == 1 {
        b
    } else if b == 1{
        a
    }
    let p = a + b;
    let q = c + d;
    let mut pn : i32;
    if p > n/2 {
        pn = 
    }
    let ac = karatsuba(a, c, n / 2);
    let bd = karatsuba(b, d, n / 2);
    let pq = karatsuba(p, q, n >> 1)
    let abcd = pq - ac - bd;

    decimal_base.pow(n) * ac + decimal_base.pow(n/2) * abcd + bd
}