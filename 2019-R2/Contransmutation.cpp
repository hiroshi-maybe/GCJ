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
const int MOD=1000000007;
//const int MOD=998244353;
struct ModInt {
  unsigned int val;
  ModInt(): val(0) {}
  ModInt(int v) { norm(v%MOD); }
  ModInt(long long v) { norm(v%MOD); }
  ModInt& norm(long long v) {
    v=v<0?v%MOD+MOD:v; // negative
    v=v>=MOD?v-MOD:v; // mod
    val=(unsigned int)v;
    return *this;
  }
  explicit operator bool() const { return val!=0; }
  ModInt operator-() const { return ModInt(0)-*this; }
  ModInt &operator+=(ModInt that) { return norm((long long)val+that.val); }
  ModInt &operator-=(ModInt that) { return norm((long long)val-that.val); }
  ModInt &operator*=(ModInt that) { val=(unsigned long long)val*that.val%MOD; return *this; }
  ModInt &operator/=(ModInt that) { return *this*=that.inv(); }
  ModInt operator+(ModInt that) const { return ModInt(*this)+=that; }
  ModInt operator-(ModInt that) const { return ModInt(*this)-=that; }
  ModInt operator*(ModInt that) const { return ModInt(*this)*=that; }
  ModInt operator/(ModInt that) const { return ModInt(*this)/=that; }
  ModInt pow(long long n) const {
    ModInt x=*this, res=1;
    while(n>0) {
      if(n&1) res*=x;
      x*=x,n>>=1;
    }
    return res;
  }
  ModInt inv() const { return (*this).pow(MOD-2); }
  bool operator==(ModInt that) const { return val==that.val; }
  bool operator!=(ModInt that) const { return val!=that.val; }
  friend ostream& operator<<(ostream& os, const ModInt& that) { return os<<that.val; }
};
struct SCC {
public:
  // input
  int V;
  vector<vector<int>> G, G_T; /* G_T=(V,E_T) where E_T = {(u,v):(v,u)∈E} */
  SCC(int V): V(V), G(V), G_T(V), cid(V, -1), viz(V) {}
  void edge(int u, int v) {
    assert(u<V&&v<V);
    G[u].push_back(v);
    G_T[v].push_back(u);
  }
  
  // build SCCs, Θ(V+E) time
  vector<int> cid; /* vertex -> component ID */
  vector<vector<int>> CC; /* component ID -> vertices */
  void build() {
    for(int u=0; u<V; ++u) dfs(u);
    int id=0;
    for(int i=(int)fins.size()-1; i>=0; --i) if(cid[fins[i]]==-1) dfs_t(fins[i], id++);
    CC.resize(id);
    for(int u=0; u<V; ++u) CC[cid[u]].push_back(u);
  }
  
  // contract SCCs and build component graph, Θ(V+E) time
  vector<vector<int>> G_SCC;
  void contract() {
    set<pair<int, int>> es;
    for(int u=0; u<V; ++u) for(int v : G[u]) if(cid[u]!=cid[v]) es.emplace(cid[u],cid[v]);
    
    G_SCC.resize(CC.size());
    for(auto e : es) G_SCC[e.first].push_back(e.second);
  }
private:
  vector<int> viz, fins;
  void dfs(int u) {
    if(viz[u]) return;
    viz[u]=true;
    for(int v : G[u]) dfs(v);
    fins.push_back(u);
  }
  void dfs_t(int u, int id) {
    cid[u]=id;-
    for(int v : G_T[u]) if(cid[v]==-1) dfs_t(v, id);
  }
};

/*
 
 5/24/2019
 
 16:11-21:20 got AC. It took tons of time to find 1 byte bug fix 👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎👎
 
 https://scrapbox.io/snuke/GCJ_2019_R2
 http://kmjp.hatenablog.jp/entry/2019/05/22/0930
 https://codingcompetitions.withgoogle.com/codejam/round/0000000000051679/0000000000146185
 https://twitter.com/ei1333/status/1129786597627457541
 https://twitter.com/ei1333/status/1129788734805762048
 https://twitter.com/n_vip/status/1129787028193857536
 
 */

// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG Contransmutation.cpp && ./a.out < Contransmutation.in | diff Contransmutation.out -
const int MAX_N=1e5+10;
LL A[MAX_N],G[MAX_N];
ModInt dp[MAX_N];
int canhaveinf[MAX_N],canexpinf[MAX_N],isinfff[MAX_N],iszero[MAX_N],ind[MAX_N];
int M;
vector<int> E[101010];

SCC scc(MAX_N);

void solve() {
  scc.build();
  ZERO(G),ZERO(dp),ZERO(isinfff),ZERO(canhaveinf),ZERO(canexpinf),ZERO(ind);
  REP(i,M) iszero[i]=true;
  int N=SZ(scc.CC);
  REP(u,M) {
    int cu=scc.cid[u];
    int cv1=scc.cid[scc.G[u][0]],cv2=scc.cid[scc.G[u][1]];
    if(cu==cv1&&cu==cv2) canhaveinf[cu]=true;
    if((cu==cv1||cu==cv2)) canexpinf[cu]=true;
    if(cu!=cv1) ind[cv1]++,E[cu].push_back(cv1);
    if(cu!=cv2) ind[cv2]++,E[cu].push_back(cv2);
  }
  REP(i,M) G[scc.cid[i]]+=A[i];
  REP(i,N) {
    iszero[i]=G[i]==0;
    dp[i]=G[i];
  }
  queue<int> Q;
  REP(u,N) if(ind[u]==0) Q.emplace(u);
  while (SZ(Q)) {
    int u=Q.front(); Q.pop();
    if(!iszero[u]&&canhaveinf[u]) isinfff[u]=1;
    if(scc.cid[0]==u) break;
    if(!iszero[u]&&canexpinf[u]) isinfff[u]=1;
    FORR(v,E[u]) {
      isinfff[v]|=isinfff[u];
      dp[v]+=dp[u];
      if(!iszero[u]) iszero[v]=false;
      if(isinfff[v]) iszero[v]=false;
      --ind[v];
      if(ind[v]==0) Q.emplace(v);
    }
  }
  if(isinfff[scc.cid[0]]) {
    cout<<"UNBOUNDED"<<endl;
  } else {
    cout<<dp[scc.cid[0]]<<endl;
  }
}
int main(int argc, char* argv[]) {
  int T; cin>>T;
  for(int t=1; t<=T; ++t) {
    cin>>M; scc=SCC(M);
    REP(i,M) {
      int u,v; cin>>u>>v;
      --u,--v;
      scc.edge(i,u),scc.edge(i,v);
      E[i].clear();
    }
    REP(i,M) cin>>A[i];
    
    cout<<"Case #"<<t<<": ";
    solve();
  }
  return 0;
}
