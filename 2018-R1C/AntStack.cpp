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
 
 5/5/2018
 
 19:41-20:20 small ACC
 
 5/10/2018
 
 15:00-15:50 Read editorials and solve by myself
 
 Editorial:
  - https://codejam.withgoogle.com/2018/challenges/0000000000007765/analysis/000000000003e0a8
  - http://kmjp.hatenablog.jp/entry/2018/05/06/1000
  - http://kazune-lab.net/contest/2018/05/05/gcj2018round1c/
  - http://memo.sugyan.com/entry/2018/05/06/205751
 
 Tweets:
  - https://twitter.com/butsurizuki/status/992728136117727233
  - https://twitter.com/_olphe/status/992731837003841536
  - https://twitter.com/dfnPer/status/992730509481410560
  - https://twitter.com/noss46/status/992730589034770434

 1. The most important point is that result is upper-bounded by K=139 (from official editorial).
 2. One typical dp technique is having weight in value instead of state in knapsack dp.
 From #1 and #2 we can solve this problem by O(N*K) dp (≈2*10^7).
 
 dp[i+1][k+1] = min(_, dp[i][k]+w[i]) if 6*w[i]>=dp[i][k]
 dp[i+1][k] = min(_, dp[i][k])
 
 Summary:
  - I wondered if there exists greedy solution during the contest from large constraint. However that's not the case 😅
  - Moving out weight in knapsack problem from state parameter to value is typical technique
  - Experiment is important to figure out accurate upper-bound
  - Very impressive problem. Proof technique is examined 👍
 
 */

// iostream
// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out < x.in | diff x.out -
const int MAX_N=1e5+1;
LL W[MAX_N];
int N;

int memo[101][100001];
int f(int i, int w) {
  if(i==N) return 0;
  int &res=memo[i][w];
  if(res>=0) return res;
  res=0;
  if(w<=W[i]*6) res=max(res,1+f(i+1,w+W[i]));
  res=max(res,f(i+1,w));
  
  return res;
}

int solve_org_small() {
  MINUS(memo);
  return f(0,0);
}

const LL Inf=1e18;
const int MAX_K=150;
LL dp[MAX_N][MAX_K];
int solve() {
  REPE(i,N)REPE(k,MAX_K) dp[i][k]=Inf;
  dp[0][0]=0;
  REP(i,N)REP(k,MAX_K) if(dp[i][k]<Inf) {
    if(6LL*W[i]>=dp[i][k]) SMIN(dp[i+1][k+1],dp[i][k]+W[i]);
    SMIN(dp[i+1][k],dp[i][k]);
  }
  int res=0;
  REPE(k,MAX_K) if(dp[N][k]<Inf) SMAX(res,k);
  return res;
}

void calcMaximalRes() {
  VI X;
  LL sum=0,cur=1;
  while(cur<=1e9) {
    if(sum<=cur*6) {
      sum+=cur;
      X.push_back(cur);
    } else {
      // sum>6*cur
      while(sum>6*cur) ++cur;
      sum+=cur;
      X.push_back(cur);
    }
  }

  dump3(cur,sum,SZ(X));
  dumpAR(X);
  
  // cur = 1165669553, sum = 8159686869, SZ(X) = 140
  // 1,1,1,1,1,1,1,2,2,2,3,3,4,4,5,6,7,8,9,11,13,15,17,20,23,27,32,37,43,50,59,69,80,93,109,127,148,173,202,235,275,320,374,436,509,594,693,808,943,1100,1283,1497,1747,2038,2377,2774,3236,3775,4404,5138,5995,6994,8160,9520,11106,12957,15117,17636,20576,24005,28006,32673,38119,44472,51884,60531,70620,82390,96122,112142,130832,152638,178077,207757,242383,282780,329910,384895,449044,523885,611199,713066,831910,970562,1132322,1321042,1541216,1798085,2097766,2447394,2855293,3331175,3886371,4534099,5289782,6171413,7199982,8399979,9799975,11433304,13338855,15561997,18155664,21181608,24711876,28830522,33635609,39241543,45781801,53412101,62314118,72699804,84816438,98952511,115444596,134685362,157132922,183321743,213875367,249521261,291108138,339626161,396230521,462268941,539313765,629199392,734065958,856410284,999145331,1165669553,
}

int main() {
  int T;
  cin >> T;
  for(int t = 1; t <= T; ++t) {
    cin >>N;
    REP(i,N) cin>>W[i];
    
    cout << "Case #" << t << ": ";
    cout << solve();
    cout << endl;
  }
  
//  calcMaximalRes();
  
  return 0;
}
