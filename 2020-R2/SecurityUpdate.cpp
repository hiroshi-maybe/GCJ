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

// $ cp-batch SecurityUpdate | diff SecurityUpdate.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address SecurityUpdate.cpp && ./a.out

/*

 5/16/2020

 7:58-8:49 visible
 9:20 submit for hidden but got WA

 11:15-12:10, 13:40-15:25 found a test case which hacks my code after looking at @tourist's code

  ```
  1
  5 4
  1 -2 -3 10
  1 2
  2 5
  1 3
  3 4
  ```

 16:47 figured out why pre-determine distances from X[i]>0. Below test case fails.
  ```
  1
  3 3
  1 1
  1 2
  2 3
  3 1
  ```

  17:36 Wrapped up. Figured out all the bugs.

  https://twitter.com/hanseilimak/status/1261808717504188416
  https://codingcompetitions.withgoogle.com/codejam/round/000000000019ffb9/000000000033871f
  https://twitter.com/satanic0258/status/1261697684970237952
  https://twitter.com/yamerarenaku/status/1261697919503044610
  https://twitter.com/konjo_p/status/1261696595101278210

 */

const int MAX_N=1e2+1,MAX_M=1e3+1;
int C,D,X[MAX_N];

int res[MAX_M];
int dists[MAX_N];
vector<III> G[MAX_N];
const int Inf=1e6;
void solve() {
  REP(i,D) res[i]=-1;
  REP(i,C) dists[i]=Inf;
  dists[0]=0;
  VV<int> ord(C+1);
  REP(i,C) {
    if(X[i]<0) ord[-X[i]].push_back(i);
    else dists[i]=X[i];
  }

/*
  REP(u,C) FORR(t,G[u]) {
    int v,i; tie(v,i,ignore)=t;
    if(dists[u]!=Inf&&dists[v]!=Inf) {
      int w=max(1,abs(dists[u]-dists[v]));
      res[i]=w;
      t={v,i,w};
      dump(u,v,w);
      assert(w>0);
    }
  }*/

  vector<int> ds;
  map<int,VI> xs;
  REP(i,C) if(dists[i]<Inf) ds.push_back(dists[i]),xs[dists[i]].push_back(i);
  sort(ALL(ds));
  FORE(i,1,C) if(SZ(ord[i])) {
    assert(SZ(ds)>=i);
    // bug during the contest
    //int d=i<SZ(ds)?ds[i]:ds.back()+1;
    int d=ds[i-1]+1;

    FORR(u,ord[i]) dists[u]=d,ds.push_back(d),xs[d].push_back(u);
    sort(ALL(ds));
  }
  dumpc(ds);
  assert(SZ(ds)==C);

  FORR(kvp,xs) if(kvp.first>0) {
    int d=kvp.first;
    FORR(u,kvp.second) {
      int x=-1;
      assert(d==dists[u]);
      REP(j,SZ(G[u])) {
        int v,w; tie(v,ignore,w)=G[u][j];
        dump(u,v,w,dists[v]);
        if(dists[v]>=d) continue;
        //if(x==-1||dists[get<0>(G[u][x])]>dists[v]) x=j;
        x=j;
        break;
      }
      //if(x==-1) continue;
      assert(x!=-1);
      int v,j; tie(v,j,ignore)=G[u][x];
      int w=d-dists[v];
      dump(u,v,w,dists[v],d);
      assert(w>0);
      G[u][x]={v,j,w};
      res[j]=w;
    }
  }

/*
  REP(u,C) {
    FORR(t,G[u]) {
      int v,j; tie(v,j,ignore)=t;
      res[j]=max(1,abs(dists[v]-dists[u]));
      assert(res[j]>0);
    }
  }*/

  REP(i,D) {
    int w=res[i];
    if(res[i]<0) w=Inf;
    cout<<w<<" \n"[i==D-1];
  }
}

void solve_original_wrong() {
  REP(i,D) res[i]=-1;
  REP(i,C) dists[i]=Inf;
  dists[0]=0;
  VV<int> ord(C+1);
  REP(i,C) {
    if(X[i]<0) ord[-X[i]].push_back(i);
    else dists[i]=X[i];
  }

  REP(u,C) FORR(t,G[u]) {
    int v,i; tie(v,i,ignore)=t;
    if(dists[u]!=Inf&&dists[v]!=Inf) {
      int w=abs(dists[u]-dists[v]);
      res[i]=max(1,w);
      t={v,i,w};
    }
  }

  FORE(i,1,C) if(SZ(ord[i])) {
    vector<II> ds;
    REP(i,C) if(dists[i]<Inf) ds.emplace_back(dists[i],i);
    sort(ALL(ds));
    //int d=i<SZ(ds)?ds[i].first:ds.back().first+1;
    int d=ds[i-1].first+1;

    dump(i,d);
    dumpc(ord[i]);
    dumpc(ds);

    FORR(u,ord[i]) {
      int x=-1;
      REP(j,SZ(G[u])) {
        int v,w; tie(v,ignore,w)=G[u][j];
        dump(u,v,w,dists[v]);
        if(dists[v]>=d) continue;
        x=j;
        break;
      }
      assert(x!=-1);
      dists[u]=d;
      int v,j; tie(v,j,ignore)=G[u][x];
      int w=d-dists[v];
      assert(w>0);
      dump(u,v,w,d);
      G[u][x]={v,j,w};
      res[j]=w;
    }
  }
  REP(i,D) cout<<(res[i]==-1?Inf:res[i])<<" \n"[i==D-1];
}

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  int T; cin>>T;
  for(int t=1; t<=T; ++t) {
    cin>>C>>D;
    REP(i,C) G[i].clear();
    REP(i,C-1)cin>>X[i+1];
    REP(i,D) {
      int u,v; cin>>u>>v;
      --u,--v;
      G[u].emplace_back(v,i,-1),G[v].emplace_back(u,i,-1);
    }

    cout<<"Case #"<<t<<": ";
    solve();
  }
  return 0;
}