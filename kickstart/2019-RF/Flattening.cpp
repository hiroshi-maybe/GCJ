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

// $ cp-batch Flattening | diff Flattening.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Flattening.cpp && ./a.out

/*
 
 9/29/2019
 
 11:02-11:50 TLE
 
 10/1/2019
 
 21:00-23:00 read editorial and got AC
 
 https://codingcompetitions.withgoogle.com/kickstart/round/0000000000050edc/000000000018666c
 
 I was confused about two conditions when making recurrence relation especially in base case.
 Every time we put right boundary, we can assume that A[r]!=A[r+1].
 This is not quite true though, we can eventually get right answer.
 
 111121 (Assuming A[r]!=A[r+1]. However that's not true)
   ^
 
 111121 (This boundary eventually covers optimal solution)
    ^
 
 Recurrence relation is guarateeing A[i]!=A[i+1] happens at most K.
 We can try all possible equal intervals by dp.
  
 */

const int MAX_N=1e2+1;
const int Inf=1e3;
int A[MAX_N];
int N,K;

int memo2[MAX_N][MAX_N];
int g(int l, int r) {
  if(l==r) return 0;
  if(r==l+1) return 0;
  int &res=memo2[l][r];
  if(res>=0) return res;
  map<int,int> cnt;
  int maxcnt=0;
  FOR(i,l,r) cnt[A[i]]++,SMAX(maxcnt,cnt[A[i]]);
  res=r-l-maxcnt;
//  dump(l,r,res);
  return res;
}

int memo[MAX_N][MAX_N];
int f(int r, int k) {
  if(r==0) return 0;
  if(k==0) return g(0,r);
  int &res=memo[r][k];
  if(res>=0) return res;
  res=Inf;
  REP(i,r) {
    int a=f(i,k-1),b=g(i,r);
    SMIN(res,a+b);
  }
//  dump(r,k,res);
  return res;
}

void solve() {
  MINUS(memo),MINUS(memo2);
  int res=f(N,K);
  cout<<res<<endl;
}

int ff(int l, int r) {
  if(l==r) return 0;
  map<int,int> cnt;
  FOR(i,l,r) cnt[A[i]]++;
  int maxcnt=0,maxkey=-1;
  FORR(kvp,cnt) if(kvp.second>maxcnt) {
    maxkey=kvp.first,maxcnt=kvp.second;
  }
  int res=0;
  FORR(kvp,cnt)if(kvp.first!=maxkey) res+=kvp.second;
  return res;
}
int res;
void dfs(int i, int k, VI &cur) {
  if(k==0||i==N) {
    cur.push_back(N);
    int l=0,ans=0;
    FORR(r,cur) {
      ans+=ff(l,r);
      l=r;
    }
    cur.pop_back();
//    dumpc(cur);
//    dump(ans);
    SMIN(res,ans);
    return;
  }
  cur.push_back(i+1);
  dfs(i+1,k-1,cur);
  cur.pop_back();
  dfs(i+1,k,cur);
}

void solve_tle() {
  res=Inf;
  VI cur;
  dfs(0,K,cur);
  cout<<res<<endl;
}

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  int T; cin>>T;
  for(int t=1; t<=T; ++t) {
    cin>>N>>K;
    REP(i,N) cin>>A[i];
    
    cout<<"Case #"<<t<<": ";
    solve();
  }
  return 0;
}
