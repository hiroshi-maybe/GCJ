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

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Pylons.cpp && ./a.out < Pylons.in | diff Pylons.out -

/*
 
 4/12/2019
 
 18:52-19:58 small test set passed

 Generally this is Hamiltonian path problem which is NP-hard.
 We need some idea unique to this problem.

 I analyzed impossible cases to construct a rule.
 I figured out that 2xa(a<=3), 3xb(b<=3). However I couldn't move forward.
 
 4/14/2019
 
 19:15-19:55 read editorials and large test case passed by random shuffle.
 22:00-23:20 add solution by constructive approach
 
 2xW:
 o---->
 -->o->
 
 3xW:
 o---->
 ->o-->
 o---->
 
 4x4:
 o-->
 ->o>
 o-->
 ->o>
 (swap is needed to avoid diagonal conflict)

 https://codingcompetitions.withgoogle.com/codejam/round/0000000000051635/0000000000104e03
  - constructive
  - randomization
  - greedy
 http://drken1215.hatenablog.com/entry/2019/04/13/143500
  - constructive
 http://kmjp.hatenablog.jp/entry/2019/04/15/0930
  - constructive
 https://twitter.com/xuzijian629/status/1116920887016599552
  - constructive
 https://twitter.com/satanic0258/status/1116907238172397569
  - constructive
 https://twitter.com/yosupot/status/1116933713680461824
  - randomization
 https://shashankmishracoder.wordpress.com/2019/04/13/google-code-jam-2019-round-1a-pylon-dfs-and-backtracking-approach/
  - randomization
 
 */

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
int R,C;

void nope() {
  cout<<"IMPOSSIBLE"<<endl;
}
vector<II> f(int H, int W, int off) {
  VI P(H,0); REP(i,H) if(i%2==1) P[i]=off;
  vector<II> res;
  int i=0;
  set<II> S;
  while(SZ(res)<H*W) {
    res.emplace_back(i,P[i]);
    S.emplace(i,P[i]);
    P[i]=(P[i]+1)%W;
    i=(i+1)%H;
  }
  assert(SZ(S)==H*W);
  return res;
}
void show(vector<vector<II>> res, bool swapped) {
//  dump(SZ(res));
  cout<<"POSSIBLE"<<endl;
  int roff=0;
  set<II> S;
  FORR(X,res) {
//    dump(SZ(X));
    FORR(p,X) {
      int i=p.first+1+roff,j=p.second+1;
      if(swapped) swap(i,j);
      cout<<i<<" "<<j<<endl;
      S.emplace(i,j);
    }
    int H=SZ(X)/C;
    roff+=H;
  }
//  if(SZ(S)!=R*C) dump(SZ(S),R*C);
  assert(SZ(S)==R*C);
}
void solve() {
//  dump(R,C);
  bool swapped=false;
  if(R>C) swap(R,C),swapped=true;
  if(R==1) {
    nope();
    return;
  }
  if(R==2&&C<5) {
    nope();
    return;
  }
  if(R==3&&C<4) {
    nope();
    return;
  }
  vector<vector<II>> res;
  if(R==4&&C==4) {
    vector<II> X=f(R,C,2);
    int M=SZ(X);
    swap(X[M-4],X[M-3]),swap(X[M-2],X[M-1]);
    res.push_back(X);
  } else {
    if(R%2==0) REP(_,R/2) res.push_back(f(2,C,3));
    else {
      REP(_,(R-3)/2) res.push_back(f(2,C,3));
      res.push_back(f(3,C,2));
    }
  }
  show(res,swapped);
}

VI G[400];
int viz[400];
int ith(int mask, int i) {
  return (mask>>i)&1;
}
int f(int p, int cnt, VI &path) {
  if(cnt==R*C) {
    cout<<"POSSIBLE"<<endl;
    assert(SZ(path)==R*C);
    REP(k,SZ(path)) {
      int i=path[k]/C,j=path[k]%C;
      cout<<i+1<<" "<<j+1<<endl;
    }
    return 1;
  }
//  shuffle(G[p].begin(), G[p].end(), rnd);
  FORR(q,G[p]) if(!viz[q]) {
    path.push_back(q);
    dump(p,q);
    viz[q]=1;
    int res=f(q,cnt+1,path);
    viz[q]=0;
    path.pop_back();
    if(res) return 1;
  }
  return 0;
}
void solve_bruteforce() {
  dump(R,C);
  REP(i,400) G[i].clear();
  REP(i1,R)REP(j1,C) {
    REP(i2,R)REP(j2,C) if(i1!=i2&&j1!=j2) {
      if(i1-j1==i2-j2) continue;
      if(i1+j1==i2+j2) continue;
      int u=i1*C+j1,v=i2*C+j2;
      G[u].push_back(v);
    }
  }
  REP(i,R*C) shuffle(G[i].begin(), G[i].end(), rnd);
  REP(i,R)REP(j,C) {
    int u=i*C+j;
    VI p={u};
    ZERO(viz);
    viz[u]=1;
    int res=f(u,1,p);
    if(res) return;
  }
  cout<<"IMPOSSIBLE"<<endl;
}
int main(int argc, char* argv[]) {
  /*
  cout<<19*19<<endl;
  FORE(i,2,20)FORE(j,2,20) {
    cout<<i<<" "<<j<<endl;
  }*/
  
  int T; cin>>T;
  for(int t=1; t<=T; ++t) {
    cin>>R>>C;
    cout<<"Case #"<<t<<": ";
    solve();
  }
  return 0;
}
