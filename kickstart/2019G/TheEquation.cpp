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

// $ cp-batch TheEquation | diff TheEquation.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address TheEquation.cpp && ./a.out

/*
 
 10/19/2019
 
 9:10-9:25 small AC
 20:16-21:20 read editorials and got AC
 
 https://twitter.com/hanseilimak/status/1185760611382087680
 https://codingcompetitions.withgoogle.com/kickstart/round/0000000000050e02/000000000018fe36
 
 */

const int MAX_N=1e3+1;
LL A[MAX_N],M;
int N;

void solve() {
  VI cnt(51,0);
  for(int i=50; i>=0; --i) {
    REP(j,N) cnt[i]+=(A[j]>>i)&1;
  }
//  dumpc(cnt);
  auto f=[&](int i, bool on)->LL {
    LL a=on?(N-cnt[i]):cnt[i];
    return a*(1LL<<i);
  };
  
  LL sum=0,k=0;
  for(int i=50; i>=0; --i) {
    LL x=sum;
    x+=f(i,1);
    for(int j=i-1; j>=0; --j) {
      x+=min(f(j,1),f(j,0));
    }
//    dump(i,x);
    if(x<=M) k|=(1LL<<i),sum+=f(i,1);
    else sum+=f(i,0);
//    dump(i,sum,k);
  }
  if(sum>M) k=-1;
  cout<<k<<endl;
}

void solve_small() {
  LL res=-1;
  REPE(k,1<<7) {
    LL sum=0;
    REP(i,N)sum+=A[i]^k;
    if(sum<=M) res=k;
  }
  cout<<res<<endl;
}

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  int T; cin>>T;
  for(int t=1; t<=T; ++t) {
    cin>>N>>M;
    REP(i,N) cin>>A[i];
    
    cout<<"Case #"<<t<<": ";
    solve();
  }
  return 0;
}
