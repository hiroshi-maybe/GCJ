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

// $ cp-batch BlindfoldedBullseye | diff BlindfoldedBullseye.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address BlindfoldedBullseye.cpp && ./a.out

/*
 
 4/19/2020
 
 9:36-10:50 AC
 
 https://codingcompetitions.withgoogle.com/codejam/round/000000000019fef2/00000000002d5b63
 https://twitter.com/snuke_/status/1251942812775403520
 https://twitter.com/n_vip/status/1251941771715571712
 https://twitter.com/ei1333/status/1251941325621981185
 https://twitter.com/gzlcp/status/1251941260195033089
 https://twitter.com/kzyKT_M/status/1251941345544921089
 https://twitter.com/yosupot/status/1251942969868824576
 
 */

LL A,B;

// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG BlindfoldedBullseye.cpp && python testing_tool.py ./a.out
// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG BlindfoldedBullseye.cpp && python interactive_runner.py python local_testing_tool.py 0 -- ./a.out
int ask(LL x, LL y) {
  dump(x,y);
  cout<<x<<" "<<y<<endl;
  string res; cin>>res;
  if(res=="WRONG") exit(0);
  if(res=="CENTER") {
    dump(res);
    return 2;
  }
  if(res=="HIT") return 1;
  return 0;
}
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
int genRandNum(int lb, int ub) {
  assert(lb<ub);
  // Helper to generate random integer in range [lb, ub)
  int x = rnd() % (int)(ub - lb);
  return x + lb;
}
vector<pair<int,int>> moves = { {0,1}/*U*/,{1,0}/*R*/,{0,-1}/*D*/,{-1,0}/*L*/ };
LL adj(LL a) {
  LL res=min(a,(LL)1e9);
  res=max(res,(LL)-1e9);
  return res;
}
bool found=false;
LL f(int mi, LL x, LL y) {
  II move=moves[mi];
  pair<LL,LL> good={x,y},bad={adj(x+move.first*2e9),adj(y+move.second*2e9)};
  if(bad.first==1e9) bad.first+=1,assert(bad.second==y);
  if(bad.first==-1e9) bad.first-=1,assert(bad.second==y);
  if(bad.second==1e9) bad.second+=1,assert(bad.first==x);
  if(bad.second==-1e9) bad.second-=1,assert(bad.first==x);

  /*
  dump(x,y,mi);
  dump(good.first,good.second);
  dump(bad.first,bad.second);*/
  
  while(abs(good.first-bad.first)+abs(good.second-bad.second)>1) {
    LL a=(good.first+bad.first)/2,b=(good.second+bad.second)/2;
    int res=ask(a,b);
    if(res==2) {
      found=true;
      return -1;
    }
    (res?good:bad)={a,b};
  }
  return mi%2==0?good.second:good.first;
}
int main() {
  int T; scanf("%d", &T);
  LL A,B; scanf("%lld %lld", &A,&B);
  dump(T,A,B);
  for(int t=1; t<=T; ++t) {
    found=false;
    int cnt=150;
    LL x0=0,y0=0;
    while(cnt--) {
      LL x=genRandNum(0,1e9+1),y=genRandNum(0,1e9+1);
      if(genRandNum(0,2)) x=-x;
      if(genRandNum(0,2)) y=-y;
      int res=ask(x,y);
      if(res==2) {
        found=true;
        break;
      }
      if(res==1) {
        x0=x,y0=y;
        break;
      }
    }
    dump(x0,y0);
    if(found) continue;
    
    LL u=f(0,x0,y0);
    if(found) continue;
    LL r=f(1,x0,y0);
    if(found) continue;
    LL d=f(2,x0,y0);
    if(found) continue;
    LL l=f(3,x0,y0);
    if(found) continue;
    LL x1=(l+r)/2,y1=(d+u)/2;
    dump(l,r,d,u);
    dump(x1,y1);
    FORE(d1,-1,1){
      FORE(d2,-1,1) {
        LL x=x1+d1,y=y1+d2;
        int res=ask(x,y);
        if(res==2) {
          found=true;
          break;
        }
      }
      if(found) break;
    }
    assert(found);
  }
  return 0;
}
