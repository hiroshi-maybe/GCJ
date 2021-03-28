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

// $ cp-batch MoonsAndUmbrellas | diff MoonsAndUmbrellas.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address MoonsAndUmbrellas.cpp && ./a.out

/*

 3/26/2021

 16:47-17:18, 20:10-20:27 AC

 https://codingcompetitions.withgoogle.com/codejam/round/000000000043580a/00000000006d12d7
 https://kmjp.hatenablog.jp/entry/2021/03/28/0930

 */

const LL Inf=1e17;
string S;
LL X,Y;

void solve() {
  int N=SZ(S);
  VV<LL> dp(N+1,vector<LL>(2,Inf));
  if(S[0]=='?') dp[0][0]=dp[0][1]=0;
  if(S[0]=='C') dp[0][0]=0;
  if(S[0]=='J') dp[0][1]=0;
  REP(i,N-1)REP(j,2) {
    if(S[i+1]=='C') {
      SMIN(dp[i+1][0], dp[i][j]+(j==1?Y:0));
    }
    if(S[i+1]=='J') {
      SMIN(dp[i+1][1], dp[i][j]+(j==0?X:0));
    }
    if(S[i+1]=='?') REP(k,2) {
      if(j==k) SMIN(dp[i+1][k], dp[i][j]);
      else if(k==1) SMIN(dp[i+1][k],dp[i][j]+X);
      else SMIN(dp[i+1][k],dp[i][j]+Y);
    }
    //dump(i,j,dp[i][j]);
  }
  cout<<min(dp[N-1][0],dp[N-1][1])<<endl;
}

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  int T; cin>>T;
  for(int t=1; t<=T; ++t) {
    cin>>X>>Y>>S;

    cout<<"Case #"<<t<<": ";
    solve();
  }
  return 0;
}
