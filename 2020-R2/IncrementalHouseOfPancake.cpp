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

// $ cp-batch IncrementalHouseOfPancake | diff IncrementalHouseOfPancake.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address IncrementalHouseOfPancake.cpp && ./a.out

/*
 
 5/16/2020
 
 7:01-7:57 TS1 passed, TS2 WA due to overflow....
 10:30-11:00 figured out the failed test case. 1e18 1e17 is the case.

 https://codingcompetitions.withgoogle.com/codejam/round/000000000019ffb9/00000000003384ea
 
 */

LL L,R;

LL f(LL a, LL d) {
  LL good=1,bad=2e9+1; /* 1e10 overflows */
  while(abs(good-bad)>1) {
    LL mid=(good+bad)/2;
    dump(mid,mid*(2LL*a+mid-1)/2);
    bool res=(LL)mid*(2LL*a+mid-1)/2<=(LL)d;
    (res?good:bad)=mid;
  }
  return good;
}

pair<LL,LL> calc(LL l, LL r, LL i, LL n) {
  LL x=(n+1)/2,y=n-x;
  LL s1=(LL)x*(i+x-1),s2=(LL)y*(i+y);
  return {s1,s2};
}

tuple<LL,LL,LL> g(LL l, LL r, LL i) {
  bool swapped=false;
  if(l<r) swapped=true,swap(l,r);
  LL good=0,bad=2e9+1;    
  while(abs(good-bad)>1) {
    LL mid=(good+bad)/2;
    auto sums=calc(l,r,i,mid);
    //dump(mid,sums.first,l,sums.second,r,sums.first<=l,sums.second<=r);
    ((sums.first<=l&&sums.second<=r)?good:bad)=mid;
  }  
  auto sums=calc(l,r,i,good);
  pair<LL,LL> res={l-sums.first, r-sums.second};
  if(swapped) swap(res.first,res.second);
  return {res.first, res.second, good};
}

void solve() {
  LL l=L,r=R,i=1;
  while(max(l,r)>=i) {
    LL d=max(l,r)-min(l,r);    
    LL n=f(i,d);
    LL sum=n*(2LL*i+n-1)/2;
    if(l>=r) l-=sum;
    else r-=sum;

    bool willbreak=false;
    if(d<=i) willbreak=true;
    i+=n;
    if(willbreak) break;
  }
  //dump(l,r,i);
  LL ll,rr,n; tie(ll,rr,n)=g(l,r,i);
  //dump(ll,rr,n);
  cout<<i+n-1<<" "<<ll<<" "<<rr<<endl;
}

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  int T; cin>>T;
  for(int t=1; t<=T; ++t) {
    cin>>L>>R;  
    cout<<"Case #"<<t<<": ";
    solve();
  }
  return 0;
}
