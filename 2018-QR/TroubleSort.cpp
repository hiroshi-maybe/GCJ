
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
#define TRACE false
#define dump(x) if(TRACE) { cout << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cout << x << ','; } cout << endl; }

int solve(vector<int> &A) {
  dumpAR(A);
  if(SZ(A)%2==1) A.push_back(1e9+5);
  int N=SZ(A);
  VI X,Y;
  REP(i,N) (i%2==0?X:Y).push_back(A[i]);
  sort(X.begin(),X.end());
  sort(Y.begin(),Y.end());
  
//  dumpAR(X);
//  dumpAR(Y);

  int NN=SZ(X);
  REP(i,NN) {
    if(X[i]>Y[i]) return 2*i;
    if(i<NN-1) if(Y[i]>X[i+1]) return 2*i+1;
  }
  return -1;
}

/*
void tsort(VI &A) {
  bool done=false;
  while(!done) {
    done=true;
    for(int i=0; i<SZ(A)-2; ++i) {
      if(A[i]>A[i+2]) {
        done=false;
        swap(A[i],A[i+2]);
      }
    }
  }
}

bool verify(VI &A) {
  VI AA=A;
  tsort(AA);
  dumpAR(AA);
  int x=-1;
  REP(i,SZ(AA)-1) if(AA[i]>AA[i+1]) {
    x=i;
    break;
  }
  int res=solve(A);
  dump2(res,x);
  return x==res;
}

void test() {
  REP(_,1000) {
    int len=rand()%1000;
    VI A(len);
    generate(A.begin(), A.end(), []() {
      return rand() % (int)(100+1.0);
    });
    bool ok=verify(A);
    if(!ok) dumpAR(A);
    assert(ok);
  }
}*/

// 11:50-12:49 submit
int main() {
//  test();
  int T; scanf("%d", &T);
  for(int t = 1; t <= T; ++t) {
    int N; scanf("%d", &N);
    vector<int> A(N);
    REP(i,N) scanf("%d", &A[i]);
    int res=solve(A);
    if (res==-1) printf("Case #%d: OK\n", t);
    else printf("Case #%d: %d\n", t, res);
  }
  return 0;
}
