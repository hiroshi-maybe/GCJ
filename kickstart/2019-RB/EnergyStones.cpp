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

// $ cp-batch EnergyStones | diff EnergyStones.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address EnergyStones.cpp && ./a.out < EnergyStones.in | diff EnergyStones.out -

/*
 
 4/20/2019
 
 16:16-16:47 give up
 
 4/24/2019
 
 18:10-19:25 read editorial and got AC
 
 https://codingcompetitions.withgoogle.com/kickstart/round/0000000000050eda/00000000001198c3
 
 # visible test set
 
 We get `0` energy from item `i` = We don't take item `i`
 Fix S which contans taken items.
 What we want to do is minimizing loss from E[i].
 If we take items, larger L[i] gives more loss.
 
 Now we are going to show total order of each item.
 
 ## Antisymmetry: a<=b and b<=a => a=b
 
 If L[i]<=L[j] and L[i]>=L[j], trivially L[i]=L[j] holds.
 
 ## Transitivity: a<=b and b<=c => a<=c
 
 If L[i]<=L[j] and L[j]<=L[k], L[i]<=L[k] holds
 
 ## Connexity: a<=b or b<=a
 
 This is trivially true too.
 
 Thus we can sort by L[i] and do knapsack dp.
 
 # hidden test set

 We can still take subset of items to ignore zero energy.
 This idea frees us from considering E[i] parameter.
 In visible test set, items were sorted by L[i] to minimize loss (larger L[i] was not worse than smaller L[i] to take earlier)
 Now S[i] is not equal. Suppose we take two items `i` and `j`.
 i: E[i],S[i],L[i]
 j: E[j],S[j],L[j]
 
 i) i->j
   profit A=E[i]+E[j]-S[i]*L[j]
 ii) j->i
   profit B=E[j]+E[i]-S[j]*L[i]
 
 profit A - profit B = S[j]*L[i]-S[i]*L[j]
 
 Thus S[j]*L[i]>S[i]*L[j] => (i->j) is strictly better.
 Now we can sort items by comparator S[j]*L[i]>S[i]*L[j]
 
 */

const int MAX_N=200+1;
const int MAX_T=1e4+1;
LL S[MAX_N],E[MAX_N],L[MAX_N];
int N;

const LL Inf=1e18;
LL dp[MAX_N][MAX_T];
void solve() {
  vector<tuple<LL,LL,LL>> X(N);
  REP(i,N) X[i]={L[i],S[i],E[i]};
  sort(ALL(X), [&](tuple<LL,LL,LL> a, tuple<LL,LL,LL> b) {
    LL la,sa; tie(la,sa,ignore)=a;
    LL lb,sb; tie(lb,sb,ignore)=b;
    return sb*la>sa*lb;
  });
  REPE(i,N)REP(t,MAX_T) dp[i][t]=-Inf;
  dp[0][0]=0;
  REP(i,N)REP(t,MAX_T) {
    LL l,s,e; tie(l,s,e)=X[i];
    if(t+s<MAX_T) SMAX(dp[i+1][t+s],dp[i][t]+max(0LL,e-t*l));
    SMAX(dp[i+1][t],dp[i][t]);
  }
  LL res=0;
  REP(t,MAX_T) SMAX(res,dp[N][t]);
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  int T; cin>>T;
  FORE(t,1,T) {
    cin>>N;
    REP(i,N) cin>>S[i]>>E[i]>>L[i];
    cout<<"Case #"<<t<<": ";
    solve();
  }
  
  return 0;
}
