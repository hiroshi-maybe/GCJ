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
 
 4/19/2018 GCJ 2018 R1A
 
 18:00-20:04 Small: AC, Large: AC
 
 Editorials:
  - articles
   - https://codejam.withgoogle.com/2018/challenges/0000000000007883/analysis/000000000003005a
   - http://kmjp.hatenablog.jp/entry/2018/04/22/0900
   - http://div9851.hatenadiary.com/entry/2018/04/14/132959
   - https://pitsbuffersolution.com/blog/articles/gcj2018_round1a.php
   - https://amalog.hateblo.jp/entry/gcj-2018-round1a
  - twitter comments
   - https://twitter.com/tanakh/status/985000551405445122
   - https://twitter.com/kusano_k/status/985000583160459264
   - https://twitter.com/nico_shindannin/status/985010096148103168
   - https://twitter.com/rickytheta/status/984998732214091776
   - https://twitter.com/beet_aizu/status/984997569456521217
   - https://twitter.com/pazzle1230/status/984997329961811968
   - https://twitter.com/koyumeishi_/status/984999854077231104
 
 Summary:
  - Wasted more than 1 hour due to template bug during the contest 👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎
 
 */

struct TwoDimCumSum {
public:
  int R,C;
  TwoDimCumSum(vector<vector<int>> &X) {
    this->R=X.size();
    if(R==0) return;
    this->C=X[0].size();
    this->cum=vector<vector<int>>(R+1,vector<int>(C+1,0));
    
    for(int i=0; i<R; ++i) for(int j=0; j<C; ++j) {
      cum[i+1][j+1]=cum[i][j+1]+cum[i+1][j]-cum[i][j]+X[i][j];
    }
  }
  // query of sum in rectangle r in [i1,i2), c in [j1,j2)
  int query(int i1, int j1, int i2, int j2) {
    return cum[i2][j2]-cum[i1][j2]-cum[i2][j1]+cum[i1][j1];
  }
private:
  vector<vector<int>> cum;
};

// iostream
// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG xxxxx.cpp && ./a.out < xxxxx.in
bool solve(int R, int C, int H, int V, vector<vector<int>> &G) {
  int sum=0;
  REP(i,R)REP(j,C) sum+=G[i][j];
  ++H,++V;
  if(sum==0) return true;
  if(sum%(H*V)!=0) return false;
  
//  dump3(sum,H,V);
  
  bool ok1=true;
  VI X(R,0);
  REP(i,R) X[i]=count(G[i].begin(),G[i].end(),true);
  int cur=0,T=sum/H,cnt=0;
  VI rs(1,0);
  REP(i,R) {
    cur+=X[i];
    if(cur<T) continue;
    if(cur==T) cur=0,cnt+=1,rs.push_back(i+1);
    if(cur>T) { ok1=false; break; }
  }
//  if(cur>0) ok1&=(cur==T),rs.push_back(R+1);
  ok1&=cnt==H;
  
  bool ok2=true;
  VI Y(C,0);
  REP(j,C) REP(i,R) Y[j]+=G[i][j];
  cur=0,T=sum/V,cnt=0;
  VI cs(1,0);
  REP(j,C) {
    cur+=Y[j];
    if(cur<T) continue;
    if(cur==T) cur=0,cnt+=1,cs.push_back(j+1);
    if(cur>T) { ok2=false; break; }
  }
//  if(cur>0) ok2&=(cur==T),cs.push_back(C+1);
  ok2&=cnt==V;
  if ((!ok1)||(!ok2)) return false;
  
//  dump3(ok1,ok2,ok1&&ok2);
  int A=sum/(H*V);
  TwoDimCumSum cum(G);
//  dump4(SZ(rs),H,SZ(cs),V);
  assert(SZ(rs)==H+1&&SZ(cs)==V+1);
  bool ok=true;
  REP(i,H) REP(j,V) ok&=(cum.query(rs[i],cs[j],rs[i+1],cs[j+1])==A);
  return ok;
}

int count(int i1, int j1, int i2, int j2, vector<vector<int>> &G) {
  int res=0;
  FOR(i,i1,i2)FOR(j,j1,j2) res+=G[i][j];
  return res;
}

bool solve_(int R, int C, int H, int V, vector<vector<int>> &G) {
  int sum=0;
  REP(i,R)REP(j,C) sum+=G[i][j];
  ++H,++V;
  //if(sum==0) return true;
  if((sum%(H*V))!=0) return false;
  int A=sum/(H*V);
  TwoDimCumSum cum(G);
  
  REP(i,R) dumpAR(G[i]);
  
  bool ok=false;
  REP(i,R) REP(j,C) {
    if(count(0,0,i,j,G)==A&&count(0,j,i,C,G)==A&&count(i,0,R,j,G)==A&&count(i,j,R,C,G)==A) {
//      dump2(i,j);
      ok=true;
    }
  }
  return ok;
}

// 18:00-20:04
int main() {
  int T;
  cin >> T;
  for(int t = 1; t <= T; ++t) {
    int R,C,H,V;
    cin >> R >> C >> H >> V;
    vector<vector<int>> G(R);
    REP(i,R) {
      string x;
      cin >> x;
      REP(j,C) G[i].push_back(x[j]=='@');
    }
    string res=solve(R,C,H,V,G)?"POSSIBLE":"IMPOSSIBLE";
    cout << "Case #" << t << ": " << res << endl;
  }
  return 0;
}
