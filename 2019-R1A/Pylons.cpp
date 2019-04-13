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

// $ cp-batch Pylons | diff Pylons.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Pylons.cpp && ./a.out < Pylons.in | diff Pylons.out -

/*
 
 4/12/2019
 
 18:52-19:58 small passed
 
 */

int R,C;
VI G[400];
int ith(int mask, int i) {
  return (mask>>i)&1;
}
int f(int p, int mask, VI &path) {
  int full=(1<<(R*C))-1;
  if(mask==full) {
    cout<<"POSSIBLE"<<endl;
    assert(SZ(path)==R*C);
    REP(k,SZ(path)) {
      int i=path[k]/C,j=path[k]%C;
      cout<<i+1<<" "<<j+1<<endl;
    }
    return 1;
  }
  dump(p,mask,__builtin_popcount(mask));
  dumpc(G[p]);
  FORR(q,G[p]) if(!ith(mask,q)) {
    path.push_back(q);
    dump(p,q);
    int res=f(q,mask|(1<<q),path);
    path.pop_back();
    if(res) return 1;
  }
  return 0;
}
void solve() {
  dump(R,C);
  REP(i,400) G[i].clear();
  REP(i1,R)REP(j1,C) {
    REP(i2,R)REP(j2,C) if(i1!=i2&&j1!=j2) {
      if(i1-j1==i2-j2) continue;
      if(i1+j1==i2+j2) continue;
      int u=i1*C+j1,v=i2*C+j2;
      G[u].push_back(v);
//      cerr<<u<<" "<<v<<endl;
    }
  }
  REP(i,R)REP(j,C) {
    int u=i*C+j;
    VI p={u};
    int res=f(u,1<<(u),p);
    if(res) return;
  }
/*  int full=(1<<(R*C))-1;
  MINUS(memo),MINUS(path);
  REP(i,R)REP(j,C) {
    int res=f(i*C+j,1<<(i*C+j));
    if(res) {
      cout<<"POSSIBLE"<<endl;
      VI ans;
      int p=i*C+j,mask=1<<(i*C+j);
      while(mask!=full) {
        int q=path[p][mask];
        ans.push_back(q);
        p=q,mask|=(1<<q);
      }
      assert(SZ(ans)==R*C);
      REP(k,SZ(ans)) {
        int i=ans[k]/C,j=ans[k]%C;
        cout<<i+1<<" "<<j+1<<endl;
      }
      return;
    }
  }*/
  cout<<"IMPOSSIBLE"<<endl;
}
int main(int argc, char* argv[]) {
  int T; cin>>T;
  for(int t=1; t<=T; ++t) {
    cin>>R>>C;
    cout<<"Case #"<<t<<": ";
    solve();
  }
  return 0;
}
