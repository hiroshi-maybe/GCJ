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
 
 18:59-19:40 AC
 
 Editorials:
  - https://codejam.withgoogle.com/2018/challenges/0000000000007765/analysis/000000000003e068
  - http://kmjp.hatenablog.jp/entry/2018/05/06/0930
  - http://memo.sugyan.com/entry/2018/05/06/205751
  - http://kazune-lab.net/contest/2018/05/05/gcj2018round1c/
 
 Tweets:
  - https://twitter.com/_olphe/status/992731837003841536
  - https://twitter.com/noss46/status/992730589034770434
  - https://twitter.com/dfnPer/status/992730509481410560
  - https://twitter.com/butsurizuki/status/992728136117727233
 
 Summary:
  - Flavor which showed up more is more likely to be preferred. Just avoid it
 
 */

// interactive (stdio)
// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && python testing_tool.py ./a.out
struct Solve {
public:
  Solve(int N): N(N) {
    viz=vector<int>(N,0);
    F=vector<int>(N,0);
  }
  int next(int D, vector<int> P) {
//    dumpAR(P);
    REP(i,D) F[P[i]]++;
    vector<II> X;
    FORR(p,P) if(viz[p]==0) {
      X.emplace_back(F[p],p);
    }
    if(X.empty()) return -1;
    sort(X.begin(),X.end());
    viz[X.front().second]=1;
    return X.front().second;
  }
private:
  vector<int> F;
  vector<int> viz;
  int N;
};
int main() {
  int T; scanf("%d", &T);
  for(int t = 1; t <= T; ++t) {
    int N; scanf("%d", &N);
    Solve s(N);
    REP(_,N) {
      int D;
      scanf("%d", &D);
      // error
      if(D==-1) return 1;
      vector<int> P(D);
      REP(i,D) scanf("%d", &P[i]);
      int p=s.next(D,P);
      fprintf(stdout, "%d\n", p);
      fflush(stdout);
    }
  }
  return 0;
}
