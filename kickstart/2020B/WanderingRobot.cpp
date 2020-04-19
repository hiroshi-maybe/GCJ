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
//#define __KUMATRACE__ true
#ifdef __KUMATRACE__
#define dump(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); __kumaerr(_it, args); }
#define dumpc(ar) { cerr<<#ar<<": "; FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }
#define dumpC(beg,end) { cerr<<"~"<<#end<<": "; __kumaerrc(beg,end); }
#else
#define dump(args...)
#define dumpc(ar)
#define dumpC(beg,end)
#endif

long double chooseLog2(int n, int k) {
  assert(n>=k);
  const int MAX_N = 1e6+1;
  assert(0<=k&&k<=MAX_N);
  static vector<long double> fact(MAX_N+1,-1);
  
  if(fact[1]<0) {
    fact[0]=fact[1]=0;
    for(int i=2;i<=MAX_N;i++) fact[i]=fact[i-1]+log2(i);
  }
  return fact[n]-fact[n-k]-fact[k];
}

// $ cp-batch WanderingRobot | diff WanderingRobot.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address WanderingRobot.cpp && ./a.out

/*
 
 4/18/2020
 
 16:48-18:31 WA
 19:50 give up
 
 4/19/2020
 
 14:00-14:55 WA
 15:30-16:30 read editorial and got AC
 
 https://codingcompetitions.withgoogle.com/kickstart/round/000000000019ffc8/00000000002d8565
 https://docs.google.com/document/d/1Yq384PEooRVsmlzB103YMLWwE_JhPN8AbxZagNrF_vY/edit#bookmark=id.m6h6ds25wb38
 
 */

int W,H,L,U,R,D;

long double ff(int r, int c) {
  long double ch=chooseLog2(r+c,r);
  return ch-(r+c);
}
long double solve() {
  dump(W,H,L,U,R,D);
  long double sum1=0,sum2=0;
  if(R<W) REP(i,U) {
    int j=U+R-1-i;
    auto p=pow(2.0,ff(i,j));
    dump(i,j,p);
    sum1+=p;
  }
  if(D<H) REP(j,L) sum2+=pow(2.0,ff(D+L-1-j,j));
  dump(sum1,sum2);
  return sum1+sum2;
}

long double f(LL r, LL c) {
//  dump(r,c,H-1,W-1);
  if(r==-1||c==-1) return 0;
  if(r==H-1&&c==W-1) return 1;
  if(r==H-1) {
    long double res=0;
    long double p=1.0/pow(2,r+c);
    res+=p;
    FORE(j,1,c) {
      int i=r+c-j;
      p*=(i+1.0)/j;
      res+=p;
    }
    return res;
  }
  if(c==W-1) {
    long double res=0;
    long double p=1.0/pow(2,r+c);
    res+=p;
    FORE(i,1,r) {
      int j=r+c-i;
      p*=(j+1.0)/i;
      res+=p;
    }
    return res;
  }
  
  long double res=1;
  FORE(n,1,r+c) res*=n*0.5;
  FORE(n,1,c) res/=n;
  FORE(n,1,r) res/=n;
  return res;
}

long double crange(LL r, LL lb, LL hb) {
  if(r==-1) return 0;
  long double p0=f(r,lb);
  long double res=p0*(lb==W-1?1:0.5);
  long double p=p0;
//  dump(r,lb,hb,res);
  FOR(c,lb+1,hb) {
    if(c!=W-1) {
      long double div=2.0*(c==0?1:c);
      p*=(r+c),p/=div;
    } else {
      p=f(r,c);
    }
    long double comp=(c==W-1?1.0:0.5);
    res+=p*comp;
//    dump(c,r+c,comp,p);
  }
//  dump(r,lb,hb,p0,res);
  return res;
}
long double rrange(LL c, LL lb, LL hb) {
  if(c==-1) return 0;
  long double p0=f(lb,c);
  long double res=p0*(lb==H-1?1:0.5);
  long double p=p0;
//  dump(c,lb,hb,p0);
  FOR(r,lb+1,hb) {
    if(r!=H-1) {
      long double div=2.0*(r==0?1:r);
      p*=(r+c),p/=div;
    } else {
      p=f(r,c);
    }
    long double comp=(r==H-1?1.0:0.5);
    res+=p*comp;
//    dump(r,p);
  }
//  dump(c,lb,hb,p0,res);
  return res;
}

bool hole(LL i, LL j) {
//  dump(i,j,U<=i,i<D,L<=j,j<R);
  return (U<=i&&i<D&&L<=j&&j<R);
}
long double dp[310][310];
long double solvedp() {
  ZERO(dp);
  dp[0][0]=1;
  if(hole(0,0)) dp[0][0]=0;
  REP(i,H)REP(j,W) {
    if(i==H-1) {
      if(!hole(i,j+1))dp[i][j+1]+=dp[i][j];
    } else if(j==W-1) {
      if(!hole(i+1,j))dp[i+1][j]+=dp[i][j];
    } else {
      if(!hole(i+1,j)) dp[i+1][j]+=0.5*dp[i][j];
      if(!hole(i,j+1)) dp[i][j+1]+=0.5*dp[i][j];
    }
  }
  return dp[H-1][W-1];
}

long double solve_wrong() {
//  dump(W,H,L,U,R,D,hole(H-1,W-1));
  if(L==0&&R==W) return 0;
  if(U==0&&D==H) return 0;
  if(H==1||W==1) return 0;
  if(L==0&&U==0) return 0;
  if(R==W&&D==H) return 0;
  long double sum1=0,sum2=0;
  sum1=crange(U-1,L,R);
  sum2=rrange(L-1,U,D);
  
//  dump(sum1,sum2);
  long double sum=sum1+sum2;
  long double res=1.0-sum;
  return res;
}

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
int genRandNum(int lb, int ub) {
  assert(lb<ub);
  // Helper to generate random integer in range [lb, ub)
  int x = rnd() % (int)(ub - lb);
  return x + lb;
}

void test() {
  H=genRandNum(1,300),W=genRandNum(1,300);
  U=genRandNum(0,H),D=genRandNum(U+1,H+1);
  L=genRandNum(0,W),R=genRandNum(L+1,W+1);
  
  double a=solvedp(),b=solve();
  dump(W,H,L,U,R,D);
  dump(a,b,abs(a-b));
  assert(abs(a-b)<=1e-5);
}

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
//  while(true) test();
  
  int T; cin>>T;
  for(int t=1; t<=T; ++t) {
    cin>>W>>H>>L>>U>>R>>D;
    --L,--U;
    
    cout<<"Case #"<<t<<": ";
    cout<<solve()<<endl;
  }
  return 0;
}
