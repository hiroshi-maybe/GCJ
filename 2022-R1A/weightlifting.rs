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

// $ cp-batch weightlifting | diff weightlifting.out -
// $ cargo run --bin weightlifting

///
/// 4/8/2022
///
/// 19:23-20:00 give up
///
/// 4/10/2022
///
/// 22:41-23:30 read editorial and got AC for small
///
/// https://codingcompetitions.withgoogle.com/codejam/round/0000000000877ba5/0000000000aa9280#analysis
///
/// https://twitter.com/laycrs/status/1512633984333000707
/// https://twitter.com/americaotogamer/status/1512634418271121414
/// https://twitter.com/tomerun/status/1512634030860431364
/// https://twitter.com/semiexp/status/1512636166256087044
/// https://twitter.com/semiexp/status/1512635123577257984
/// https://twitter.com/_su1sen/status/1512636534071382020
///

fn solve() -> i64 {
    let (e, w) = readln!(usize, usize);
    let mut x = readlns!([usize]; e);
    x.push(vec![0; w]);
    let mut q = VecDeque::new();
    q.push_back((vec![], 0, 0));
    let mut dist = HashSet::new();
    while let Some((st, step, d)) = q.pop_front() {
        if step == x.len() {
            assert!(st.is_empty());
            return d;
        }

        let mut check = |st: Vec<usize>| {
            let mut cnt = vec![0; w];
            for &w in &st {
                cnt[w] += 1;
            }
            if let Some(&n) = cnt.iter().max() {
                if n > 3 {
                    return;
                }
            }

            if cnt == x[step] {
                if dist.insert((st.clone(), step + 1)) {
                    q.push_back((st, step + 1, d + 1));
                }
            } else {
                if dist.insert((st.clone(), step)) {
                    q.push_back((st, step, d + 1));
                }
            }
        };

        for i in 0..w {
            let mut st2 = st.clone();
            st2.push(i);
            check(st2);
        }
        if !st.is_empty() {
            let mut st2 = st.clone();
            st2.pop();
            check(st2);
        }
    }

    unreachable!()
}

fn main() {
    setup_out!(put, puts);

    for t in 0..readln!(usize) {
        let res = solve();
        puts!("Case #{}: {}", t + 1, res);
    }
}
