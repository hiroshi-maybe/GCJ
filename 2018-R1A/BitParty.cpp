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
 
 4/7/2018 R1A
 
 20:05-20:30 I didn't have much time during the contest. I just solved Small set. However no luck 😞
 
 4/19/2018
 
 Retry the problem
 
 16:30-16:53 analysis
 16:54-17:20 pause
 18:10-18:33 solved
 
 Editorials:
  - https://codejam.withgoogle.com/2018/challenges/0000000000007883/analysis/000000000002fff6
  - http://div9851.hatenadiary.com/entry/2018/04/14/132959
  - https://pitsbuffersolution.com/blog/articles/gcj2018_round1a.php
  - tweets mentioning to solution
   - https://twitter.com/kusano_k/status/985000583160459264
   - https://twitter.com/tanakh/status/985000552516866048
   - https://twitter.com/koyumeishi_/status/984999854077231104
   - https://twitter.com/satanic0258/status/984998929967104000
   - https://twitter.com/rickytheta/status/984998732214091776
   - https://twitter.com/ei1333/status/984997708439044096
   - https://twitter.com/beet_aizu/status/984997569456521217
   - https://twitter.com/pazzle1230/status/984997329961811968
 
 Key:
  - https://twitter.com/noisy_noimin/status/984999257013800960
 
 4/21/2018
 
 13:30-15:26 fix bugs and verify code in practice mode
 
 Summary:
  - Found implementaion bugs in practice mode
   - ignoring cashers when maximal number of bits is more than `m`
   - sort is missing
   - overflow bug of m,s,p (45 mins debug)
   - overflow bug of B (10 mins debug)
   - overflow bug of signature of a function
   - overflow bug of res
  - too many overflows 👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎
 
 */

// iostream
// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG xxxxx.cpp && ./a.out < xxxxx.in

bool ok(LL t, LL R, LL B, LL C, vector<vector<LL>> &A) {
  vector<LL> xs;
  REP(i,C) {
    LL m=A[i][0],s=A[i][1],p=A[i][2];
    LL n=max(0LL,(t-p)/s);
    n=min(n, m);
    xs.push_back(n);
  }
  sort(xs.rbegin(),xs.rend());
  LL tot=accumulate(xs.begin(),xs.begin()+R,0LL);
  return tot>=B;
}

LL solve(LL R, LL B, LL C, vector<vector<LL>> &A) {
//  LL good=0;
//  REP(i,SZ(A)) SMAX(good,1LL*A[i][0]*A[i][1]+A[i][2]);
  LL good= 1LL<<60;
  LL bad=0;
  while(abs(good-bad)>1) {
    LL mid=(good+bad)/2LL;
    (ok(mid,R,B,C,A)?good:bad)=mid;
  }
  return good;
}

int main() {
  int T;
  cin >> T;
  for(int t = 1; t <= T; ++t) {
    LL R,C,B;
    cin >> R >> B >> C;
    vector<vector<LL>> A(C);
    REP(i,C) {
      LL m,s,p;
      cin >> m >> s >> p;
      A[i]={m,s,p};
    }
    LL res=solve(R,B,C,A);
    cout << "Case #" << t << ": " << res << endl;
  }
  return 0;
}

/*
int res=1e9,R,B,C;
vector<vector<int>> A;
void dfs(int c, int b, VI &cur) {
  if(SZ(cur)==R) {
    if(b!=0) return;
    int a=*max_element(cur.begin(),cur.end());
    SMIN(res,a);
    return;
  }
  FOR(i,c,C) REPE(x,b) {
    int M=A[i][0],S=A[i][1],P=A[i][2];
    if(x>M) continue;
    cur.push_back(S*x+P);
    dfs(i+1,b-x,cur);
    cur.pop_back();
  }
}
// Small set did not pass
int solve_dfs(int RR, int BB, int CC, vector<vector<int>> &AA) {
  res=1e9;
  A=AA;
  R=RR,B=BB,C=CC;
  VI cur={};
  dfs(0,B,cur);
  return res;
}
*/
