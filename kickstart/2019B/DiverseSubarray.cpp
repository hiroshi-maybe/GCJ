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

// $ cp-batch DiverseSubarray | diff DiverseSubarray.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address DiverseSubarray.cpp && ./a.out < DiverseSubarray.in

/*
 
 4/20/2019
 
 16:47-17:28 small test case passed
 18:40 give up
 
 5/5/2019
 
 14:14-17:54 read editorials and got AC
 
 https://codingcompetitions.withgoogle.com/kickstart/round/0000000000050eda/00000000001198c1
 
 @UoA_ZQC's solution with subsegment max sum segment tree:
 https://codingcompetitions.withgoogle.com/kickstart/submissions/0000000000050eda/VW9BX1pRQw
 
 We are going to brute-force left boundary.
 By imos idea, we can represent each element as an event of {+1, -S, 0}.
 Result is max subsegment sum of above events. 
 
 */

struct Node {
  static const int id=0;
  LL ans,sum,pref,suf;
  Node(LL val=0LL) : sum(val) {
    LL v=max(val,0LL);
    ans=v,pref=v,suf=v;
  }
  static Node IDE; // Identity element in monoid
};
// Merge operation should be associative A`op`(B`op`C) == (A`op`B)`op`C
Node Node::IDE=Node();
Node merge(const Node &a, const Node &b) {
  Node res;
  res.sum=a.sum+b.sum;
  res.ans=max({a.ans,b.ans,a.suf+b.pref});
  res.pref=max(a.pref,a.sum+b.pref);
  res.suf=max(b.suf,b.sum+a.suf);
  return res;
}

struct SegmentTree {
public:
  int N__;
  vector<Node> Tree;
  SegmentTree(int N) {
    int n=1;
    // Init by power of 2
    while(n<N) n<<=1;
    this->Tree=vector<Node>(2*n,Node::IDE);
    this->N__=n;
  }
  
  // Initialize tree with `ns`
  void build(const vector<Node> &ns) {
    buildTree(ns,0,0,N__);
  }
  
  // Update k-th (0-indexed) value
  void update(int i, const Node &x) {
    updateTree(i,x,0,0,N__);
  }
  
  // query in range [L,R)
  Node query(int L, int R) {
    return queryTree(L,R,0,0,N__);
  }
private:
  void buildTree(const vector<Node> &ns, int i, int l, int r) {
    if (l==r-1) {
      if(l<ns.size()) Tree[i]=ns[l];
      return;
    }
    
    int mid=l+(r-l)/2;
    buildTree(ns,2*i+1,  l,mid); // left child
    buildTree(ns,2*i+2,mid,  r); // right child
    
    Tree[i]=merge(Tree[2*i+1],Tree[2*i+2]);
  }
  
  void updateTree(int p, const Node &x, int i, int l, int r) {
    if (l==r-1) { Tree[i]=x; return; }
    
    int mid=l+(r-l)/2;
    if(p<mid) updateTree(p,x,2*i+1,  l,mid);
    else      updateTree(p,x,2*i+2,mid,  r);
    
    Tree[i]=merge(Tree[2*i+1],Tree[2*i+2]);
  }
  
  Node queryTree(int L, int R, int i, int l, int r) {
    // out of range
    if (r<=L||R<=l) return Node::IDE;
    
    // all covered
    if (L<=l&&r<=R) return Tree[i];
    
    // partially covered
    int mid=l+(r-l)/2;
    Node a=queryTree(L,R,2*i+1,  l,mid);
    Node b=queryTree(L,R,2*i+2,mid,  r);
    Node res=merge(a,b);
    return res;
  }
};

const int MAX_N=1e6+1;
LL A[MAX_N];
int N,S;

VI ps[MAX_N];
void solve() {
  REP(i,MAX_N) ps[i].clear();
  REP(i,N) ps[A[i]].push_back(i);
  SegmentTree T(N);
  LL res=0;
  for(int i=N-1; i>=0; --i) {
    int a=A[i];
    Node x(1);
    T.update(i,x);
    int p=lower_bound(ALL(ps[a]),i)-ps[a].begin();
    if(p+S+1<SZ(ps[a])) {
      Node x(0);
      T.update(ps[a][p+S+1],x);
    }
    if(p+S<SZ(ps[a])) {
      Node x(-S);
      T.update(ps[a][p+S],x);
    }
    SMAX(res,T.query(0,N).ans);
  }
  cout<<res<<endl;
}

void solve_wrong() {
  int curp[MAX_N];
  dump(N,S);
  int res=0;
  set<II> Q;
  REP(i,N) {
    int a=A[i];
    ps[a].push_back(i);
  }
  REP(a,MAX_N) if(SZ(ps[a])>S) {
    Q.emplace(ps[a][S],a);
    curp[a]=S;
  }
  Q.emplace(N,MAX_N);
  
  map<int,int> cnt;
  int sum=0,r=0;
  REP(i,N) {
    int a=A[i];
    while(SZ(Q)) {
      int rr,b; tie(rr,b)=*Q.begin();
      while(r<rr) {
        int a=A[r++];
        cnt[a]++,sum++;
        assert(cnt[a]<=S);
        dump(i,r,a,cnt[a],sum);
        SMAX(res,sum);
      }
      if(rr==N) goto fin;
      Q.erase({rr,b});
      
      if(a==b) break;
    }
    cnt[a]--,sum--;
    if(curp[a]<SZ(ps[a])&&Q.count({ps[a][curp[a]],a})) Q.erase({ps[a][curp[a]],a});
    curp[a]++;
    if(curp[a]<SZ(ps[a])) Q.emplace(ps[a][curp[a]],a);
  }
fin:
  cout<<res<<endl;
}

void solve_small() {
  int res=0;
  REP(i,N) {
    map<int,int> cnt;
    int sum=0;
    FOR(j,i,N) {
      int a=A[j];
      cnt[a]++;
      if(cnt[a]==S+1) sum-=S;
      else if(cnt[a]<=S) sum++;
//      dump(i,j,a,sum);
      SMAX(res,sum);
    }
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  int T; cin>>T;
  FORE(t,1,T) {
    cin>>N>>S;
    REP(i,N) cin>>A[i];
    cout<<"Case #"<<t<<": ";
    solve();
  }
  
  return 0;
}
