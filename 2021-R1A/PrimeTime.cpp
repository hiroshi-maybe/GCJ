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

// $ cp-batch PrimeTime | diff PrimeTime.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address PrimeTime.cpp && ./a.out

/*

 4/9/2021

 19:01-19:17 Test Set 1 AC (7pt)
 19:46 Test Set 2 AC

 4/10/2021

 21:30-23:18 read editorial and got AC

 https://codingcompetitions.withgoogle.com/codejam/round/000000000043585d/00000000007543d8#analysis
 https://kmjp.hatenablog.jp/entry/2021/04/10/0930

 https://twitter.com/chokudai/status/1380726072484929537
 https://twitter.com/yamerarenaku/status/1380726505299271680
 https://twitter.com/camypaper/status/1380726075659939840
 https://twitter.com/semiexp/status/1380725808935755778
 https://twitter.com/laycrs/status/1380724825300168705

 */

const int MAX_N=100;
int P[MAX_N];
LL cnt[MAX_N];
int M;

void solve() {
  LL tot=0;
  REP(i,M) tot+=P[i]*cnt[i];
  LL res=0;
  for(LL s=max(1LL,tot-(LL)3e4); s<=tot; ++s) {
    LL sum=s;
    LL rem=tot-sum;
    if(rem<=0) continue;
    vector<LL> cnts(M);
    int cnttot=0;
    REP(i,M) {
      LL p=P[i];
      while(sum%p==0&&cnttot<=60) {
        cnttot++,sum/=p,cnts[i]++;
      }
    }
    if(sum!=1) continue;

    bool ok=true;
    REP(i,M) {
      if(cnts[i]>cnt[i]) ok=false;
      rem-=(LL)cnts[i]*P[i];
    }
    //dump(s,sum,rem,ok);
    //dumpc(cnts);
    ok&=(rem==0);
    if(ok) SMAX(res,s);
  }
  cout<<res<<endl;
}

bool ith(int mask, int i) { return (mask>>i)&1; }
void solve_s1() {
  VI ps;
  REP(i,M) REP(_,cnt[i]) ps.push_back(P[i]);
  int N=SZ(ps);
  assert(N<=20);
  LL res=0;
  REP(mask, 1<<N) {
    VI s1,s2;
    REP(i,N) {
      (ith(mask,i)?s1:s2).push_back(ps[i]);
    }

    LL maxsum=500*SZ(s1);
    LL prod=1,sum=0;
    REP(i,SZ(s1)) sum+=s1[i];
    FORR(p,s2) {
      prod*=p;
      if(prod>maxsum) break;
    }
    if(sum==prod) SMAX(res,sum);
  }
  cout<<res<<endl;
}

vector<int> sieve(int N) {
  assert(N>=1);
  vector<int> fs(N+1, true);
  fs[0]=fs[1]=false;
  for(long long p=2; p*p<=N; ++p) if(fs[p]) {
    for(long long q=p*p; q<=N; q+=p) fs[q]=false;
  }
  vector<int> res;
  for(int n=2; n<=N; ++n) if(fs[n]) res.push_back(n);
  return res;
}

void solve_s2() {
  const LL Inf=5e4;
  VI maxcnt(M);

  LL tot=0;
  REP(i,M) tot+=P[i]*cnt[i];
  /*
  REP(i,M) {
    LL p=P[i],prod=1;
    REP(_,cnt[i]) {
      prod*=p;
      if(prod>=Inf) break;
      maxcnt[i]++;
    }
  }*/

  LL res=0;
  auto dfs=[&](auto &&self, int i, LL prod, LL sum) {
    if(i==M) {
      if(prod==sum) {
        SMAX(res,sum);
      }
      return;
    }

    //dump(i,P[i],cnt[i],prod,sum);
    self(self,i+1,prod,sum);
    REP(c,cnt[i]) {
      prod*=P[i],sum-=P[i];
      if(prod>=Inf) break;
      self(self,i+1,prod,sum);
    }
  };

  dfs(dfs,0,1,tot);
  cout<<res<<endl;
  //dumpc(maxcnt);
}

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  /*
  VI ps=sieve(500);
  M=SZ(ps);
  REP(i,M) P[i]=ps[i],cnt[i]=100;
  solve();
  return 0;*/

  int T; cin>>T;
  for(int t=1; t<=T; ++t) {
    cin>>M;
    REP(i,M) cin>>P[i]>>cnt[i];

    cout<<"Case #"<<t<<": ";
    solve();
  }
  return 0;
}