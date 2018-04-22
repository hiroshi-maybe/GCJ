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
#define TRACE true
#define dump(x) if(TRACE) { cerr << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }

/*

 4/19/2018
 
 18:30-18:45, 20:40-21:20 pause
 24:45-25:22 analysis
 25:22-25:38 submit
 
 4/20/2018
 
 I figured out that my solution takes exponential time.
 DP is needed according to the editorials...
 
 8:05-8:35 Give up
 8:35-9:30 Read editorials...
 
 Editorials:
  - https://codejam.withgoogle.com/2018/challenges/0000000000007883/analysis/000000000002fff7
  - http://kmjp.hatenablog.jp/entry/2018/04/22/1000
  - https://pitsbuffersolution.com/blog/articles/gcj2018_round1a.php
  - http://div9851.hatenadiary.com/entry/2018/04/14/132959
  - https://amalog.hateblo.jp/entry/gcj-2018-round1a
 
 Twitter comments:
  - dp
   - https://togetter.com/li/1217944
   - https://twitter.com/nico_shindannin/status/985010096148103168
   - https://twitter.com/btk15049/status/985001504615555072
   - https://twitter.com/koyumeishi_/status/984999854077231104
   - https://twitter.com/rickytheta/status/984998732214091776
   - https://twitter.com/btk15049/status/984998728011403264
   - https://twitter.com/konjo_p/status/984997750696628224
   - https://twitter.com/ei1333/status/984997708439044096
   - https://twitter.com/beet_aizu/status/984997569456521217
   - https://twitter.com/pazzle1230/status/984997329961811968
  - Interval merge
   - https://twitter.com/tanakh/status/985000552516866048
   - https://twitter.com/kusano_k/status/985000583160459264
   - https://twitter.com/Darsein/status/985001171457687552
   - https://twitter.com/satanic0258/status/984998929967104000
    - https://twitter.com/skyaozora/status/985004365231501312
 
 21:00-21:30 add my analysis and solution
 
 # Solution 1. dp
 
 If we brute-force selection of each cookie, it needs 2^N search space. We want to optimize it.
 For each cookie, we make a choice to cut it or not.
 
 a) we cut cookie whose dimension is `w` x `h`
 
 Perimeter increases by ∆ in range [2*min(w,h), 2*√w^2+h^2]
 
 b) we don't cut it
 
 Size of this cookie no longer affects
 
 Once cookie is selected, 2*min(w,h) length is mandatory.
 If it doesn't exceed, more room to be added up to 2*hypot(w,h) is preferred,
 so that we can adjust the perimeter to be as close as P.
 Thus `2*min(w,h)` is weight. We want to "maximize" bonus by 2*√w^2+h^2.
 This is knapsack dp problem.
 
 dp[x] = max(_, dp[x-2*min(w,h)]+2*hypot(w,h))
 
 res = S + max { min(P-S, dp[x]) : x=0..P-S }, S = 2* ∑ { w+h }
 
 # Solution 2. merge intervals
 
 We want to show that upper-bound of number of interval is small.
 When min(w,h) = a, we have minimal interval, which is [a,a*√2].
 In the worst case, we have this interval without any space.
 Suppose we have `n` intervals. Then...
 
 √2^n <= a*√2^n <= P-S (S = 2* ∑ { w+h }) <= P
 
 => √2^n <= P
 n <= log(P)/log(√2) < 54
 
 Thus the number of interval is upper-bounded by 54. We don't need to be worried about 2^N intervals.
 
 4/21/2018
 
 I confirmed both solutin #1 and #2 passes large set.
 
 Key:
  - dp or merge intervals
  - dp solution is smart and impressive
  - Interval solution needs deep analysis to prove that time limit does not exceed
 
 Summary:
  - I should have deeper analysis about merge interval
   - if possible value is small, it may not give exponential set
  - I couldn't reduce to knapsack problem from set of intervals
   - Maximizing "slack" is always optimal by sacrificing lower bound. This is the key to come up with it.
  - Implementation bugs in dp solution
   - wrong enumeration to lookup dp table
   - wrong upper-bound of lower range (`*100` was missing)
   - `*2` was missing in lower bound computation
 
 */

// iostream
// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG EdgyBaking.cpp && ./a.out < EdgyBaking.in | diff EdgyBaking.out -

// System test passed
double solve_mergeintervals(int N, int P, vector<II> &A) {
  double sum=0;
  FORR(a,A) sum+=2*(a.first+a.second);
  
  vector<pair<double,double>> rs={{sum,sum}};
  REP(i,N) {
    double a=2.0*min(A[i].first,A[i].second),b=2.0*hypot(A[i].first,A[i].second);
    vector<pair<double,double>> rs2=rs;
    FORR(r,rs) rs2.emplace_back(r.first+a, r.second+b);
    sort(rs2.begin(),rs2.end());
    rs.clear();
    FORR(r, rs2) {
      if(rs.empty()||rs.back().second<r.first) {
        rs.push_back(r);
      } else {
        rs.back().second=max(rs.back().second,r.second);
      }
    }
  }
  
  REP(i,SZ(rs)) dump2(rs[i].first,rs[i].second);
  
  double res=0;
  FORR(r,rs) if(r.first<=P) {
    if(r.second<P) res=r.second;
    else res=P;
  }
  return res;
}

double dp[50001];
double solve(int N, int P, vector<II> &A) {
  int sum=0;
  FORR(a,A) sum+=2*(a.first+a.second);
  
  ZERO(dp);
  REP(i,N) for(int x=50000; x>=0; --x) {
    int a=A[i].first,b=A[i].second;
    int y=2*min(a,b);
    if(x>=y) SMAX(dp[x], dp[x-y]+2*hypot(a,b));
  }
  
  double res=0, ub=P-1.0*sum;
  REPE(x,50000) {
    if(dp[x]>=0&&x<=ub) SMAX(res,min(ub,dp[x]));
  }
  return sum+res;
}

int main() {
  int T;
  cin >> T;
  for(int t = 1; t <= T; ++t) {
    int N,P;
    cin >> N >> P;
    vector<II> A;
    REP(_, N) {
      int w,h;
      cin >> w >> h;
      A.emplace_back(w,h);
    }
    double res = solve(N,P,A);
    printf("Case #%d: %f\n", t, res);
    //cout << "Case #" << t << ": " << res << endl;
  }
  return 0;
}
