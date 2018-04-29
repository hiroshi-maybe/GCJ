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
 
 4/29/2018
 
 25:00-26:08 1WA
 
 4/30/2018
 
 11:15-11:17 add missing sort and all the test cases passed 😱
 
 */

// iostream
// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out < x.in | diff x.out -
//const int MAX_N=1e5+1;
const int Inf=1e6;

int solve(int N, int L, vector<int> C) {
  vector<II> X;
  set<int> S;
  
  REP(n,N) if((1LL*1000*n/N%10)>=5) {
    S.emplace(n);
  }
  
  LL tot=0;
  REP(i,L) {
    int c=C[i];
    tot+=c;
    auto it=S.lower_bound(c);
    if(it==S.end()) X.emplace_back(Inf,c);
    else if(*it==c) X.emplace_back(Inf,c);
    else {
      X.emplace_back(*it-c,c);
    }
  }
  
  //    REP(i,SZ(X)) dump3(t,X[i].first,X[i].second);
  
  auto it=S.lower_bound(0);
  int gap=(it==S.end()?Inf:*it);
  REP(_,N-tot) X.emplace_back(gap,0);
  
  sort(X.begin(),X.end());
  
  int rem=N-tot;
  REP(i,SZ(X)) {
    int gap=X[i].first;
    if(gap<=rem) {
      X[i].second+=gap;
      rem-=gap;
    }
  }
  if(rem>0) X[SZ(X)-1].second+=rem;
  
  int res=0;
  REP(i,SZ(X)) {
    int a=1LL*X[i].second*100/N,b=(1LL*X[i].second*1000/N%10)>=5;
    res+=a+b;
  }
  return res;
}

int solve2(int N, int L, vector<int> C) {
  return 0;
}

int main() {
  int T;
  cin >> T;
  for(int t = 1; t <= T; ++t) {
    int N,L;
    cin >> N >> L;
    vector<int> C;
    REP(i,L) {
      int c; cin>>c;
      C.push_back(c);
    }
    
    cout << "Case #" << t << ": ";
    cout<< solve(N,L,C);
    cout << endl;
  }
  return 0;
}
