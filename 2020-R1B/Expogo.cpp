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

// $ cp-batch Expogo | diff Expogo.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Expogo.cpp && ./a.out

/*
 
 4/19/2020
 
 9:00-9:35 Solved Test Set 1 and 2
 
 21:12-22:35 read editorial and got AC
 
 https://codingcompetitions.withgoogle.com/codejam/round/000000000019fef2/00000000002d5b62
 https://docs.google.com/document/d/1Yq384PEooRVsmlzB103YMLWwE_JhPN8AbxZagNrF_vY/edit#bookmark=id.sbhkp1klftk1
 https://docs.google.com/document/d/1Yq384PEooRVsmlzB103YMLWwE_JhPN8AbxZagNrF_vY/edit#bookmark=id.bhsl9n4pd4oq
 https://twitter.com/xuzijian629/status/1251942002280693760
 https://twitter.com/snuke_/status/1251942213396787200
 https://twitter.com/yosupot/status/1251942969868824576
 https://twitter.com/n_vip/status/1251941771715571712
 https://twitter.com/ei1333/status/1251941325621981185
 https://twitter.com/gzlcp/status/1251941260195033089
 https://twitter.com/enuemuenuemuenu/status/1251945192522801153
 
 */

LL X,Y;
vector<pair<int,int>> moves = { {0,1}/*R*/,{1,0}/*D*/,{0,-1}/*L*/,{-1,0}/*U*/ };
bool ith(int mask, int i) {
  return (mask>>i)&1;
}

bool ok(LL x, LL y) {
  LL xx=x/2,yy=y/2;
  if(xx%2==0&&yy%2==0) return false;
  if(xx%2==1&&yy%2==1) return false;
  return true;
}

void solve() {
  LL x=abs(X),y=abs(Y);
  if(x%2==y%2) {
    cout<<"IMPOSSIBLE"<<endl;
    return;
  }
  string res;
  while(true) {
    dump(x,y);
    if(x==1&&y==0) {
      res.push_back('E');
      break;
    }
    if(x==0&&y==1) {
      res.push_back('N');
      break;
    }
    
    char d='?';
    if(x%2) {
      if(ok(x+1,y)) d='W',x+=1;
      else d='E',x-=1;
    } else {
      if(ok(x,y+1)) d='S',y+=1;
      else d='N',y-=1;
    }
    x/=2,y/=2;
    res.push_back(d);
  }
  dump(res);
  if(X<0) REP(i,SZ(res)) {
    if(res[i]=='W') res[i]='E';
    else if(res[i]=='E') res[i]='W';
  }
  if(Y<0) REP(i,SZ(res)) {
    if(res[i]=='N') res[i]='S';
    else if(res[i]=='S') res[i]='N';
  }
  cout<<res<<endl;
}

void solve_tesset2() {
  REP(maxp,10) {
    REP(mask,1<<maxp) {
      REP(mask2,1<<maxp) {
        LL x=0,y=0;
        string res;
        REP(i,maxp) {
          LL d=1<<i;
          string s;
          if(!ith(mask,i)) d=-d,s="SW";
          else s="NE";
          if(ith(mask2,i)) x+=d;
          else y+=d;
          res.push_back(s[ith(mask2,i)]);
        }
        if(x==X&&y==Y) {
          cout<<res<<endl;
          return;
        }
      }
    }
  }
  cout<<"IMPOSSIBLE"<<endl;
}

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  int T; cin>>T;
  for(int t=1; t<=T; ++t) {
    cin>>X>>Y;
    cout<<"Case #"<<t<<": ";
    solve();
  }
  return 0;
}
