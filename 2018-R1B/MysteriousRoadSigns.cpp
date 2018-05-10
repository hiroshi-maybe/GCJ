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
int tt;
#define TRACE true
#define dump(x) if(TRACE&&tt==6) { cerr << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE&&tt==6) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE&&tt==6) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE&&tt==6) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE&&tt==6) { FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }

int genRandNum(int lb, int ub) {
  // Helper to generate random integer in range [lb, ub)
  int x = rand() % (int)(ub - lb);
  return x + lb;
}
vector<int> genRandSeq(int size, int lb, int ub) {
  if (size==0) return {};
  vector<int> res(size);
  generate(res.begin(), res.end(), [&]() {
    return genRandNum(lb, ub);
  });
  return res;
}

/*
 
 4/29/2018
 
 26:30-27:30 time up
 
 4/30/2018
 
 19:10-20:12 submit but WA
 20:13-20:33 bug fix, but 2WA
 
 22:00-23:33 copy editorial solution, fix a bug and add solution for small
 23:34-24:20 pause for large
 
 Editorials:
  - https://codejam.withgoogle.com/2018/challenges/0000000000007764/analysis/000000000003675b
  - http://naoyat.hatenablog.jp/entry/GCJ2018R1B
 
 Tweets:
  - https://togetter.com/li/1222764
 
 Summary:
  - I completely forgot MMMNNMMM case 👎👎👎👎👎👎👎
   - MMMNNN is not sufficient
  - swap technique to avoid copy&paste is cool
 
 */

// iostream
// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out < x.in | diff x.out -
//const int MAX_N=1e5+1;
const int Inf=1e6;
II solve_wrong(int S, VI &D, VI &A, VI &B) {
  vector<II> X1,X2;
  vector<int> P(S,-1);
  
  int l=0;
  REPE(r,S) {
    if(r==S||D[r]+A[r]!=D[l]+A[l]) {
      X1.emplace_back(l,r);
      l=r;
    }
  }
  l=0;
  REPE(r,S) {
    if(r==S||D[r]-B[r]!=D[l]-B[l]) {
      FOR(i,l,r) P[i]=SZ(X2);
      X2.emplace_back(l,r);
      l=r;
    }
  }
  
  sort(X1.begin(),X1.end());

  dumpAR(P);
  if(tt==2)REP(i,SZ(X2)) dump3(i,X2[i].first,X2[i].second);

  set<II> MN;
  int maxlen=-1;
  REP(i,SZ(X1)) {
    int l=X1[i].first,r=X1[i].second;
//    dump3(i,l,r);
    
    // right
    II p=make_pair(S,S);
    if(r!=S) {
      int x=P[r];
      if(x<SZ(X2)) p=X2[x];
    }
    int len1=p.second-l;
    if(maxlen==len1) MN.emplace(l,p.second);
    if(maxlen<len1) {
      MN.clear();
      MN.emplace(l,p.second);
      maxlen=len1;
    }
    
    if(tt==2&&len1==5) {
      dump2(P[r],P[r-1]);
      dump4(l,r,p.first,p.second);
    }
    
    // left
    p=make_pair(0,0);
    if(l!=0) {
      int x=P[l-1];
      if(x<SZ(X2)) p=X2[x];
    }
    int len2=r-p.first;

    if(tt==2&&len2==5) dump3(p.first,r,SZ(MN));
    
    if(maxlen==len2) MN.emplace(p.first,r);
    if(maxlen<len2) {
      MN.clear();
      MN.emplace(p.first,r);
      maxlen=len2;
    }
  }

  return {maxlen,SZ(MN)};
}

II solve(int S, VI &D, VI &A, VI &B) {
  VI M(S),N(S);
  REP(i,S) M[i]=D[i]+A[i],N[i]=D[i]-B[i];
  
  dumpAR(M);
  dumpAR(N);
  
  set<II> MN;
  int maxlen=-1;
  
  REP(_,2) {
  
    vector<II> X1,X2;
    vector<int> P(S,-1);
    
    int l=0;
    REPE(r,S) {
      if(r==S||M[r]!=M[l]) {
        X1.emplace_back(l,r);
        l=r;
      }
    }
    l=0;
    REPE(r,S) {
      if(r==S||N[r]!=N[l]) {
        FOR(i,l,r) P[i]=SZ(X2);
        X2.emplace_back(l,r);
        l=r;
      }
    }
    
    sort(X1.begin(),X1.end());
    
  //  dumpAR(P);
  //  if(tt==2)REP(i,SZ(X2)) dump3(i,X2[i].first,X2[i].second);
    
    auto update = [&](int l, int r) {
      int len=r-l;
      if(maxlen==len) MN.emplace(l,r);
      if(maxlen<len) {
        MN.clear();
        MN.emplace(l,r);
        maxlen=len;
      }
    };
    
    REP(i,SZ(X1)) {
      int l=X1[i].first,r=X1[i].second;
      //    dump3(i,l,r);
      
      // right
      II p1=make_pair(Inf,Inf);
      if(r!=S) {
        int x=P[r];
        if(x<SZ(X2)) p1=X2[x];
      }
      // left
      II p2=make_pair(Inf,Inf);
      if(l!=0) {
        int x=P[l-1];
        if(x<SZ(X2)) p2=X2[x];
      }
      
      /*
      if(tt==4&&i==1) {
        dump2(N[l-1],N[r]);
        dump4(p1.first,p1.second,p2.first,p2.second);
      }*/
      
      if(p1.first==Inf&&p2.first==Inf) update(l,r);
      else if(p1.first==Inf) update(p2.first,r);
      else if(p2.first==Inf) update(l,p1.second);
      else {
        if(N[r]==N[l-1]) update(p2.first,p1.second);
        else {
          update(l,p1.second);
          update(p2.first,r);
        }
      }
    }
    
    swap(M,N);
  }
    
  return {maxlen,SZ(MN)};
}

II solve2(int S, VI &D, VI &A, VI &B) {
  VI M(S),N(S);
  REP(i,S) M[i]=D[i]+A[i],N[i]=D[i]-B[i];
  
  set<II> R; int maxlen=-1;
  REP(r,S) REPE(l,r) REP(_,2) {
    int m=M[l],n;
    FORE(i,l,r) if(M[i]!=m) n=N[i];
    
    bool ok=true;
    FORE(i,l,r) if(M[i]!=m&&N[i]!=n) ok=false;
    if(ok) {
      if(maxlen<r-l+1) maxlen=r-l+1,R.clear(),R.emplace(l,r);
      else if(maxlen==r-l+1) R.emplace(l,r);
    }
    
    swap(M,N);
  }
  
//  FORR(r,R) dump3(tt,r.first,r.second);
  
  return {maxlen,SZ(R)};
}

II solve3(int S, VI &D, VI &A, VI &B) {
  VI M(S),N(S);
  REP(i,S) M[i]=D[i]+A[i],N[i]=D[i]-B[i];
  SETI MM(M.begin(),M.end()),NN(N.begin(),N.end());
  
//  if(tt==2)dumpAR(MM);
//  if(tt==2)dumpAR(NN);
  
  set<int> X[S+1];
  FORR(m,MM)FORR(n,NN) {
    int cnt=0;
    REP(i,S) {
      if(M[i]==m||N[i]==n) ++cnt;
      else X[cnt].emplace(i),cnt=0;
    }
    X[cnt].emplace(S);
  }
  
//  dumpAR(X);
  
  int maxlen=-1;
  REPE(l,S) if(SZ(X[l])) maxlen=l;
  
  return {maxlen,SZ(X[maxlen])};
}

int main() {
  int T;
  cin >> T;
  for(int t = 1; t <= T; ++t) {
    
    tt=t;
    
    int S;
    cin >> S;
    vector<int> D,A,B;
    REP(i,S) {
      int d,a,b; cin>>d>>a>>b;
      D.push_back(d);
      A.push_back(a);
      B.push_back(b);
    }
    
    cout << "Case #" << t << ": ";
    II res=solve(S,D,A,B);
    cout << res.first<<" "<<res.second;
    cout << endl;
  }

  /*
  int SS;
  VI DD,AA,BB;
  while(true) {
    SS=genRandNum(1,10);
    DD=genRandSeq(SS,1,100);
    AA=genRandSeq(SS,1,100);
    BB=genRandSeq(SS,1,100);

    II x=solve(SS,DD,AA,BB),y=solve2(SS,DD,AA,BB);
    if(x!=y) {
      dump4(x.first,x.second,y.first,y.second);
      dump(SS);
      REP(i,SS) printf("%d %d %d\n",DD[i],AA[i],BB[i]);
//
//      dumpAR(DD);
//      dumpAR(AA);
//      dumpAR(BB);
      break;
    }
  }*/
  
  return 0;
}
