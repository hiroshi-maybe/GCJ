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

// $ cp-batch letter_blocks | diff letter_blocks.out -
// $ cargo run --bin letter_blocks

///
/// 4/30/2022
///
/// 2:00-3:26 small and large AC
///
/// https://codingcompetitions.withgoogle.com/codejam/round/0000000000877b42/0000000000afe6a1#analysis
///
/// https://twitter.com/ei1333/status/1520365608801808384
/// https://twitter.com/_primenumber/status/1520365964881104896
/// https://twitter.com/satanic0258/status/1520366205777104897
///

fn to_i(c: char) -> usize {
    (c as u8 - b'A') as usize
}

fn solve() -> Option<Vec<char>> {
    let _n = readln!(i64);
    let s = readln!([String]);
    let s = s.iter().map(|s| s.chars().collect_vec()).collect_vec();
    let tot_len = s.iter().map(|cs| cs.len()).sum::<usize>();

    let mut singles = vec![vec![]; 26];
    let mut starts = vec![None; 26];
    let mut ends = vec![None; 26];
    for cs in s {
        let mut found = false;
        for c in 0..26 {
            let ch = (b'A' + c) as char;
            if cs.iter().filter(|&&x| x == ch).count() == cs.len() {
                singles[c as usize].append(&mut cs.clone());
                found = true;
                break;
            }
        }
        if !found {
            let is = to_i(cs[0]);
            let ie = to_i(*cs.last().unwrap());
            if starts[is].is_some() {
                return None;
            }
            starts[is] = Some(cs.clone());

            if ends[ie].is_some() {
                return None;
            }
            ends[ie] = Some(cs);
        }
    }

    let can_start = (0..26)
        .filter(|&i| starts[i].is_some() && ends[i].is_none())
        .collect_vec();
    let mut res: Vec<Vec<char>> = vec![];
    for c in can_start {
        let mut c = c;
        while let Some(cs) = &starts[c] {
            if !singles[c].is_empty() {
                res.push(singles[c].drain(0..).collect_vec());
            }
            res.push(cs.clone());
            c = to_i(*cs.last().unwrap());
        }
        if !singles[c].is_empty() {
            res.push(singles[c].drain(0..).collect_vec());
        }
    }
    for mut cs in singles {
        if !cs.is_empty() {
            res.push(cs.drain(0..).collect_vec());
        }
    }

    let res = res.iter().flatten().copied().collect_vec();
    if res.len() != tot_len {
        return None;
    }
    let mut ps = vec![vec![]; 26];
    for i in 0..res.len() {
        ps[to_i(res[i])].push(i);
    }
    for i in 0..26 {
        if ps[i].windows(2).any(|ps| ps[1] - ps[0] != 1) {
            return None;
        }
    }

    Some(res)
}

fn main() {
    setup_out!(put, puts);

    for t in 0..readln!(usize) {
        let res = solve();
        puts!(
            "Case #{}: {}",
            t + 1,
            if let Some(cs) = res {
                cs.iter().collect::<String>()
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
