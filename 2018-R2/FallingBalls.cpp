#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include <iostream>
#include <utility>
#include <cctype>
#include <queue>
#include <stack>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <unordered_set>
#include <unordered_map>
#include <limits.h>
#include <cstring>
#include <tuple>
#include <cassert>
#include <numeric>
using namespace std;
// type alias
typedef long long LL;
typedef vector < int > VI;
typedef unordered_map < int, int > MAPII;
typedef unordered_set < int > SETI;
typedef pair< int , int > II;
typedef tuple< int, int, int > III;
// repetition
#define FORE(i,a,b) for(int i=(a);i<=(b);++i)
#define REPE(i,n)  for(int i=0;i<=(n);++i)
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())
// DP
#define MINUS(dp) memset(dp, -1, sizeof(dp))
#define ZERO(dp) memset(dp, 0, sizeof(dp))
// minmax
#define SMAX(a,b) a = max(a,b)
#define SMIN(a,b) a = min(a,b)
// debug cerr
#define TRACE false
#define dump(x) if(TRACE) { cerr << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }

/*
 
 5/19/2018
 
 23:03-24:04 AC
 
 Editorials:
  - https://codejam.withgoogle.com/2018/challenges/0000000000007706/analysis/00000000000459f2
  - http://kmjp.hatenablog.jp/entry/2018/05/23/0900
  - http://yosupo.hatenablog.com/entry/2018/05/20/015213
 
 */

// iostream
// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out < x.in | diff x.out -
// 23:03-24:04 small
const int C_MAX=101;
int C;
int B[C_MAX];
int t;
const string no="IMPOSSIBLE";
void NO() { cout<<no<<endl; }
void solve() {
  if(B[0]<=0) { NO(); return; }
  if(B[C-1]<=0) { NO(); return; }
  if(accumulate(B,B+C,0)!=C) { NO(); return; }
  VI to(C,0);
  int cur=0;
  REP(i,C) {
    REP(_,B[i]) to[cur++]=i;
  }
  dump(t);
  dumpAR(to);
  
  int R=1;
  REP(i,C) SMAX(R,abs(i-to[i])+1);
  dump(R);
  vector<string> res(R,string(C,'.'));
  REP(i,C) if(to[i]!=i) {
    bool d=to[i]>i;
    dump2(i,d);
    for(int x=0; abs(x)<abs(to[i]-i); x+=(d?1:-1)) {
      char abc=(d?'\\':'/');
      res[abs(x)][i+x]=abc;
    }
  }
  cout<<R<<endl;
  REP(r,R) cout<<res[r]<<endl;
}
int main() {
  int T;
  cin >> T;
  for(t = 1; t <= T; ++t) {
    cin>>C;
    REP(i,C) cin>>B[i];
    
    cout << "Case #" << t << ": ";
    solve();
  }
  return 0;
}
