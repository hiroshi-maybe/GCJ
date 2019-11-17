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

// $ cp-batch SpectatingVillages | diff SpectatingVillages.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address SpectatingVillages.cpp && ./a.out

/*
 
 9/29/2019
 
 12:15-13:57 WA
 
 10/5/2019
 
 21:30-22:50 read analysis and got AC
 
 My original code had a bug to count child's score twice :(
 
 https://codingcompetitions.withgoogle.com/kickstart/round/0000000000050edc/000000000018666b
 https://twitter.com/hanseilimak/status/1180723579421249537
 
 */

const int MAX_N=1e5+1;
LL A[MAX_N];
VI G[MAX_N];
int N;

const LL Inf=1e13;

LL memo[MAX_N][2][2];
int viz[MAX_N][2][2];
LL f(int u, int pon, int on, int pre) {
  if(viz[u][pon][on]) return memo[u][pon][on];
  LL &res=memo[u][pon][on];
  viz[u][pon][on]=1;
  VI B;
  FORR(v,G[u]) if(v!=pre) B.push_back(v);
  int M=SZ(B);
  vector<vector<LL>> dp(M+1,vector<LL>(2,-Inf));
  dp[0][0]=0;
  REP(i,M)REP(j,2) {
    int v=B[i];
    // on
    SMAX(dp[i+1][1],dp[i][j]+f(v,on,1,u));
    // off
    SMAX(dp[i+1][j],dp[i][j]+f(v,on,0,u));
  }

  REP(i,2) SMAX(res,dp[M][i]+((i|on|pon)?A[u]:0));
//  dump(u,pon,on,dp[M][0],dp[M][1],res);
  return res;
}

void solve() {
  ZERO(viz);
  REP(i,N)REP(j,2)REP(k,2) memo[i][j][k]=-Inf;
  LL res=0;
  res=max({res,f(0,0,0,-1),f(0,0,1,-1)});
  cout<<res<<endl;
}

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  int T; cin>>T;
  for(int t=1; t<=T; ++t) {
    cin>>N;
    REP(i,N) cin>>A[i];
    REP(i,N-1) {
      int u,v; cin>>u>>v;
      --u,--v;
      G[u].push_back(v),G[v].push_back(u);
    }
    
    cout<<"Case #"<<t<<": ";
    solve();
    REP(i,N) G[i].clear();
  }
  return 0;
}
