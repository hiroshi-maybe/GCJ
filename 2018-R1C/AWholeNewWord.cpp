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
 
 18:25-18:58 small and large passed
 
 Editorials:
  - official:
   - https://codejam.withgoogle.com/2018/challenges/0000000000007765/analysis/000000000003e064
  - brute-force
   - http://ferin-tech.hatenablog.com/entry/2018/05/05/224622
   - http://kmjp.hatenablog.jp/entry/2018/05/06/0900
   - http://memo.sugyan.com/entry/2018/05/06/205751
 
 Tweets:
  - https://togetter.com/li/1224542
  - Randomize
   - https://twitter.com/butsurizuki/status/992728136117727233
  - Brute-force
   - https://twitter.com/_olphe/status/992731837003841536
    - Same as official editorial. Before checking 26^L word, (N+1)-th word should be valid result.
   - https://twitter.com/ferin_tech15/status/992728812767997952
   - https://twitter.com/dfnPer/status/992730509481410560
   - https://twitter.com/noss46/status/992730589034770434
   - https://twitter.com/JP3BGY/status/992733407795793921
 
 5/7/2018 Add brute-force solution
 
 Summary:
  - solved by randomization without specific proof
  - it's informative that computation of brute-force is upper-bounded by 2000
 
 */

// iostream
// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out < x.in | diff x.out -
const int MAX_N=2001;
string B[MAX_N];
int N,L;
int genRandNum(int lb, int ub) {
  // Helper to generate random integer in range [lb, ub)
  int x = rand() % (int)(ub - lb);
  return x + lb;
}
string solve_org() {
  vector<SETI> S(L);
  REP(i,L) REP(j,N) S[i].emplace(B[j][i]-'A');
  vector<vector<int>> SS(L);
  REP(i,L) SS[i]=vector<int>(S[i].begin(),S[i].end());
  /*
  vector<int> X;
  REP(i,L) X.emplace(SZ(SS[i]));
  sort(X.begin(),X.end());
  if(L==1||X[L-2]==1) return "-";
   */
  LL tot=1LL;
  REP(i,L) tot*=SZ(SS[i]);
  if(N==tot) return "-";
  
  unordered_set<string> WS;
  REP(i,N) WS.emplace(B[i]);
  
  while(true) {
    string x="";
    REP(i,L) {
      int j=genRandNum(0,SZ(SS[i]));
      char c='A'+SS[i][j];
      x+=c;
    }
    if(WS.count(x)==0) return x;
  }
  
  return "-";
}

vector<vector<int>> SS;
unordered_set<string> WS;
string res="-";
bool dfs(int i, string &cur) {
  if(i==L) {
    if(WS.count(cur)==0) {
      res=cur;
      return true;
    }
    return false;
  }
  
  FORR(ci,SS[i]) {
    char c='A'+ci;
    cur.push_back(c);
    if(dfs(i+1,cur)) return true;
    cur.pop_back();
  }
  return false;
}

string solve() {
  vector<SETI> S(L);
  REP(i,L) REP(j,N) S[i].emplace(B[j][i]-'A');
  REP(i,L) SS.emplace_back(vector<int>(S[i].begin(),S[i].end()));
  
  LL tot=1LL;
  REP(i,L) tot*=SZ(SS[i]);
  if(N==tot) return "-";
  
  REP(i,N) WS.emplace(B[i]);
  
  string e="";
  dfs(0,e);
  
  return res;
}

int main() {
  int T;
  cin >> T;
  for(int t = 1; t <= T; ++t) {
    SS.clear(); WS.clear();
    cin >>N>>L;
    REP(i,N) cin>>B[i];
    
    cout << "Case #" << t << ": ";
    cout << solve();
    cout << endl;
  }
  return 0;
}
