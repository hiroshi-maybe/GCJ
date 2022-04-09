#![allow(unused_macros, unused_imports)]
use std::cmp::*;
use std::collections::*;

use crate::cplib::io::*;
use crate::cplib::minmax::*;
use crate::cplib::vec::*;
// region: cplib
#[rustfmt::skip]
#[allow(dead_code)]
#[macro_use]
pub mod cplib {
#[macro_use]
pub mod io {
	macro_rules! _with_dollar_sign { ($($body:tt)*) => { macro_rules! __with_dollar_sign { $($body)* } __with_dollar_sign!($); }}
	macro_rules! setup_out {
		($fn:ident,$fn_s:ident) => {
			use std::io::Write;
			let out = std::io::stdout();
			let mut out = ::std::io::BufWriter::new(out.lock());
				_with_dollar_sign! { ($d:tt) => {
				macro_rules! $fn { ($d($format:tt)*) => { let _ = write!(out,$d($format)*); } }
				macro_rules! $fn_s { ($d($format:tt)*) => { let _ = writeln!(out,$d($format)*); } }
			}}
		};
	}
	macro_rules! _epr { ($v:expr $(,)?) => {eprint!("{} = {:?}, ", stringify!($v), $v)}; }
	macro_rules! dbgln { ($($val:expr),*) => {{ eprint!("[{}:{}] ", file!(), line!()); ($(_epr!($val)),*); eprintln!(); }}; }
	pub fn readln_str() -> String {
		let mut line = String::new();
		::std::io::stdin().read_line(&mut line).unwrap_or_else(|e| panic!("{}", e));
		line
	}
	macro_rules! _read {
		($it:ident; [char]) => { _read!($it; String).chars().collect::<Vec<_>>() };
		($it:ident; [u8]) => { Vec::from(_read!($it; String).into_bytes()) };
		($it:ident; usize1) => { $it.next().unwrap_or_else(|| panic!("input mismatch")).parse::<usize>().unwrap_or_else(|e| panic!("{}", e)) - 1 };
		($it:ident; [usize1]) => { $it.map(|s| s.parse::<usize>().unwrap_or_else(|e| panic!("{}", e)) - 1).collect::<Vec<_>>() };
		($it:ident; [$t:ty]) => { $it.map(|s| s.parse::<$t>().unwrap_or_else(|e| panic!("{}", e))).collect::<Vec<_>>() };
		($it:ident; $t:ty) => { $it.next().unwrap_or_else(|| panic!("input mismatch")).parse::<$t>().unwrap_or_else(|e| panic!("{}", e)) };
		($it:ident; $($t:tt),+) => { ($(_read!($it; $t)),*) };
	}
	macro_rules! readlns {
		($($t:tt),*; $n:expr) => {{ let stdin = ::std::io::stdin();
			::std::io::BufRead::lines(stdin.lock()).take($n).map(|line| {
				let line = line.unwrap(); #[allow(unused_mut)]let mut it = line.split_whitespace(); _read!(it; $($t),*)
			}).collect::<Vec<_>>()
		}};
	}
	macro_rules! readln {
		($($t:tt),*) => {{ let line = cplib::io::readln_str(); #[allow(unused_mut)]let mut it = line.split_whitespace(); _read!(it; $($t),*) }};
	}
}
#[macro_use]
pub mod minmax {
	pub trait SetMinMax {
		fn setmin(&mut self, other: Self) -> bool;
		fn setmax(&mut self, other: Self) -> bool;
	}
	macro_rules! _set { ($self:ident, $cmp:tt, $other:ident) => {{
			let update = $other $cmp *$self;
			if update { *$self = $other; }
			update
	}}; }
	impl<T> SetMinMax for T where T: PartialOrd {
		fn setmin(&mut self, other: T) -> bool { _set!(self, <, other) }
		fn setmax(&mut self, other: T) -> bool { _set!(self, >, other) }
	}
}
#[macro_use]
pub mod vec {
	pub trait CollectVec: Iterator { fn collect_vec(self) -> Vec<Self::Item> where Self: Sized { self.collect() } }
	impl<T> CollectVec for T where T: Iterator {}
	macro_rules! vvec {
		($v:expr; $n:expr) => { Vec::from(vec![$v; $n]) };
		($v:expr; $n:expr $(; $ns:expr)+) => { Vec::from(vec![vvec![$v $(; $ns)*]; $n]) };
	}
}
}
// endregion: cplib

// region: bitmask
#[rustfmt::skip]
#[allow(dead_code)]
mod bitmask {
	#[derive(Debug, Copy, Clone)]
	pub struct BitMask(usize);
	impl BitMask {
		pub fn new(max_power_of_two: usize) -> BitMask { BitMask(max_power_of_two) }
		pub fn iter(&self) -> BitMaskIterator { BitMaskIterator(0..1<<self.0) }
	}
	impl IntoIterator for BitMask {
		type Item = BitSet; type IntoIter = BitMaskIterator;
		fn into_iter(self) -> Self::IntoIter { self.iter() }
	}

	//#[derive(IntoItarator)]
	pub struct BitMaskIterator(std::ops::Range<usize>);
	impl Iterator for BitMaskIterator {
		type Item = BitSet;
		fn next(&mut self) -> Option<Self::Item> {
			self.0.next().map(|m| BitSet(m))
		}
	}

	#[derive(Debug, PartialEq, Copy, Clone)]
	pub struct BitSet(usize);
	impl BitSet {
		pub fn ith(&self, i: usize) -> bool { (self.0 >> i) & 1 == 1 }
		pub fn ones(&self) -> BitSetOnesIterator {
			BitSetOnesIterator { set: BitSet(self.0), iter: 0..(self.0.count_ones() + self.0.count_zeros()) as usize }
		 }
	}
	impl From<usize> for BitSet {
		fn from(val: usize) -> BitSet { BitSet(val) }
	}
	pub struct BitSetOnesIterator { set: BitSet, iter: std::ops::Range<usize> }
	impl Iterator for BitSetOnesIterator {
		type Item = usize;
		fn next(&mut self) -> Option<Self::Item> {
			let set = self.set; self.iter.find(|&i| set.ith(i))
		}
	}
}
pub use bitmask::{BitMask, BitSet};
// endregion: bitmask

// $ cp-batch double_or_one_thing | diff double_or_one_thing.out -
// $ cargo run --bin double_or_one_thing

///
/// 4/8/2022
///
/// 18:00-18:32 AC
///
/// https://codingcompetitions.withgoogle.com/codejam/round/0000000000877ba5/0000000000aa8e9c#analysis
///

fn solve(s: &Vec<char>) -> String {
    let n = s.len();

    let mut res = vec![];
    for i in 0..n {
        let mut ss = res.clone();
        ss.push(s[i]);
        let mut x = ss.clone();
        let mut y = x.clone();
        y.push(s[i]);
        for j in i + 1..n {
            x.push(s[j]);
            y.push(s[j]);
        }
        if x < y {
            res = ss;
        } else {
            ss.push(s[i]);
            res = ss;
        }
        // dbgln!(res);
    }

    res.iter().collect::<String>()
}

fn main() {
    setup_out!(put, puts);

    for t in 0..readln!(usize) {
        let s = readln!([char]);
        let res = solve(&s);
        puts!("Case #{}: {}", t + 1, res);
    }
}

#[test]
fn test_bruteforce() {
    use rand::prelude::*;

    let maxl = 10;
    let crange = 7;
    loop {
        let mut rng = thread_rng();
        let n = rng.gen_range(1, maxl);
        let s = (0..n)
            .map(|_| (b'A' + rng.gen_range(0u8, crange)) as char)
            .collect_vec();

        let act = solve(&s);

        let mut exp = (0..2 * n).map(|_| 'Z').collect_vec();
        for mask in BitMask::new(n) {
            let mut x = vec![];
            for i in 0..n {
                x.push(s[i]);
                if mask.ith(i) {
                    x.push(s[i]);
                }
            }
            exp.setmin(x);
        }
        let exp = exp.iter().collect::<String>();

        if act != exp {
            dbgln!(act, exp);
            dbgln!(s.iter().collect::<String>());
        }
        dbgln!(s, exp);
    }
}
