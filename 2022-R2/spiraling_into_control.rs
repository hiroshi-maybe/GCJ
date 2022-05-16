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

// $ cp-batch spiraling_into_control | diff spiraling_into_control.out -
// $ cargo run --bin spiraling_into_control

///
/// 5/14/2022
///
/// 7:04-9:01 Test Set A
///
/// 5/15/2022
///
/// 11:00-11:40, 24:00-24:52 AC
///
/// https://codingcompetitions.withgoogle.com/codejam/round/00000000008778ec/0000000000b15a74#analysis
/// https://twitter.com/laycrs/status/1525514498937077761
/// https://twitter.com/kzyKT_M/status/1525515249738166272
/// https://twitter.com/tanakh/status/1525515979697950720
/// https://twitter.com/satanic0258/status/1525515309486346241
///

#[allow(dead_code)]
fn layer(i: i64, j: i64, n: i64) -> i64 {
    let ii = min(i, n - i - 1);
    let jj = min(j, n - j - 1);
    min(ii, jj)
}

fn ok(i: i64, j: i64, n: i64) -> bool {
    0 <= i && i < n && 0 <= j && j < n
}

fn dfs(
    i: usize,
    j: usize,
    n: usize,
    step: usize,
    k: usize,
    gg: &GridGraph,
    g: &Vec<Vec<usize>>,
    cur: &mut Vec<usize>,
) -> Option<Vec<usize>> {
    // dbgln!(i, j, g[i][j], step);
    if g[i][j] == n * n - 1 {
        return if step == k { Some(cur.clone()) } else { None };
    }

    for (ii, jj) in gg.adj_cells4(i, j) {
        if g[ii][jj] < g[i][j] {
            continue;
        }

        if g[ii][jj] - g[i][j] > 1 {
            cur.push(g[i][j]);
            cur.push(g[ii][jj]);
        }
        let r = dfs(ii, jj, n, step + 1, k, gg, g, cur);
        if r.is_some() {
            return r;
        }
        if g[ii][jj] - g[i][j] > 1 {
            cur.pop();
            cur.pop();
        }
    }
    return None;
}

fn positions(l: usize, a: usize, n: usize) -> Vec<usize> {
    let x = n - 2 * l;
    (1..=7).step_by(2).map(|c| x / 2 * c + a).collect_vec()
}

fn solve() -> Option<Vec<usize>> {
    let (n, k) = readln!(usize, usize);

    if k % 2 == 1 {
        return None;
    }
    if k < (n / 2) * 2 {
        return None;
    }

    let mut res = vec![];
    let mut a = 0;
    let mut rem = n * n - 1 - k;
    let mut i = 0;
    for l in 0..n / 2 {
        let x = n - 2 * l;
        let aa = a + (x - 1) * 4;

        let ps = positions(l, a, n);
        let ps2 = positions(l + 1, aa, n);
        let deltas = ps
            .iter()
            .zip(ps2.iter())
            .map(|(p, pp)| pp - p - 1)
            .collect_vec();

        let ii = deltas
            .iter()
            .enumerate()
            .position(|(ii, &delta)| delta <= rem && ii >= i);

        // dbgln!(l, rem, i, a, aa);
        // dbgln!(ps);
        // dbgln!(ps2);
        if let Some(ii) = ii {
            rem -= deltas[ii];
            i = ii;
            if deltas[ii] > 1 {
                res.push(ps[ii]);
                res.push(ps2[ii]);
            }
        }
        // dbgln!(l, rem, i, res);

        a = aa;
    }

    assert_eq!(rem, 0);
    return Some(res);
}

#[allow(dead_code)]
fn solve_bf() -> Option<Vec<usize>> {
    let (n, k) = readln!(i64, i64);

    if k % 2 == 1 {
        return None;
    }
    if k < (n / 2) * 2 {
        return None;
    }

    let gg = GridGraph::new(n as usize, n as usize);

    let mut g = vec![vec![n as usize * n as usize; n as usize]; n as usize];
    let moves = vec![(0, 1), (1, 0), (0, -1), (-1, 0)];
    let mut mi = 0;
    let mut i = 0;
    let mut j = 0;
    for step in 0..n * n {
        g[i as usize][j as usize] = step as usize;
        let domove = |i, j, mi: usize| (i + moves[mi].0, j + moves[mi].1);
        let (ii, jj) = domove(i, j, mi);
        if ok(ii, jj, n) && g[ii as usize][jj as usize] > step as usize {
            i = ii;
            j = jj;
        } else {
            mi = (mi + 1) % 4;
            let (ii, jj) = domove(i, j, mi);
            i = ii;
            j = jj;
        }
    }

    let mut cur = vec![];
    let res = dfs(0, 0, n as usize, 0, k as usize, &gg, &g, &mut cur);

    return res;
}

fn main() {
    setup_out!(put, puts);

    for t in 0..readln!(usize) {
        let res = solve();
        if let Some(r) = res {
            puts!("Case #{}: {}", t + 1, r.len() / 2);
            for i in 0..r.len() / 2 {
                puts!("{} {}", r[2 * i] + 1, r[2 * i + 1] + 1);
            }
        } else {
            puts!("Case #{}: IMPOSSIBLE", t + 1);
        }
    }
}

// region: grid_graph

#[rustfmt::skip]
#[allow(dead_code)]
mod grid_graph {
	pub struct GridGraph { h: usize, w: usize, }
	impl GridGraph { pub fn new(h: usize, w: usize) -> GridGraph { GridGraph { h, w } } }
	macro_rules! impl_adjacent_cells {
		($method: ident, $iterator: ident, $moves: expr) => {
			impl GridGraph {
				pub fn $method(&self, i: usize, j: usize) -> $iterator {
					assert!(i < self.h && j < self.w);
					$iterator { cur: 0, i: i as i64, j: j as i64, w: self.w as i64, h: self.h as i64 }
				}
			}
			pub struct $iterator { cur: usize, i: i64, j: i64, w: i64, h: i64 }
			impl Iterator for $iterator {
				type Item = (usize, usize);
				fn next(&mut self) -> Option<Self::Item> {
					for &(di,dj) in $moves[self.cur..].iter() {
						self.cur += 1;
						let (ii, jj) = (self.i + di, self.j + dj);
						if (0..self.h).contains(&ii) && (0..self.w).contains(&jj) {
							return Some((ii as usize, jj as usize));
						}
					}
					None
				}
			}
		}
	}
	impl_adjacent_cells!(adj_cells4, AdjacentCells4, vec![(1,0),(0,1),(-1,0),(0,-1)]);
	impl_adjacent_cells!(adj_cells2, AdjacentCells2, vec![(1,0),(0,1)]);
}
pub use grid_graph::GridGraph;

// endregion: grid_graph

#[test]
fn test() {
    use rand::prelude::*;

    let maxl = 10;
    let max_a = 7;
    loop {
        let mut rng = thread_rng();
        let n = rng.gen_range(1, maxl);
        let a = (0..n).map(|_| rng.gen_range(0, n)).collect_vec();

        let act = solve();

        let exp = 0;

        if act != exp {
            dbgln!(act, exp);
            dbgln!(s);
        }
    }
}
