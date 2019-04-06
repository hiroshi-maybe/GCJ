#include <bits/stdc++.h>
using namespace std;
// type alias
typedef long long LL;
typedef pair<int,int> II;
typedef tuple<int,int,int> III;
typedef vector<int> VI;
typedef vector<string> VS;
typedef unordered_map<int,int> MAPII;
typedef unordered_set<int> SETI;
template<class T> using VV=vector<vector<T>>;
// minmax
template<class T> inline T SMIN(T& a, const T b) { return a=(a>b)?b:a; }
template<class T> inline T SMAX(T& a, const T b) { return a=(a<b)?b:a; }
// repetition
#define FORE(i,a,b) for(int i=(a);i<=(b);++i)
#define REPE(i,n)  for(int i=0;i<=(n);++i)
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())
// collection
#define ALL(c) (c).begin(),(c).end()
// DP
#define MINUS(dp) memset(dp, -1, sizeof(dp))
#define ZERO(dp) memset(dp, 0, sizeof(dp))
// stdout
#define println(args...) fprintf(stdout, ##args),putchar('\n');
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

// $ cp-batch YouCanGoYourOwnWay | diff YouCanGoYourOwnWay.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address YouCanGoYourOwnWay.cpp && ./a.out < YouCanGoYourOwnWay.in | diff YouCanGoYourOwnWay.out -

/*
 
 4/6/2019
 
 4:06-4:31, 7:08-7:40 submit
 
 */
string solve(int N, string P) {
  int M=2*N-2;
  int r=0,c=0;
  if(P[0]!=P[M-1]) {
    string es(N-1,'E'),ss(N-1,'S');
    if(P[0]=='E') return ss+es;
    else return es+ss;
  }
  VI scnt(N,0),ecnt(N,0);
  REP(i,2*N-2) {
    if(P[i]=='S') {
      scnt[c]++;
      ++r;
    } else {
      ecnt[r]++;
      ++c;
    }
  }
  if(P[0]=='S') {
    int k=-1;
    REP(j,N) if(scnt[j]==0) {
      k=j;
      break;
    }
    assert(k!=-1);
    string es1(k,'E'),ss(N-1,'S'),es2(N-k-1,'E');
    return es1+ss+es2;
  } else {
    int k=-1;
    REP(i,N) if(ecnt[i]==0) {
      k=i;
      break;
    }
    assert(k!=-1);
    string ss1(k,'S'),es(N-1,'E'),ss2(N-k-1,'S');
    return ss1+es+ss2;
  }
}
int main() {
  int T;
  cin >> T;
  for(int t = 1; t <= T; ++t) {
    int N; string P; cin>>N>>P;
    
    cout << "Case #" << t << ": ";
    cout << solve(N,P);
    cout << endl;
  }
  return 0;
}
