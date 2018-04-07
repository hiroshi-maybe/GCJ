
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
// debug cout
#define TRACE true
#define dump(x) if(TRACE) { cerr << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }

struct Solve {
public:
  Solve(int A) {
    this->R=(A+2)/3;
    ZERO(viz);
//    dump2(A,R);
  }
  II next() {
    ++cnt;
    return {i,2};
  }
  void fill(int r, int c) {
    assert(r>=1&&c>=1);
    viz[r][c]=true;
    while(i<R&&ok(i-1)) ++i;
//    show();
  }
  void show() {
    REP(j,4) {
      REPE(i,R) cout << (viz[i][j]?'#':'.');
      cout <<endl;
    }
  }
  int cnt=0,i=2,R;
private:
  bool viz[80][4];
  bool ok(int i) {
    return viz[i][1]&&viz[i][2]&&viz[i][3];
  }
};

// g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG GoGopher.cpp && python test_GoGopher.py ./a.out
// 13:30-15:00 submit
int main() {
  int T; scanf("%d", &T);
  for(int t = 1; t <= T; ++t) {
    int A; scanf("%d", &A);
//    fprintf (stderr, "%d is given\n", A);
    Solve s(A);
    while(true) {
      II p=s.next();
//      fprintf (stderr, "%d, %d\n", p.first,p.second);
      fprintf(stdout, "%d %d\n", p.first,p.second);
      fflush(stdout);
      int r,c;
      scanf("%d %d", &r, &c);
//      cin >> r >> c;
      assert(r!=-1&&c!=-1);
      if(r==0&&c==0) break;
      s.fill(r,c);
    }
//    fprintf (stderr, "%d tries\n", s.cnt);
  }
  return 0;
}
