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

// standard io in competitive programming
// https://qiita.com/blackcurrant/items/312ea2471900132fbd6a

// iostream
// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG xxxxx.cpp && ./a.out < xxxxx.in
string solve(int D, string P) {
  return "IMPOSSIBLE";
}
int main() {
  int T;
  cin >> T;
  for(int t = 1; t <= T; ++t) {
    int D; string P;
    cin >> D >> P;
    cerr << "Case #" << t << ": " << solve(D,P) << endl;
  }
  return 0;
}

// variable length array (stdio)
// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG xxxxx.cpp && ./a.out < xxxxx.in
int solve_(vector<int> &A) {
  return -1;
}
int main_vector() {
  int T; scanf("%d", &T);
  for(int t = 1; t <= T; ++t) {
    int N; scanf("%d", &N);
    vector<int> A(N);
    REP(i,N) scanf("%d", &A[i]);
    int res=solve_(A);
    if (res==-1) printf("Case #%d: OK\n", t);
    else printf("Case #%d: %d\n", t, res);
  }
  return 0;
}

// interactive (stdio)
// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG xxxxx.cpp && python testing_tool.py ./a.out
struct Solve {
public:
  Solve(int A): A(A) {
  }
  II next() {
    return {-1,-1};
  }
  void fill(int r, int c) {
  }
private:
  int A;
};
int main_inteactive() {
  int T; scanf("%d", &T);
  for(int t = 1; t <= T; ++t) {
    int A; scanf("%d", &A);
    Solve s(A);
    while(true) {
      II p=s.next();
      fprintf(stdout, "%d %d\n", p.first,p.second);
      fflush(stdout);
      int r,c;
      scanf("%d %d", &r, &c);
      assert(r!=-1&&c!=-1);
      if(r==0&&c==0) break;
      s.fill(r,c);
    }
  }
  return 0;
}
