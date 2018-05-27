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
 
 5/19/2018
 
 24:05-25:00 give up
 
 5/27/2018
 
 16:00-18:17 read editorials and add solution
 
 Editorials:
  - https://codejam.withgoogle.com/2018/challenges/0000000000007706/analysis/00000000000459f3
  - http://kmjp.hatenablog.jp/entry/2018/05/23/0930
  - http://yosupo.hatenablog.com/entry/2018/05/20/015213
  - https://twitter.com/sigsegvvv/status/997880492312559616

 Tweets:
  - https://togetter.com/li/1229062
  - https://twitter.com/btk15049/status/997881295026905088
  - https://twitter.com/rickytheta/status/997878134102900736
  - https://twitter.com/TangentDay/status/997878270350643200
  - https://twitter.com/gzlcp/status/997878270472339456
  - https://twitter.com/DEGwer3456/status/997878301258432512
  - https://twitter.com/_TTJR_/status/997878746148306944
  - https://twitter.com/rickytheta/status/997879061182480385
 
 @tourist's simple implementation: https://codejam.withgoogle.com/2018/challenges/0000000000007706/attempts/for/Gennady.Korotkevich#
 
 Key:
  - Greedily give smaller number of balls in DP transition which upper-bounds numer of transitions
  - Put used balls in outer loop to guarantee pair of used balls are unique
  - Space can be saved by dropping used number of balls from dp table
  - Precomputation of all the cases is efficient
 
 Summary:
  - I thought this is DP problem though, I couldn't come up with state transition without duplicated pairs
  - No chance to solve without figuring out how to iterate unique pairs in dp 😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡
 
 */

// iostream
// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out < x.in | diff x.out -
/*
int R,B;
int dp[100][100][101];
void solve() {
  MINUS(dp);
  REPE(tot,R+B) dp[0][0][tot]=0;
  REPE(r,R)REPE(b,B)REPE(tot,R+B) if(dp[r][b][tot]>=0) {
    SMAX(dp[r][b][tot+1],dp[r][b][tot]);
    REP(rr,tot) {
      int bb=tot-rr;
      if(r+rr<=R&&b+bb<=B) SMAX(dp[r+rr][b+bb][tot],dp[r][b][tot]+1);
    }
  }
  int res=0;
  REPE(tot,R+B) SMAX(res,dp[R][B][tot]);
  cout<<res<<endl;
}
void test() {
  int r=0,b=0,j=0;
  for(int tot=1; r<=500&&b<=500; ++tot) {
    REPE(a,tot) {
      r+=a; b+=tot-r;
      if(r>500||b>500) break;
      ++j;
    }
  }
  dump(j);
}
*/

const int Inf=1e4;
int R,B;
int memo[51][51][51][51];
int f(int r, int b, int x, int y) {
  if(r<0||b<0) return -Inf;
  if(r==0&&b==0) return 0;
  if(x>R) return -Inf;

  int &res=memo[r][b][x][y];
  if(res>=0) return res;
  int x2=x,y2=y+1;
  if(y2>B) ++x2,y2=0;
  res=max(f(r,b,x2,y2), 1+f(r-x,b-y,x2,y2));
  return res;
}
void solve_small() {
  int res=f(R,B,0,1);
  cout<<res<<endl;
}

int dp[501][501];

void solve() {
  REPE(i,500)REPE(j,500) dp[i][j]=-Inf;
  dp[0][0]=0;
  REP(x,35)REP(y,35) if(x+y>0) {
    for(int i=500; i>=0; --i) for(int j=500; j>=0; --j) {
      if(i+x<=500&&j+y<=500) SMAX(dp[i+x][j+y],dp[i][j]+1);
    }
  }
}

int main() {
  // MINUS(memo);
  solve();

  int T;
  cin >> T;
  for(int t = 1; t <= T; ++t) {
    cin>>R>>B;
    
    cout << "Case #" << t << ": "<<dp[R][B]<<endl;
  }
  
//  test();
  
  return 0;
}
