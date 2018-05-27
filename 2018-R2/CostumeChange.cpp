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
 
 25:00-25:30 time up
 
 5/27/2018
 
 18:25-19:15 read editorials and add solution for small test cases
 21:20-22:45 add solution for large test case
 
 Editorials:
 - https://codejam.withgoogle.com/2018/challenges/0000000000007706/analysis/0000000000045875
 - http://kmjp.hatenablog.jp/entry/2018/05/25/0900
  - Solution is not bipartite graph. However it's still max flow.
 - http://yosupo.hatenablog.com/entry/2018/05/20/015213
 - https://twitter.com/pes_magic/status/997881858988785664
 
 Tweets:
  - https://togetter.com/li/1229062
  - https://twitter.com/ei1333/status/997878561179516928
  - https://twitter.com/rian_tkb/status/997878385144557569
 
 There are 2*N choices for color. We want to minimize cells to be changed.
 Per each color, we want to take more pairs of (col, row). Also same row or column cannot be used twice.
 Thus it turns out this is max matching (maximum independent set of the graph).
 
 References:
  - https://qiita.com/drken/items/e805e3f514acceb87602
  - https://qiita.com/drken/items/7f98315b56c95a6181a4
 
 Key:
  - We can solve independently per color
  - We want max pair of (row, col) in constraint row or column can be used only once
   - Build bipartite graph with 2*N vertices
   - Graph is composed of N vertices for row and N vertices for column
   - Maximize matching of row and column to minimize cells to be changed
 
 Summary:
  - I never come up with flow 👎
  - First step is reducing to 2*N subproblems per color (or make 4*N graph like @kmjp's solution)
  - Second step is figuring out max independent set from the constraint that row or column is never used twice
 
 */

// iostream
// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out < x.in | diff x.out -
const int MAX_N=101;
int G[MAX_N][MAX_N];
int N;
void solve_small() {
  int res=N*N;
  REP(mask,1<<(N*N)) {
    bool ok=true;
    REP(i,N) {
      SETI S;
      REP(j,N) if(mask&(1<<(i*N+j))) {
        if(S.count(G[i][j])) { ok=false; goto next; }
        S.emplace(G[i][j]);
      }
    }
    REP(j,N) {
      SETI S;
      REP(i,N) if(mask&(1<<(i*N+j))) {
        if(S.count(G[i][j])) { ok=false; goto next; }
        S.emplace(G[i][j]);
      }
    }
  next:
    if(ok) SMIN(res,N*N-__builtin_popcount(mask));
  }
  cout<<res<<endl;
}

const int MAX_V=210;
class MaxBipartiteMatching {
public:
  MaxBipartiteMatching(int V) : V(V) {}
  
  void addEdge(int u, int v) {
    assert(u<V&&v<V);
    E[u].push_back(v);
    E[v].push_back(u);
  }
  
  int solve() {
    int res=0;
    memset(match, -1, sizeof(match));
    for(int u=0; u<V; ++u) if(match[u]<0) {
      memset(viz,0,sizeof viz);
      res+=dfs(u);
    }
    
    return res;
  }
private:
  int V;
  vector<int> E[MAX_V];
  int match[MAX_V];
  bool viz[MAX_V];
  
  // find augmenting path in residual network
  bool dfs(int u) {
    viz[u]=true;
    for(auto v : E[u]) {
      int w=match[v];
      if(w<0||(!viz[w]&&dfs(w))) {
        match[v]=u;
        match[u]=v;
        return true;
      }
    }
    return false;
  }
};

void solve() {
  int res=N*N;
  FORE(c,-N,N) if(c!=0) {
    MaxBipartiteMatching bm(2*N);
    REP(i,N)REP(j,N) if(G[i][j]==c) bm.addEdge(i,N+j);
    res-=bm.solve();
  }
  cout<<res<<endl;
}

int main() {
  int T;
  cin >> T;
  for(int t = 1; t <= T; ++t) {
    cin>>N;
    REP(i,N) REP(j,N) cin>>G[i][j];
    
    cout << "Case #" << t << ": ";
    solve();
  }
  return 0;
}
