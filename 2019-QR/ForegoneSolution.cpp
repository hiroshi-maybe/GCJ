#include <bits/stdc++.h>
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
#define ALL(c) (c).begin(),(c).end()
// DP
#define MINUS(dp) memset(dp, -1, sizeof(dp))
#define ZERO(dp) memset(dp, 0, sizeof(dp))
// minmax
#define SMAX(a,b) a = max(a,b)
#define SMIN(a,b) a = min(a,b)
// debug cerr
template<class Iter> void __kumaerrc(Iter begin, Iter end) { for(; begin!=end; ++begin) { cerr<<*begin<<','; } cerr<<endl; }
void __kumaerr(istream_iterator<string> it) { (void)it; cerr<<endl; }
template<typename T, typename... Args> void __kumaerr(istream_iterator<string> it, T a, Args... args) { cerr<<*it<<"="<<a<<", ",__kumaerr(++it, args...); }
template<typename S, typename T> std::ostream& operator<<(std::ostream& _os, const std::pair<S,T>& _p) { return _os<<"{"<<_p.first<<','<<_p.second<<"}"; }
#define __KUMATRACE__ true
#ifdef __KUMATRACE__
#define dump(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); __kumaerr(_it, args); }
#define dumpc(ar) { cerr<<#ar<<": "; FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }
#define dumpC(beg,end) { cerr<<"~"<<#end<<": "; __kumaerrc(beg,end); }
#else
#define dump(args...)
#define dumpc(ar)
#define dumpC(beg,end)
#endif

/*
 
 4/6/2019
 
 3:40-4:00 got AC on test set 1&2
 
 */

// iostream
// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG ForegoneSolution.cpp && ./a.out < ForegoneSolution.in | diff ForegoneSolution.out -

void check(string X, string Y, string S) {
  reverse(ALL(X)),reverse(ALL(Y));
  assert(SZ(X)==SZ(S));
  int N=SZ(S);
  string T(N,'?');
  int car=0;
  REP(i,N) {
    int x=X[i]-'0',y=0;
    if(i<SZ(Y)) y=Y[i]-'0';
    T[i]='0'+(x+y+car)%10;
    car=(x+y+car)/10;
  }
//  dump(S,T);
  assert(S==T);
}

void solve(string S) {
  reverse(ALL(S));
  int N=SZ(S);
  string A,B;
  REP(i,N) {
    int a=0,b=0;
    if(S[i]=='4') a=1,b=3;
    else a=S[i]-'0';
    A.push_back('0'+a),B.push_back('0'+b);
  }
  while(SZ(B)&&B.back()=='0') B.pop_back();
  reverse(ALL(A)),reverse(ALL(B));
//  dump(A,B);
  check(A,B,S);
  cout<<A<<" "<<B;
}

int main() {
  int T;
  cin >> T;
  for(int t = 1; t <= T; ++t) {
    string S;
    cin>>S;
    
    cout << "Case #" << t << ": ";
    solve(S);
    cout << endl;
  }
  return 0;
}
