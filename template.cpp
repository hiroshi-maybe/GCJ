#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef vector < int > VI;
typedef unordered_map < int, int > MAPII;
typedef unordered_set < int > SETI;
typedef pair< int , int > II;
typedef tuple< int, int, int > III;
template<class T> using VV=vector<vector<T>>;
#define FORE(i,a,b) for(int i=(a);i<=(b);++i)
#define REPE(i,n)  for(int i=0;i<=(n);++i)
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())
template<class T> inline T SMIN(T& a, const T b) { return a=(a>b)?b:a; }
template<class T> inline T SMAX(T& a, const T b) { return a=(a<b)?b:a; }
#define ALL(c) (c).begin(),(c).end()
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

// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out < x.in | diff x.out -
const int MAX_N=1e6+1;
LL A[MAX_N];
int N;
void solve() {
}
int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  int T; cin>>T;
  for(int t=1; t<=T; ++t) {
    cin>>N;
    REP(i,N) cin>>A[i];
    
    cout<<"Case #"<<t<<": ";
    solve();
  }
  return 0;
}

// interactive
// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && python testing_tool.py ./a.out
// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && python interactive_runner.py python testing_tool.py 0 -- ./a.out
struct Solve {
public:
  Solve(int A): A(A) {
  }
  int ask(int x) {
    cout<<x<<endl;
    int res; cin>>res;
    if(res==-1) exit(0);
    return res;
  }
  void ans(int x) {
    cout<<x<<endl;
    int verd; cin>>verd;
    assert(verd!=-1);
    exit(0);
  }
private:
  int A;
};
int main_inteactive() {
  int T; scanf("%d", &T);
  for(int t=1; t<=T; ++t) {
    int A; scanf("%d", &A);
    Solve s(A);
    while(true) s.ask(0);
    s.ans(0);
  }
  return 0;
}
