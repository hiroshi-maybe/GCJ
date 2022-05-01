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

// $ cp-batch squary | diff squary.out -
// $ cargo run --bin squary

///
/// 4/30/2022
///
/// 3:27-3:42 small
/// 4:15 give up
///
/// 10:10-10:55 read editorials and AC
///
/// https://codingcompetitions.withgoogle.com/codejam/round/0000000000877b42/0000000000afdf76
///
/// https://twitter.com/ei1333/status/1520365608801808384
/// https://twitter.com/_primenumber/status/1520365964881104896
/// https://twitter.com/satanic0258/status/1520366205777104897
///

fn solve() -> Option<Vec<i64>> {
    let (n, k) = readln!(usize, usize);
    let e = readln!([i64]);

    let s = e.iter().sum::<i64>();
    let sqs = e.iter().map(|&a| a * a).sum::<i64>();

    if k == 1 {
        let res = sqs - s * s;

        if s == 0 {
            return if sqs == 0 { Some(vec![0]) } else { None };
        }

        if res % (2 * s) == 0 {
            Some(vec![res / (2 * s)])
        } else {
            None
        }
    } else {
        let n1 = 1 - s;
        let mut n2 = 0;
        for j in 0..n {
            for i in 0..j {
                n2 += e[i] * e[j];
            }
        }
        n2 += n1 * s;
        n2 *= -1;
        dbgln!(s, sqs, n1, n2);
        Some(vec![n1, n2])
    }
}

fn main() {
    setup_out!(put, puts);

    for t in 0..readln!(usize) {
        let res = solve();
        puts!(
            "Case #{}: {}",
            t + 1,
            if let Some(r) = res {
                r.iter().map(|a| a.to_string()).collect_vec().join(" ")
            } else {
                String::from("IMPOSSIBLE")
            }
        );
    }
}

#[test]
fn test() {
    use rand::prelude::*;

    let maxl = 10;
    let max_a = 7;
    loop {
        let mut rng = thread_rng();
        let n = rng.gen_range(1, maxl);
        let a = (0..n).map(|_| rng.gen_range(0u8, crange)).collect_vec();

        let act = solve();

        let exp = 0;

        if act != exp {
            dbgln!(act, exp);
            dbgln!(s);
        }
    }
}
