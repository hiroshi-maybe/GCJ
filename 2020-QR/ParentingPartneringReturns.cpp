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

// $ cp-batch ParentingPartneringReturns | diff ParentingPartneringReturns.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address ParentingPartneringReturns.cpp && ./a.out

/*
 
 4/4/2020
 
 14:24-14:43 AC
 
 https://codingcompetitions.withgoogle.com/codejam/round/000000000019fd27/000000000020bdf9
 
 */

const int MAX_N=1e3+1;
int N;
II A[MAX_N];

void solve() {
  VV<II> X(24*60+10);
  REP(i,N) {
    int l,r; tie(l,r)=A[i];
    X[l].emplace_back(1,i),X[r].emplace_back(0,i);
  }
  REP(i,SZ(X)) sort(ALL(X[i]));
  string res(N,'?');
  queue<char> Q; Q.emplace('C'),Q.emplace('J');
  FORR(x,X) FORR(p,x) {
    int start,i; tie(start,i)=p;
    if(start) {
      if(Q.empty()) {
        cout<<"IMPOSSIBLE"<<endl;
        return;
      }
      char c=Q.front(); Q.pop();
      res[i]=c;
    } else {
      Q.emplace(res[i]);
    }
  }
  assert(count(ALL(res),'?')==0);
  cout<<res<<endl;
}

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  int T; cin>>T;
  for(int t=1; t<=T; ++t) {
    cin>>N;
    REP(i,N) {
      int l,r; cin>>l>>r;
      A[i]={l,r};
    }
    
    cout<<"Case #"<<t<<": ";
    solve();
  }
  return 0;
}
