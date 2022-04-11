#![allow(unused_macros, unused_imports)]
use std::cmp::*;
use std::collections::*;
use std::process::exit;

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

// $ cargo build --bin equal_sum && python interactive_runner.py python3 local_testing_tool.py 0 -- ./target/debug/equal_sum

///
/// 4/8/2022
///
/// 18:34-19:23 give up
///
/// 4/9/2022
///
/// 22:40-23:00 read solution tweets
///
/// 4/10/2022
///
/// 21:30-22:30 AC after reading editorial
///
/// https://docs.google.com/document/d/1Yq384PEooRVsmlzB103YMLWwE_JhPN8AbxZagNrF_vY/edit#bookmark=id.4kkcbii5irpz
///
/// https://codingcompetitions.withgoogle.com/codejam/round/0000000000877ba5/0000000000aa8fc1
/// https://twitter.com/laycrs/status/1512633984333000707
/// https://twitter.com/americaotogamer/status/1512634418271121414
/// https://twitter.com/torus711/status/1512635285166694403
/// https://twitter.com/tomerun/status/1512634030860431364
/// https://twitter.com/kuuso1/status/1512635842434863110
/// https://twitter.com/tanakh/status/1512635688159653891
/// https://twitter.com/semiexp/status/1512635123577257984
///

fn to_s(a: &Vec<i64>) -> String {
    a.iter().map(|n| n.to_string()).collect_vec().join(" ")
}

fn solve() -> Vec<i64> {
    let n = readln!(usize);

    let mut a = (0..30).map(|i| 1 << i).collect_vec();
    for i in 0..(n - a.len()) {
        a.push(129 + i as i64);
    }

    println!("{}", to_s(&a));

    let b = readln!([i64]);
    if b[0] == -1 {
        exit(1);
    }

    let mut x = a[30..]
        .iter()
        .copied()
        .chain(b.iter().copied())
        .collect_vec();
    x.sort_unstable();

    let mut s1 = vec![];
    let mut s2 = vec![];
    let mut sum1 = 0;
    let mut sum2 = 0;
    for &x in x.iter().rev().chain(a[..30].iter().rev()) {
        if sum1 <= sum2 {
            sum1 += x;
            s1.push(x);
        } else {
            sum2 += x;
            s2.push(x);
        }
        // dbgln!(x, (sum1 - sum2).abs());
    }

    assert_eq!(sum1, sum2);

    s1
}

fn main() {
    // setup_out!(put, puts);

    for _ in 0..readln!(usize) {
        let res = solve();
        println!("{}", to_s(&res));
    }
}
