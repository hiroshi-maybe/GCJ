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

// iostream
// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out < x.in | diff x.out -
int solve(int D, string P) {
  return 0;
}
int main() {
  int T;
  cin >> T;
  for(int t = 1; t <= T; ++t) {
    int D; string P;
    cin >> D >> P;
    
    cout << "Case #" << t << ": ";
    cout << solve(D,P);
    cout << endl;
  }
  return 0;
}

// variable length array (stdio)
// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out < x.in | diff x.out -
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
// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && python testing_tool.py ./a.out
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

// standard io in competitive programming
// https://qiita.com/blackcurrant/items/312ea2471900132fbd6a
